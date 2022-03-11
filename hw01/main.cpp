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
        Cnode * m_Left;
        Cnode * m_Right;

    };
    Cnode * head = nullptr;

    int readChunks(int & index,vector<int>& array,int & CharactersTotal ){
        if (array.at(index) == 1){
            CharactersTotal = 4096;
            index++;
            printf("+4096\n");
            return 1;

        }
        else if (array.at(index) == 0){
            index++;
            printf("+smaller\n");
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
             //printf("Going left\n");
            index++;
            readLetter(index,array,position->m_Left);
            }
         else if (array.at(index)==1) {
             //printf("Going right\n");
            index++;
            readLetter(index,array,position->m_Right);
        }


    }
    void decode (int & index,vector<int>& array,int bitsTotal){

            int c;
            printf("\n");
            for (int i = 0; i < bitsTotal; i++) {
                c = readLetter(index, array, head);
                printf("%c", c);

            }
        printf("\n");




    }


    void readInput (vector<int>& array){
        int size = array.size();
        int index = 0;
        int CharacterTotal = 0;
        createTree(index,array, head);

        while (readChunks(index, array,CharacterTotal)==1){
            decode(index,array,CharacterTotal);

        }
        if (index < size - 1){
            decode(index,array,CharacterTotal);


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

            printf("jednicka reached index : %d\n", index);
            index++;
            current->m_Val = read8or12(index,array,8);
            //index +=9;

        }

    }


};



int main() {
    ifstream in ("test1.huf", ios::in | ios::binary);

    char c;
    vector<int> array;
    while (in.get(c))
    {
        for (int i = 7; i >= 0; i--)
            array.push_back(((c >> i) & 1));
    }

   /* while(in.get(c)) {
        if (c != '0' and c != '1' and c != ' ') {
            //cout << "Error reading" << "c: << "  << ">>" << c << endl;
        } else {
            if (c == '0' or c == '1') {
                int m = c - '0';
                array.push_back(m);
            }
        }
    }
    */
    /*for (auto i: array)
        std::cout << i << ' ';*/

    cout << "\n"<<"velikost:" << array.size() << endl;

    CTree a;
    //make tree
    a.readInput(array);
    //a.print_t(a.head);







}
