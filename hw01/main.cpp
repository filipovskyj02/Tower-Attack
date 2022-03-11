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



    int readChunks(int & index,vector<int>& array){
        int bitsTotal = 0;
        if (array.at(index) == 1){
            index++;
            bitsTotal += 4096;
        }
        index += 1;
         bitsTotal += read8or12(index,array,12);
        printf("bits total: %d\n", bitsTotal);
        return bitsTotal;

    }

    int readLetter (int & index,vector<int>& array, Cnode * position){

        if (position->m_Val != '0') {
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
        int bitsTotal;
        int i = 0;
        createTree(i,array, head);
        printf("skoncil sem na indexu :%d na cisle >%d<\n", i, array.at(i));
        bitsTotal = readChunks(i, array);
        decode(i,array,bitsTotal);


    }

    int read8or12 (int & index,vector<int>& array, int bits){
        int total = 0;
        bits--;
        for (int pow = bits; pow >= 0; pow--){
            if (array.at(index) == 1){
                if (bits == 11) { printf("precetl sem 1\n");}
                total += twoPow(pow);
            }
            if (bits == 11 && array.at(index)== 0) { printf("precetl sem 0\n");}
            index++;

        }
        return total;
    }

    void createTree (int & index,vector<int>& array, Cnode * current){
        //Creates root and saves it
        if (current == nullptr){
            auto * newHead = new Cnode;
            current = newHead;
            head = newHead;

        }
        if (array.at(index) == 0){
            current->m_Val = '0';
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

    void print(Cnode * head){
        if (!head->m_Right and !head->m_Left)return;

        else {
            printf("Hodnota : %d",head->m_Val);
            print(head->m_Left);
            print(head->m_Right);
        }
    }
    int _print_t(Cnode *tree, int is_left, int offset, int depth, char s[20][255])
    {
        char b[20];
        int width = 5;

        if (!tree) return 0;

        sprintf(b, "(%03c)", tree->m_Val);

        int left  = _print_t(tree->m_Left,  1, offset,                depth + 1, s);
        int right = _print_t(tree->m_Right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
        for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
        for (int i = 0; i < width; i++)
            s[2 * depth][offset + left + i] = b[i];

        if (depth && is_left) {

            for (int i = 0; i < width + right; i++)
                s[2 * depth - 1][offset + left + width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset + left + width + right + width/2] = '+';

        } else if (depth && !is_left) {

            for (int i = 0; i < left + width; i++)
                s[2 * depth - 1][offset - width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset - width/2 - 1] = '+';
        }
#endif

        return left + width + right;
    }

    void print_t(Cnode *tree) {
        char s[20][255];
        for (int i = 0; i < 20; i++)
            sprintf(s[i], "%80s", " ");

        _print_t(tree, 0, 0, 0, s);

        for (int i = 0; i < 20; i++)
            printf("%s\n", s[i]);
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
