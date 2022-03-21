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
        unsigned int c_Balance = 0;

    };
public:
    vector<Company*> pointerVecId;
    vector<Company*> pointerVecNameAddr;
    vector<unsigned int>transactions;
    unsigned int pos = 0;

    void print (){
        for (int i = 0; i < pointerVecId.size(); i++){

            cout << "Name : " << pointerVecId[i]->c_Name << " Address: " << pointerVecId[i]->c_Address << " ID: " << pointerVecId[i]->c_ID << "Balance :" << pointerVecId[i]->c_Balance << endl;


        }
        printf("------------------------------------------------------------------------\n");
        for (int i = 0; i < pointerVecNameAddr.size(); i++){

            cout << "Name : " << pointerVecNameAddr[i]->c_Name << " Address: " << pointerVecNameAddr[i]->c_Address << " ID: " << pointerVecNameAddr[i]->c_ID << " Balance: " << pointerVecNameAddr[i]->c_Balance<<endl;


        }




    }


    bool  static cmpID(const Company * a,const string & b) {

        return a->c_ID < b ? true : false;
    }

    bool  static cmpName(const Company * a,const string & b) {

        return a->c_NAME < b ? true : false;
    }


    bool  static cmpAdr(const Company * a,const string & b) {

        return a->c_ADDRESS < b ? true : false;
    }
    auto findIndex (const string    & taxID)const{
        auto pos = lower_bound(pointerVecId.begin(),pointerVecId.end(), taxID, cmpID);
        if (pos == pointerVecId.end()) return pointerVecId.end();
        if ((*pos)->c_ID != taxID) return pointerVecId.end();

        return pos;




    }
    auto findIndex (const string    & name,
                    const string    & addr)const{
        string NAME = name;
        string ADDR = addr;

        transform(NAME.begin(), NAME.end(), NAME.begin(),::toupper);
        transform(ADDR.begin(), ADDR.end(), ADDR.begin(),::toupper);

        auto pos = lower_bound(pointerVecNameAddr.begin(),pointerVecNameAddr.end(), NAME, cmpName);
        if (pos == pointerVecNameAddr.end())return pointerVecNameAddr.end();
        if ((*pos)->c_NAME != NAME) return pointerVecNameAddr.end();

        auto pos1 = lower_bound(pos,pointerVecNameAddr.end(), ADDR, cmpAdr);
        if (pos1 == pointerVecNameAddr.end())return pointerVecNameAddr.end();
        if ((*pos1)->c_NAME != NAME or (*pos1)->c_ADDRESS != ADDR) return pointerVecNameAddr.end();

        return pos1;






    }
    void add (void ){
        pos++;
    }





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
            if (posID != pointerVecId.end()) {
                if ((*posID)->c_ID == taxID) return false;
            }

            posName = lower_bound(pointerVecNameAddr.begin(),pointerVecNameAddr.end(),NAME,cmpName);
            if (posName != pointerVecNameAddr.end()){
            if ((*posName)->c_NAME == NAME){
                auto end = posName;
                while ((*end)->c_NAME == NAME){
                    end++;
                    if (end == pointerVecNameAddr.end()) break;
                }
                auto tmp = posName;
                posName = lower_bound(tmp,end,ADDR,cmpAdr);
                if (posName != pointerVecNameAddr.end()) {
                    if ((*posName)->c_ADDRESS == ADDR) return false;
                }

            }

            }

        }
            Company * addNew = new Company;
            addNew->c_ID.append(taxID);
            addNew->c_Name.append(name);
            addNew->c_Address.append(addr);
            addNew->c_NAME.append(NAME);
            addNew->c_ADDRESS.append(ADDR);
            pointerVecId.insert(posID, addNew);
            pointerVecNameAddr.insert(posName, addNew);



        return true;
        }





        bool          cancelCompany  ( const string    & name,
                                   const string    & addr ){
            auto pos = findIndex(name,addr);
            if (pos == pointerVecNameAddr.end()) return false;
            pointerVecNameAddr.erase(pos);

            auto pos1 = findIndex((*pos)->c_ID);
            pointerVecId.erase(pos1);

            delete (*pos1);
            return true;



    }
    bool          cancelCompany  ( const string    & taxID ){
        auto pos = findIndex(taxID);
        if (pos == pointerVecId.end()) return false;

        pointerVecId.erase(pos);

        auto pos1 = findIndex((*pos)->c_Name, (*pos)->c_Address);
        pointerVecNameAddr.erase(pos1);

        delete (*pos1);
        return true;


    }
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount ){
        auto pos = findIndex(taxID);
        if (pos == pointerVecId.end()) return false;

        (*pos)->c_Balance += amount;
        transactions.push_back(amount);
        return true;

    }

    bool          invoice        ( const string    & name,
                                   const string    & addr,
                                   unsigned int      amount ){
       auto pos = findIndex(name,addr);
        if (pos == pointerVecNameAddr.end()) return false;
        (*pos)->c_Balance += amount;
        transactions.push_back(amount);
        return true;


    }
    bool          audit          ( const string    & name,
                                   const string    & addr,
                                   unsigned int    & sumIncome ) const{

        auto pos = findIndex(name,addr);
        if (pos == pointerVecNameAddr.end()) return false;

        sumIncome = (*pos)->c_Balance;
        return true;


    }

    bool          audit          ( const string    & taxID,
                                   unsigned int    & sumIncome ) const{
        auto pos = findIndex(taxID);
        if (pos == pointerVecId.end()) return false;

        sumIncome = (*pos)->c_Balance;
        return true;



    }
    bool          firstCompany   ( string          & name,
                                   string          & addr ) const{
        if (pointerVecNameAddr.empty()) return false;
            name = pointerVecNameAddr[0]->c_Name;
            addr = pointerVecNameAddr[0]->c_Address;

            return true;






    }
    bool          nextCompany    ( string          & name,
                                   string          & addr ) {
        add();
        if (pos >= pointerVecNameAddr.size()) return false;

        name = pointerVecNameAddr[pos]->c_Name;
        addr = pointerVecNameAddr[pos]->c_Address;
        return true;



    }
   unsigned int  medianInvoice  ( void ) const{
       if (transactions.empty()) return 0;
    vector<unsigned int> trCopy;
        for (auto i = 0; i < transactions.size(); i++){
            trCopy.push_back(transactions.at(i));

        }
    sort(trCopy.begin(),trCopy.end());
    int pos = trCopy.size()/2;


        return trCopy.at(pos);


    }

  private:




};



//#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;
  /*
    //cout << ("666/666" < "123456") << endl;
  CVATRegister b1;

    assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );




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
  b1.print();
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
  assert ( b1 . medianInvoice () == 2000 );/*
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
 // assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  //assert ( ! b1 . firstCompany ( name, addr ) );

*/
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

  return EXIT_SUCCESS;
}
//#endif /* __PROGTEST__ */
