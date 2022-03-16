#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

int twoPow (int pow){
    int n = 1;
    for (int i = 0; i < pow; i++){
        n *= 2;
    }
    return n;

}
struct CTree {
    struct Cnode {
        string UTF8;
        char m_Val;
        Cnode * m_Left = nullptr;
        Cnode * m_Right = nullptr;

    };
    Cnode * head = nullptr;


    void deleteTree(Cnode * position){
        if (position == nullptr) return;

        deleteTree(position->m_Left);
        deleteTree(position->m_Right);
        delete position;

    }
    int readChunks(int & index,vector<bool>& array,int & CharactersTotal ){
        if (array.at(index) == 1){
            CharactersTotal = 4096;
            index++;

            return 1;

        }
        else if (array.at(index) == 0){
            index++;

            CharactersTotal = read8or12(index,array,12);
            return 0;
        }

        return -1;
    }

    string readLetter (int & index,vector<bool>& array, Cnode * position, int & streamSize){


        if(position == nullptr){
            streamSize = -1;
            return "";
        }

        while (position->UTF8.compare("150"s)==0){
            if (array.at(index) == 0){
                index++;
                position = position->m_Left;
            }
            else{
                index++;
                position = position->m_Right;

            }

        }
        return position->UTF8;






    }
    bool decode (int & index,vector<bool>& array,int bitsTotal,ofstream & output){
        int streamSize = array.size();
        string c;

        for (int i = 0; i < bitsTotal; i++) {
            if (index == streamSize) return false;
            c = readLetter(index, array, head,streamSize);
            if (streamSize == -1) return false;

            output << c;
            if (output.fail()) return false;
        }
        return true;
    }


    bool readInput (vector<bool>& array, ofstream & file){
        int size = array.size();
        int index = 0;
        int CharacterTotal = 0;
        int fail = 0;

        createTree(index,array, head,fail,size);

        if (fail > 0 )return false;

        while (readChunks(index, array,CharacterTotal)==1){
            if (decode(index,array,CharacterTotal,file)== false) {
                return false;
            }

        }
        if (index < size - 1){
            if (decode(index,array,CharacterTotal,file)== false) {

                return false;
            }


        }
        return true;

    }

    int read8or12 (int & index,vector<bool>& array, int bits){
        int total = 0;
        bits--;
        for (int pow = bits; pow >= 0; pow--){
            if (array.at(index) == 1){

                total += twoPow(pow);
            }
            index++;

        }
        return total;
    }

    void createTree (int & index,vector<bool>& array, Cnode * current, int & fail, int & size){
        if (current == nullptr){
            auto * newHead = new Cnode;
            current = newHead;
            head = newHead;

        }
        if (index +1 >= size) {fail++;return;}
        if (array.at(index) == 0){
            current->UTF8 = "150"s;
            index++;
            current->m_Left = new Cnode;
            current->m_Right = new Cnode;
            createTree(index,array,current->m_Left,fail,size);
            createTree(index,array,current->m_Right,fail,size);

        }
        else if (array.at(index) == 1){


            index++;
            char c = read8or12(index,array,8);
            current->UTF8.push_back(c);


        }

    }


};

bool decompressFile ( const char * inFileName, const char * outFileName )
{
    ifstream in (inFileName, ios::in | ios::binary);
    ofstream myfile;
    myfile.open (outFileName);
    if (!in.good()) return false;
    char c;
    vector<bool> array;
    while (in.get(c))
    {
        for (int i = 7; i >= 0; i--)
            array.push_back(((c >> i) & 1));
    }

    CTree a;
    if (a.readInput(array,myfile)== false) {
        a.deleteTree(a.head);
        return false;
    }

    a.deleteTree(a.head);
    return true;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
    // keep this dummy implementation (no bonus) or implement the compression (bonus)
    return false;
}
#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
    // todo
    return false;
}

int main ( void )
{
    assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
    //assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
   // assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
   // assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
    //assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
    //assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );

    //assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );

/*

    assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );

    assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
    assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );

*/
    return 0;
}
#endif /* __PROGTEST__ */