#ifndef __PROGTEST__
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
#endif /* __PROGTEST__ */

class CVATRegister
{

    struct Company {
        string c_Name;
        string c_Address;
        string c_ID;
        pair<string, string> c_Both;
        unsigned int c_Balance = 0;

    };
public:
    bool mezniflag = false;
    vector<Company*> pointerVecId;
    vector<Company*> pointerVecNameAddr;
    CVATRegister(void){

    }

    ~CVATRegister(void){

        for  (auto it = begin(pointerVecId); it != end(pointerVecId); it++){
            delete (*it);
        }


    }



    vector<unsigned int>transactions;
    unsigned int pos = 0;



    void print (){
        for (long unsigned int i = 0; i < pointerVecId.size(); i++){

            cout << "Name : " << pointerVecId[i]->c_Name << " Address: " << pointerVecId[i]->c_Address << " ID: " << pointerVecId[i]->c_ID << " Balance :" << pointerVecId[i]->c_Balance << endl;


        }
        printf("------------------------------------------------------------------------\n");
        for (long unsigned int i = 0; i < pointerVecNameAddr.size(); i++){

            cout << "Name : " << pointerVecNameAddr[i]->c_Name << " Address: " << pointerVecNameAddr[i]->c_Address << " ID: " << pointerVecNameAddr[i]->c_ID << " Balance: " << pointerVecNameAddr[i]->c_Balance<<endl;


        }
        printf("***************************************************************************\n");




    }



    bool  static cmpID(const Company * a,const string & b) {

        return a->c_ID < b ? true : false;
    }

    bool  static cmpName(const Company * a,const pair<string,string> & b) {

        return a->c_Both < b ? true : false;
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
        pair<string,string> bothpair;
        bothpair.first = NAME;
        bothpair.second = ADDR;

        auto pos = lower_bound(pointerVecNameAddr.begin(),pointerVecNameAddr.end(), bothpair, cmpName);
        if (pos == pointerVecNameAddr.end()) return pointerVecNameAddr.end();
        if ((*pos)->c_Both != bothpair) return pointerVecNameAddr.end();





        return pos;







    }


    bool          newCompany     ( const string    & name,
                                   const string    & addr,
                                   const string    & taxID ){

        string NAME = name;
        string ADDR = addr;
        transform(NAME.begin(), NAME.end(), NAME.begin(),::toupper);
        transform(ADDR.begin(), ADDR.end(), ADDR.begin(),::toupper);
        pair<string,string> bothpair;
        bothpair.first = NAME;
        bothpair.second = ADDR;






        auto posID = pointerVecId.begin();
        auto posName = pointerVecNameAddr.begin();
        if (!pointerVecId.empty() and !pointerVecNameAddr.empty()) {
            posID = lower_bound(pointerVecId.begin(), pointerVecId.end(), taxID, cmpID);
            if (posID != pointerVecId.end()) {
                if ((*posID)->c_ID == taxID) return false;
            }
            posName = lower_bound(pointerVecNameAddr.begin(),pointerVecNameAddr.end(),bothpair,cmpName);
            if(posName != pointerVecNameAddr.end()){
                if ((*posName)->c_Both == bothpair) return false;


            }



        }
        Company * addNew = new Company;
        addNew->c_ID.append(taxID);
        addNew->c_Name.append(name);
        addNew->c_Address.append(addr);
        addNew->c_Both = bothpair;
        pointerVecId.insert(posID, addNew);
        pointerVecNameAddr.insert(posName, addNew);

        return true;
    }





    bool          cancelCompany  ( const string    & name,
                                   const string    & addr ){
        Company * comp;
        auto pos = findIndex(name,addr);
        if (pos == pointerVecNameAddr.end()) return false;

        string ID = (*pos)->c_ID;
        comp = (*pos);

        auto pos1 = findIndex(ID);

        pointerVecNameAddr.erase(pos);
        pointerVecId.erase(pos1);

        if (comp != nullptr) delete comp;
        return true;


    }
    bool          cancelCompany  ( const string    & taxID ){
        Company * comp;
        auto pos = findIndex(taxID);
        if (pos == pointerVecId.end()) return false;
        string name = (*pos)->c_Name;
        string address = (*pos)->c_Address;
        comp = (*pos);

        auto pos1 = findIndex(name,address);

        pointerVecId.erase(pos);
        pointerVecNameAddr.erase(pos1);

        if (comp != nullptr) delete comp;
        return true;


    }


    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount ){


            auto pos = findIndex(taxID);
            if (pos == pointerVecId.end()) return false;


            (*pos)->c_Balance += amount;

            auto posTr = lower_bound(transactions.begin(), transactions.end(), amount);
            transactions.insert(posTr, amount);
            return true;

    }

    bool          invoice        ( const string    & name,

                                   const string    & addr,
                                   unsigned int      amount ){



        auto pos = findIndex(name,addr);
        if (pos == pointerVecNameAddr.end()) return false;
       
        (*pos)->c_Balance += amount;

        auto posTr = lower_bound(transactions.begin(),transactions.end(),amount);
        transactions.insert(posTr,amount);
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
                                   string          & addr ) const {
        auto pos = findIndex(name,addr);
        if (pos == pointerVecNameAddr.end()) return false;
        pos++;
        if (pos == pointerVecNameAddr.end()) return false;
        name = (*pos)->c_Name;
        addr = (*pos)->c_Address;
        return true;



    }
    unsigned int  medianInvoice  ( void ) const{
        if (transactions.empty()) return 0;
        if (transactions.size()==1) return transactions.at(0);

        unsigned int pos = transactions.size();
        return transactions.at(pos/2);


    }

