#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CDate
{
    public:
        int xpYear;
        int xpMonth;
        int xpDay;
     
        CDate (const int & y,const int & m,const int & d ){
           xpYear = y;
           xpMonth = m;
           xpDay = d;
        }

        bool operator<(const CDate & a) const {
            return tie(xpYear,xpMonth,xpDay) < tie(a.xpYear,a.xpMonth,a.xpDay);
        }

        //Print out for debugging purposes
        friend ostream & operator<< (ostream & out, CDate const & a){
           out << " " << a.xpYear << "-"<< a.xpMonth << "-" << a.xpDay << " ";
           return out;
        }
    
};

struct cmpDate {
    bool operator()(const CDate & a, const CDate & b) const {
       return tie(a.xpYear,a.xpMonth,a.xpDay) < tie(b.xpYear,b.xpMonth,b.xpDay);
    }
};



class CSupermarket
{
  
    public:
  	    unordered_map<string, map<CDate,int,cmpDate>> inventory;

        CSupermarket(){
            inventory.max_load_factor(0.25);    
        }

        //Print out for debugging purposes
        friend ostream & operator <<(ostream & out, CSupermarket const & a){
            out << "-------------------------------------------------------" << endl;
            for (auto i: a.inventory){
                out << i.first << " contains: ";
                for (auto m: i.second){
                    out << m.first << " : ";
                    out << m.second << "   ";
                }
                out << endl;
            }
            out << "-------------------------------------------------------" << endl;
            out << "Size: " << a.inventory.size() << endl;
            out << "Bucket count: " << a.inventory.bucket_count() << endl;
            out << "-------------------------------------------------------" << endl;
            return out;

        }

        bool static cmpPair(const pair<string,int> & a, const int & b) {

            return a.second > b;
        }
    
        //Proud of this one :)
        //Using the brillant overloaded operator[] of hashmaps
        //Looks for an element with the key name, if absent, creates it and creates coresponding value of a new BST of ordered dates
        //If there, looks if an entry with the same date is present, if not, inserts it into the BST
        //if present (emplace failed and returned a pair with false in .second) adds to its count
        CSupermarket & store   ( const char * name, const CDate & expiryDate, const int & count ){

            if (!inventory[name].emplace(expiryDate, count).second) inventory[name][expiryDate]+=count;

            return *this;
         }

        //String compare method with one difference allowed, sizes have to match though
        bool strLetterCmp (const string & a, const string & b){
        
            if (a.size() != b.size()) return false;         
            int diffLetters = 0;            
            for (unsigned int i = 0; i < a.size(); i++){
                if (a[i] != b[i]) diffLetters++;
                if (diffLetters > 1) return false;

            }
            return true;
        } 
        //Lineary searches through the whole map looking for an entry with exactly one different letter
        //returns iterator pointing to .end() if none or more than one are found
        //if exactly one is found returns an iterator to it
        unordered_map<string, map<CDate, int, cmpDate>>::iterator isThere (const string & str){

            auto iterator = inventory.end();
            int matchCnt = 0;           
            for (auto i = inventory.begin(); i != inventory.end(); i++){

                if (strLetterCmp(str,(*i).first)){
                    matchCnt++;
                    if (matchCnt > 1) return inventory.end();
                    iterator = i;
                }         
            }
            return iterator;

        }    

        void sell    ( list<pair<string,int>> & shopList ){

            vector<list<pair<string,int>>::iterator> correctVec;
            vector<unordered_map<std::string, std::map<CDate, int, cmpDate>>::iterator> correctVecMapIter;

            //Goes through the whole shopping list beforehand to fulfill the "transaction like" requirement
            //and decides which items it can and cannot sell
            //If it can sell the item, saves its iterator for both the hashmap and the shopping list
            //Method later works only with the items from those two correct vectors
            for (auto i = shopList.begin(); i != shopList.end(); i++){
                auto f = inventory.find((*i).first);

                //exact key is not present
                if (f == inventory.end()){
                    f = isThere((*i).first);

                    if (f != inventory.end()){
                        correctVec.push_back(i);
                        correctVecMapIter.push_back(f);
                    }
                }
                //Key matches exactly
                else {
                    correctVec.push_back(i);
                    correctVecMapIter.push_back(f);
                }

            }

            int cnt = 0;

            vector<list<pair<string,int>>::iterator> deleteFromListVec;
            //Loops through both correct vectors and edits the quantities
            for (auto i = correctVec.begin(); i != correctVec.end(); i++){
                    auto m = correctVecMapIter[cnt];
                    //Until no more items are left or all requested were sold
                    while (!((*m).second.empty())){

                        //One specific date
                        auto j = (*m).second.begin();
                        //No more left with the current date
                        if ((*j).second < (*i)->second){
                            (*i)->second -= (*j).second;
                            (*m).second.erase(j);

                        }
                        //All requested sold
                        else if ((*j).second > (*i)->second){

                            (*j).second -= (*i)->second;
                            deleteFromListVec.push_back(*i);
                            break;

                        }
                        // Both
                        else {
                            (*m).second.erase(j);
                            deleteFromListVec.push_back(*i);
                            break;
                        }
                        //next date

                    }

                    if ((*m).second.empty()){
                        inventory.erase(m);
                    }
                    //next item
                    cnt++;

            }

            for (auto k: deleteFromListVec){
                shopList.erase(k);
            }
            return;

        }
        //Loops through the whole map and BSTs at each key 
        //Looks for items that expire before date X and saves them to a list
        //sorted by their descending quantity
        list<pair<string,int>> expired (const CDate & date ) const{

            list<pair<string,int>> lis;

            for (auto i = inventory.begin(); i != inventory.end(); ++i){
                int currCount = 0;

                for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j){
                    if ((*j).first < date){
                    currCount+= (*j).second;

                    }
                    else break;
                }
                if (currCount) lis.emplace_back((*i).first, currCount);

            }

