#include "Processor.h"
#include <string>
using namespace std;


void sortMtxs(int idx1,int idx2, int idx3){
    int tmpi;
    if(idx1 > idx2){
        tmpi= idx1;
        idx1 = idx2;
        idx2 = tmpi;
    }
    if(idx1 > idx3){
        tmpi= idx1;
        idx1 = idx3;
        idx3 = tmpi;
        
    }
    if(idx2 > idx3){
        tmpi= idx3;
        idx3 = idx2;
        idx2 = tmpi;
    }
    cout << idx1 << " " << idx2 << " "<< idx3<< endl;
}
void sortMtxs(int idx1, int idx2){
    int tmpi;
    if(idx1 > idx2){
        tmpi= idx1;
        idx1 = idx2;
        idx2 = tmpi;
    }

    cout << idx1 << " " << idx2 << endl;
}
//Receiving the program to run as an argument.
//All heap allocations are destroyed by the end of the program. No memory leaks.
//All types of exceptions are handled. Please check README.md for more details.
int main(int argc, char *argv[]){
   /* try{
        int memory[1024];
    Proccessor Pr(memory);
    if(argc == 1) {
        cout << "Please specify the input program through the command line; read the README.md for more details" << endl;
        return 0;
    }
    Pr.loadInstMem(argv[1]);
    Pr.run();
    return 0;
    }catch(exception& exp){
        cout << exp.what() << endl;
        return 0;
    }*/
    int i, j,k;
    cin >> i >> j >> k;
    sortMtxs(i,j,k);

    cin >> i >> j;
    sortMtxs(i,j);
}