private:




};


#ifndef __PROGTEST__
int               main           ( void )
{
    string name, addr;
    unsigned int sumIncome;

    CVATRegister b1,b0,b8,b5,b4;

    CVATRegister b3;


    assert ( b5 . newCompany ( "c", "ccc", "1" ) );
    assert ( !b5 .cancelCompany("cc","cc") );
    assert ( b0 . newCompany ( "c", "cccccccccccccccccccccccccccccccc", "1" ) );
    assert ( b0 . newCompany ( "cc", "ccccccccccccccccccccccccccccccc", "12" ) );
    assert ( b0 . newCompany ( "ccc", "cccccccccccccccccccccccccccccc", "13" ) );
    assert ( b0 . newCompany ( "cccc", "ccccccccccccccccccccccccccccc", "135" ) );
    assert(b0.invoice("c", "cccccccccccccccccccccccccccccccc",3500));
    assert ( b0 . audit ( "1", sumIncome ) && sumIncome == 3500 );
    assert(b0.invoice("cc", "ccccccccccccccccccccccccccccccc",35000));
    assert(b0.invoice("cc", "ccccccccccccccccccccccccccccccc",35000));
    assert(b0.invoice("cc", "ccccccccccccccccccccccccccccccc",35000));
    assert(b0.invoice("cc", "ccccccccccccccccccccccccccccccc",35000));
    assert ( b0 . audit ( "12", sumIncome ) && sumIncome == 140000 );
    assert(b0.invoice("ccc", "cccccccccccccccccccccccccccccc",35));
    assert(b0.invoice("ccc", "cccccccccccccccccccccccccccccc",35));
    assert(b0.invoice("ccc", "cccccccccccccccccccccccccccccc",35000));
    assert(b0.invoice("ccc", "cccccccccccccccccccccccccccccc",35000));
    assert ( b0 . audit ("ccc", "cccccccccccccccccccccccccccccc", sumIncome ) && sumIncome == 70070 );
    assert(!b0.cancelCompany("ccccc", "cccccccccccccccccccccccccccc"));
    assert(b0.cancelCompany("c", "cccccccccccccccccccccccccccccccc"));
    assert ( b0 .cancelCompany( "cc", "ccccccccccccccccccccccccccccccc" ) );
    assert ( b0 .cancelCompany( "ccc", "cccccccccccccccccccccccccccccc" ) );
    assert ( b0 .cancelCompany( "cccc", "ccccccccccccccccccccccccccccc" ) );
    assert ( !b0 . audit ( "1", sumIncome ) );
    assert(!b0.invoice("cc", "ccccccccccccccccccccccccccccccc",35000));





    assert ( b8 . medianInvoice () == 0 );
    assert ( !b8 . invoice ( "666/666", 2000 ) );
    assert ( !b8 . firstCompany ( name, addr ) );
    assert ( !b8 . nextCompany( name, addr ) );
    assert ( !b8 . cancelCompany ( "666/666" ) );
    assert ( b8 . medianInvoice () == 0 );
    assert ( !b8 . nextCompany( name, addr ) );
    assert ( b8 . newCompany ( "", "", "666" ) );
    assert ( !b8 . invoice ( "666/666", 2000 ) );
    assert ( b8 . invoice ( "666", 2000 ) );
    assert ( b8 . medianInvoice () == 2000 );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . medianInvoice () == 2000 );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( !b8 . invoice ( " ", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . invoice ( "", "", 2000 ) );
    assert ( b8 . medianInvoice () == 2000 );
    name = "";
    addr = "";
    assert(!b8.nextCompany(name,addr));
    assert(b8.firstCompany(name,addr));
    assert ( b8 . medianInvoice () == 2000 );




    assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
    assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
    assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
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


    CVATRegister b2;
    assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
    assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
    assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
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
#endif /* __PROGTEST__ */