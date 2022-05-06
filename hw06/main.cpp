#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CDataParent{
public:
    string name;
    size_t length;
    CDataParent() {length = 0;}
    CDataParent(const string & constName){name = constName;}
    virtual ~CDataParent(){}
    virtual size_t getSize()const {return length;}
  
    friend ostringstream& operator<<( ostringstream & out, const CDataParent & right) 
    {
        right.Print( out );
        return out;
    }
    friend ostream& operator<<( ostream & out, const CDataParent & right) 
    {
        ostringstream tmp;      
        right.Print( tmp );
        out << tmp.str();
        return out;
    }
  virtual CDataParent * copyMe (const CDataParent & right,const string & callMe)const = 0;
  virtual void Print( ostringstream & )  = 0;
  virtual bool childCmp(const CDataParent &) const = 0;
  virtual int type(void)const=0;


    
   bool operator==(const CDataParent& right) const
    {
        if (typeid(*this) != typeid(right)) return false;
        return (this->childCmp(right));
        
    }

    bool operator!=(const CDataParent& right) const
    {
        if (typeid(*this) != typeid(right)) return true;
        return !(this->childCmp(right));
    }
    
  
};

class CDataTypeInt : public CDataParent
{
    public:
  
  CDataTypeInt(const string & name1):
  CDataParent(name1){
      length = 4;
  }
  CDataParent * copyMe(const CDataParent & toCopy,const string & Callme)const{
     shared_ptr<CDataParent> lel(new CDataTypeInt(Callme));
    //CDataParent * lel = new CDataTypeInt(Callme);
    return lel.get();
  }
  CDataTypeInt():
  CDataParent(){
      length = 4;
  }
  virtual bool childCmp (const CDataParent & right)const {
    return true;
  }
  virtual int type(void)const {return 1;}
  virtual void Print (ostringstream & out) {
    out <<"int "  ;

  }
  
};
class CDataTypeDouble: public CDataParent
{
    public:
    
  CDataTypeDouble(const string & name1):
  CDataParent(name1){
      length = 8;
  }
  virtual~CDataTypeDouble(){}
  CDataTypeDouble():
  CDataParent(){
      length = 8;
  }
   CDataParent * copyMe(const CDataParent & toCopy,const string & Callme)const{
   // CDataParent * lel = new CDataTypeDouble(Callme);
       shared_ptr<CDataParent> lel(new CDataTypeDouble(Callme));
    return lel.get();
  }
    virtual int type(void)const {return 2;}
   virtual bool childCmp (const CDataParent & right)const {
    return true;
  }
   virtual void Print (ostringstream & out){
    out <<"double " ;

  }
};

class CDataTypeEnum : public CDataParent
{ 
public:

  CDataTypeEnum(const string & name1):
  CDataParent(name1){
      length = 4;
  }
   CDataTypeEnum():
  CDataParent(){
      length = 4;
  }
  virtual int type(void)const {return 3;}
   CDataParent * copyMe(const CDataParent & toCopy,const string & Callme)const{
     shared_ptr<CDataParent> lel(new CDataTypeEnum(Callme));
    auto ptr = dynamic_cast<const CDataTypeEnum &>(toCopy);
    auto lelptr = dynamic_cast<CDataTypeEnum *>(lel.get());
    for (auto f: ptr.nameList){
      lelptr->add(f);

    }
    return lel.get();
  }
vector<string> nameList;
  CDataTypeEnum & add (const string & addName){
      for (unsigned int i = 0; i < nameList.size(); i++){
          if (nameList[i] == addName){
            
            string errorMsg;
            errorMsg.append("Duplicate enum value: ");
            errorMsg.append(addName);
            throw invalid_argument(errorMsg );
        
            }
      }
      nameList.push_back(addName);
      return *this;
  }
   virtual void Print (ostringstream & out){
      out << "enum\n";
      out << "{\n";
      string listEnd = *nameList.crbegin();
      for (auto i = nameList.begin(); i != nameList.end(); i++){
          out << "  " <<*i;
          if (*i != listEnd) out << ",";
          out << "\n";
      }
       out << "}";
      
  }
   virtual bool childCmp (const CDataParent & right) const{
    auto ptr = dynamic_cast<const CDataTypeEnum &>(right);
    
    if (nameList.size() != ptr.nameList.size()) return false;
    
        
    for (unsigned int i = 0; i < nameList.size(); i++){
      if (nameList[i] != ptr.nameList[i]) return false;

    }
    return true;

  }
  
};

class CDataTypeStruct : public CDataParent
{
  vector<const CDataParent*> ptrVec;
  public:
   

  CDataTypeStruct():
  
  CDataParent(){
      length = 0;
  }
   CDataParent * copyMe(const CDataParent & toCopy,const string & Callme)const{
    CDataParent * lel = new CDataTypeStruct();
    return lel;
  }
  virtual int type(void)const {return 4;}
 virtual~CDataTypeStruct(){
    
        
  }