            lis.sort([](auto const& a, auto const& b) {
                return a.second > b.second;
            });

            return lis;

        }
    
};
#ifndef __PROGTEST__
int main ( void )
{


  for (int i = 0; i < 1; i++) {
  CSupermarket s;
  s . store ( "bread", CDate ( 2016, 4, 30 ), 100 )
    . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
    . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
    . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
    . store ( "okey", CDate ( 2016, 7, 18 ), 5 );
  cout << s;
 
 
    
  
  list<pair<string,int> > l0 = s . expired ( CDate ( 2018, 4, 30 ) );
  assert ( l0 . size () == 4 );
  assert ( ( l0 == list<pair<string,int> > { { "bread", 200 }, { "beer", 50 }, { "butter", 10 }, { "okey", 5 } } ) );

  list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
  s . sell ( l1 );
  
  assert ( l1 . size () == 2 );
  assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );

  list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
  assert ( l2 . size () == 1 );
  assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );

  list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
  assert ( l3 . size () == 1 );
  assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );

  list<pair<string,int> > l4 { { "bread", 105 } };
  s . sell ( l4 );
  assert ( l4 . size () == 0 );
  assert ( ( l4 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l5 . size () == 3 );
  assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );

  s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );
  
  cout << s;
  list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
  s . sell ( l6 );
  cout << s;
  assert ( l6 . size () == 3 );
  assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );

  list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l7 . size () == 4 );
  assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );

  s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );

  list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
  s . sell ( l8 );
  assert ( l8 . size () == 2 );
  assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );

  list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l9 . size () == 5 );
  assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );
  cout << s;
  list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
  s . sell ( l10 );
  cout << s;
  assert ( l10 . size () == 2 );
  assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );

  list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l11 . size () == 4 );
  assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );
  cout << s;
  list<pair<string,int> > l12 { { "Cake", 4 } };
  s . sell ( l12 );
  cout << s;
  
  assert ( l12 . size () == 0 );
  assert ( ( l12 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l13 . size () == 4 );
  assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );

  list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
  s . sell ( l14 );
  assert ( l14 . size () == 1 );
  assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );

  s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
    . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
    . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );

  list<pair<string,int> > l15 { { "ccccc", 10 } };
  s . sell ( l15 );
  assert ( l15 . size () == 1 );
  assert ( ( l15 == list<pair<string,int> > { { "ccccc", 10 } } ) );
  s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
    . store ( "ccccdfsddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "dccfdgcc", CDate ( 2019, 2, 14 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "cc5rddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "cccfsddfscdsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccad", CDate ( 2019, 6, 9 ), 100 ). store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccfdsccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccdsdadsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "cccddssacddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccfdccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccasdddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccdassddsad", CDate ( 2019, 6, 9 ), 100 ). store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccdsdasdaddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccsdddsad", CDate ( 2019, 6, 9 ), 100 )

    . store ( "ccccdsaddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccsdadsasdddsad", CDate ( 2019, 6, 9 ), 100 )

    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccdsaddsad", CDate ( 2019,4, 9 ), 100 )
    . store ( "ccccdddsasad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2059, 7, 9 ), 100 )
    . store ( "cccdsasdcddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2059, 6, 9 ), 100 )
    . store ( "ccccddsadsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccdasddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2079, 6, 9 ), 100 )
    . store ( "ccccdasddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddssdaddsad", CDate ( 2019, 6, 9 ), 100 )
    . store ( "ccccddsad", CDate ( 2019, 6, 9 ), 100 );
    for (int k = 0; k < 1; k++){
    s . expired ( CDate ( 28000, 4, 30 ) );
    }


  }
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
