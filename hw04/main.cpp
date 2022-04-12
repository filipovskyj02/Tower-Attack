#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

class CFile {
public:
    struct CFileData {
        uint8_t *array = nullptr;
        uint32_t size = 0;
        int refCounter = 0;
        CFileData() {
            array = nullptr;
            size = 0;
            refCounter = 1;
        }
        ~CFileData(){
            delete[] array;
        }

    };


    uint32_t pos = 0;
    CFile * prev = nullptr;
    CFileData * ptr;
    void AddRef (CFileData *p) {
        ptr = p;
        ++p->refCounter;
    }
    void Release () {
        if (--ptr->refCounter <= 0) delete ptr;
    }
    CFile () {
        ptr = new CFileData();
        pos = 0;
        prev = nullptr;
    }
    ~CFile (){
        delete this->prev;
        Release();


    }
    CFile (CFile & ref){
        AddRef(ref.ptr);
        this->prev = nullptr;
        if (ref.prev){
            this->prev = new CFile(*ref.prev);
        }

        pos = ref.pos;
    }
    CFile operator = (CFile & ref){

        if (&ref == this) return *this;
        CFile * tmp = prev;
        Release();
        AddRef(ref.ptr);
        this->prev = nullptr;
        if (ref.prev) {
            this->prev= new CFile(*ref.prev);
        }

        pos = ref.pos;
        delete tmp;
        return * this;

    }
    void deepCopy (){
        if (ptr->refCounter <= 1) return;

        CFileData * a = new CFileData;
        a->refCounter = 1;
        a->array = new uint8_t[ptr->size];
        a->size = ptr->size;

        for (unsigned int i = 0; i < a->size; i++){
            a->array[i] = ptr->array[i];


        }
        Release();
        ptr = a;



    }
    void changeSize (uint32_t size) {
        deepCopy();
        CFileData * a = new CFileData;
        a->array = new uint8_t[size]();
        a->size = size;
        a->refCounter = 1;

        for (unsigned int i = 0; i < size; i++) {
            if (i >= ptr->size) break;
            a->array[i] = ptr->array[i];
        }

        Release();
        ptr = a;



    }
    int getRef (){
        return ptr->refCounter;

    }
    friend std::ostream &operator<<(std::ostream &out, const CFile &c) {

        out << " ( ";
        for (unsigned int i = 0; i < c.ptr->size; i++) {
                out << (unsigned) c.ptr->array[i] << " , ";
        }
        out << " ) " << endl;
        return out;
    }
    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes ){
        if (bytes == 0) return 0;

        deepCopy();
        if (pos + bytes > ptr->size) changeSize(pos + bytes);
        memcpy(&ptr->array[pos],src,bytes);
        pos += bytes;
        return bytes;


    }
    uint32_t                 fileSize                      ( void ) const{
        return ptr->size;
    }
    bool                     seek                          ( uint32_t          offset ){
        if (offset > ptr->size) return false;
        pos = offset;
        return true;

    }
    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes ){
        if (pos + bytes >= ptr->size) bytes = ptr->size - pos;
        memcpy(dst,&ptr->array[pos],bytes);
        pos += bytes;
        return bytes;

    }
    void                     truncate                      ( void ){
        deepCopy();
        changeSize(pos);

    }
    void                     addVersion                    ( void ){


        CFile * tmp = this->prev;
        this->prev = new CFile(*this);
        delete tmp;


    }
    bool                     undoVersion                   ( void ){


        if (this->prev == nullptr) return false;
        *this = *prev;
        return true;





    }

};


#ifndef __PROGTEST__
bool               writeTest                               ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          wrLen )
{
    return x . write ( data . begin (), data . size () ) == wrLen;
}

bool               readTest                                ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          rdLen )
{
    uint8_t  tmp[100];
    uint32_t idx = 0;

    if ( x . read ( tmp, rdLen ) != data . size ())
        return false;
    for ( auto v : data )
        if ( tmp[idx++] != v )
            return false;
    return true;
}


int main ( void )
{

    CFile a;
    a.changeSize(10);

    cout << a.getRef() << endl;
    for (int i = 0; i < 10; i++){
        a.ptr->array[i] = i;

    }
    cout << a;
    a.changeSize(3);
    CFile b(a);
    cout << a.getRef() << endl;
    cout << a.ptr->size;
    cout << b;
    b.deepCopy();
    b.ptr->array[1] = 5;
    cout << a;
    cout << b;
    cout << a.getRef() << endl;
    cout << b.getRef() << endl;
    b.changeSize(5);
    cout << b;
    cout << a;



    CFile f0;
    f0 . truncate ();
    assert ( f0 . seek ( 0 ));
    f0 . addVersion();
    assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
    assert ( f0 . undoVersion () );
    assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
    assert ( f0 . fileSize () == 3 );
    assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
    assert ( f0 . fileSize () == 6 );
    assert ( f0 . seek ( 2 ));
    assert ( writeTest ( f0, { 5, 4 }, 2 ) );
    assert ( f0 . fileSize () == 6 );
    assert ( f0 . seek ( 1 ));
    assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));
    assert ( f0 . seek ( 3 ));
    f0 . addVersion();
    assert ( f0 . seek ( 6 ));
    assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );
    f0 . addVersion();
    assert ( f0 . seek ( 5 ));
    CFile f1 ( f0 );
    f0 . truncate ();
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
    assert ( f0 . undoVersion () );
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
    assert ( f0 . undoVersion () );
    assert ( f0 . seek ( 0 ));
    assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
    assert ( !f0 . seek ( 100 ));
    assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
    assert ( f1 . seek ( 0 ));
    assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
    assert ( f1 . undoVersion () );
    assert ( f1 . undoVersion () );
    assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
    assert ( !f1 . undoVersion () );

    cout << "Yes" << endl;
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