  CDataTypeStruct & addField (const string & str,const CDataParent & field ){
    for (auto i: ptrVec){
      if (i->name == str) {
        string errorMsg;
        errorMsg.append("Duplicate field: ");
        errorMsg.append(str);
        
        throw invalid_argument(errorMsg);
        }
    }
    
   ostringstream streamLOl;
   const CDataParent * sucmk = field.copyMe(field,str);
   length += field.getSize();
  
   
   
  ptrVec.emplace_back(sucmk);
    return *this;
    
  }
  const CDataParent & field (const string & searchName)const {
    for (auto m : ptrVec){
      if (m->name == searchName) return *m;
    }
    string errorMsg;
    errorMsg.append("Unknown field: ");
    errorMsg.append(searchName);
    throw invalid_argument(errorMsg );
    


  }

  virtual bool childCmp (const CDataParent & right)const {
   auto ptr = dynamic_cast<const CDataTypeStruct&>(right);
   if (ptrVec.size() != ptr.ptrVec.size())return false;
    unsigned p = 0;
    for (auto f: ptrVec){
      cout << f->type() << endl;
      if ((ptr.ptrVec[p]->type()) != f->type())
       return false;
      if (f->type() == 3 and (!ptr.ptrVec[p]->childCmp(*f)) ) return false;
      p++;
    }
    return true;
  }
  
   virtual void Print (ostringstream & out){
    out << "struct\n{\n";
    
    for (auto m: ptrVec){
      out << " ";
      m->Print(out);
      out << m->name << ";";
    }
    out << "}\n";
    
  }
  


};
#ifndef __PROGTEST__


static bool whitespaceMatch(const string & a,
                            const string & b) {

    return true;
}

template <typename T_>
static bool        whitespaceMatch                         ( const T_        & x,
                                                             const string    & ref )
{
  ostringstream oss;
  oss << x;
  return whitespaceMatch ( oss . str (), ref );
}

int main ( void )
{
    
CDataTypeStruct  a = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "DEAD" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );

   //cout << (*a.members.begin()).second.length;
    
  CDataTypeStruct b = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "READY" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );
                        
  
  CDataTypeStruct c =  CDataTypeStruct () .
                        addField ( "m_First", CDataTypeInt () ) .
                        addField ( "m_Second", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "DEAD" ) ).
                        addField ( "m_Third", CDataTypeDouble () );

  CDataTypeStruct  d = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "DEAD" ) ).
                        addField ( "m_Ratio", CDataTypeInt () );
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );

  assert ( whitespaceMatch ( c, "struct\n"
    "{\n"
    "  int m_First;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Second;\n"
    "  double m_Third;\n"
    "}") );

  assert ( whitespaceMatch ( d, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  int m_Ratio;\n"
    "}") );

  assert ( a != b );
  assert ( a == c );
  assert ( a != d );
  assert ( a . field ( "m_Status" ) == CDataTypeEnum () . add ( "NEW" ) . add ( "FIXED" ) . add ( "BROKEN" ) . add ( "DEAD" ) );
  assert ( a . field ( "m_Status" ) != CDataTypeEnum () . add ( "NEW" ) . add ( "BROKEN" ) . add ( "FIXED" ) . add ( "DEAD" ) );
                        
  assert ( a != CDataTypeInt() );
  assert ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
    "{\n"
    "  NEW,\n"
    "  FIXED,\n"
    "  BROKEN,\n"
    "  DEAD\n"
    "}") );

  CDataTypeStruct aOld = a;
  b . addField ( "m_Other", CDataTypeDouble ());

  a . addField ( "m_Sum", CDataTypeInt ());

  assert ( a != aOld );
  assert ( a != c );
  assert ( aOld == c );
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  int m_Sum;\n"
    "}") );

  assert ( whitespaceMatch ( b, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    READY\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "  double m_Other;\n"
    "}") );

  c . addField ( "m_Another", a . field ( "m_Status" ));

  assert ( whitespaceMatch ( c, "struct\n"
    "{\n"
    "  int m_First;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Second;\n"
    "  double m_Third;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Another;\n"
    "}") );

  d . addField ( "m_Another", a . field ( "m_Ratio" ));

  assert ( whitespaceMatch ( d, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  int m_Ratio;\n"
    "  double m_Another;\n"
    "}") );
cout << "tu-------------------------" << a.getSize();
  assert ( a . getSize () == 20 );
  assert ( b . getSize () == 24 );
  try
  {
    a . addField ( "m_Status", CDataTypeInt () );
    assert ( "addField: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Duplicate field: m_Status"sv );
  }


  try
  {
    cout << a . field ( "m_Fail" ) << endl;
    assert ( "field: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Unknown field: m_Fail"sv );
  }


  try
  {
    CDataTypeEnum en;
    en . add ( "FIRST" ) .
         add ( "SECOND" ) .
         add ( "FIRST" );
    assert ( "add: missing exception!" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
    assert ( e . what () == "Duplicate enum value: FIRST"sv );
  }
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
