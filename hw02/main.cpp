//#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
//#endif /* __PROGTEST__ */

class CVATRegister
{

    struct Company {
        string c_Name;
        string c_Address;
        string c_ID;
        string c_NAME;
        string c_ADDRESS;
        int c_Balance = 0;

    };
public:
    vector<Company*> pointerVecId;
    vector<Company*> pointerVecNameAddr;

    void print (){
        for (int i = 0; i < pointerVecId.size(); i++){

            cout << "Name : " << pointerVecId[i]->c_Name << " Address: " << pointerVecId[i]->c_Address << " ID: " << pointerVecId[i]->c_ID << endl;


        }



    }


    bool  static cmpID(const Company * a,const string & b) {

        return a->c_ID < b ? true : false;
    }
    bool  static cmpName(const Company * a,const string & b) {

        return a->c_Name < b ? true : false;
    }


    bool  static cmpAdr(const Company * a,const string & b) {

        return a->c_Address < b ? true : false;
    }




                  CVATRegister   ( void );
                  ~CVATRegister  ( void );


    bool          newCompany     ( const string    & name,
                                   const string    & addr,
                                   const string    & taxID ){

        string NAME = name;
        string ADDR = addr;

        transform(NAME.begin(), NAME.end(), NAME.begin(),::toupper);
        transform(ADDR.begin(), ADDR.end(), ADDR.begin(),::toupper);


        auto posID = pointerVecId.begin();
        auto posName = pointerVecNameAddr.begin();
        if (!pointerVecId.empty()) {
            posID = lower_bound(pointerVecId.begin(), pointerVecId.end(), taxID, cmpID);
            if ((*posID)->c_ID == taxID) return false;

            posName = lower_bound(pointerVecNameAddr.begin(),pointerVecNameAddr.end(),name,cmpName);
            if ((*posName)->c_Name == name){
                auto end = posName;
                while ((*posName)->c_Name == name){end++;}
                auto tmp = posName;
                posName = lower_bound(tmp,end,addr,cmpAdr);

                if ((*posName)->c_ADDRESS == addr) return false;

            }

        }
            Company * addNew = new Company;
            addNew->c_ID.append(taxID);
            addNew->c_Name.append(name);
            addNew->c_Address.append(addr);
            addNew->c_NAME = NAME;
            addNew->c_ADDRESS = ADDR;
            pointerVecId.insert(posID, addNew);
            pointerVecNameAddr.insert(posName, addNew);



        return true;
        }





        bool          cancelCompany  ( const string    & name,
                                   const string    & addr );
    bool          cancelCompany  ( const string    & taxID ){

    }
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount );
    bool          invoice        ( const string    & name,
                                   const string    & addr,
                                   unsigned int      amount );
    bool          audit          ( const string    & name,
                                   const string    & addr,
                                   unsigned int    & sumIncome ) const;
    bool          audit          ( const string    & taxID,
                                   unsigned int    & sumIncome ) const;
    bool          firstCompany   ( string          & name,
                                   string          & addr ) const;
    bool          nextCompany    ( string          & name,
                                   string          & addr ) const;
    unsigned int  medianInvoice  ( void ) const;
  private:




};




//#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;
    //cout << ("666/666" < "123456") << endl;
  CVATRegister b1;
    assert ( b1 . newCompany ( "ACME1", "Kolejni1", "666/666/666/666" ) );
    assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );

  b1.print();
  /*
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

    printf("\n");
  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  b2.print();

  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );
*/
  return EXIT_SUCCESS;
}
//#endif /* __PROGTEST__ */
