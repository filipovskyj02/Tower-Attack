#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int twoPow (int pow){
    int n = 1;
    for (int i = 0; i < pow; i++){
        n *= 2;
    }
    return n;

}
struct CTree {
    struct Cnode {
        int m_Val;
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
    int readChunks(int & index,vector<int>& array,int & CharactersTotal ){
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


    }

    int readLetter (int & index,vector<int>& array, Cnode * position){
        if(position == nullptr)return 0;
        if (position->m_Val != 150) {
            int Letter = position->m_Val;
            return Letter;
        }

         if (array.at(index)==0) {

            index++;
            readLetter(index,array,position->m_Left);
            }
         else if (array.at(index)==1) {

            index++;
            readLetter(index,array,position->m_Right);
        }


    }
    void decode (int & index,vector<int>& array,int bitsTotal,ofstream & output){




            int c;

            for (int i = 0; i < bitsTotal; i++) {
                c = readLetter(index, array, head);

                output << static_cast<char>(c);
            }
    }


    void readInput (vector<int>& array, ofstream & file){
        int size = array.size();
        int index = 0;
        int CharacterTotal = 0;
        createTree(index,array, head);

        while (readChunks(index, array,CharacterTotal)==1){
            decode(index,array,CharacterTotal,file);

        }
        if (index < size - 1){
            decode(index,array,CharacterTotal,file);


        }

    }

    int read8or12 (int & index,vector<int>& array, int bits){
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

    void createTree (int & index,vector<int>& array, Cnode * current){
        if (current == nullptr){
            auto * newHead = new Cnode;
            current = newHead;
            head = newHead;

        }
        if (array.at(index) == 0){
            current->m_Val = 150;
            index++;
            current->m_Left = new Cnode;
            current->m_Right = new Cnode;
            createTree(index,array,current->m_Left);
            createTree(index,array,current->m_Right);

        }
        else if (array.at(index) == 1){


            index++;
            current->m_Val = read8or12(index,array,8);


        }

    }


};



int main() {
    ifstream in ("test5.huf", ios::in | ios::binary);
    ofstream myfile;
    myfile.open ("output5.txt");

    char c;
    vector<int> array;
    while (in.get(c))
    {
        for (int i = 7; i >= 0; i--)
            array.push_back(((c >> i) & 1));
    }



    CTree a;
    a.readInput(array,myfile);
    a.deleteTree(a.head);








}
