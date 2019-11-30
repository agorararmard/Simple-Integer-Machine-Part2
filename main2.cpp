#include "nSIM.h"
#include <string>
using namespace std;


//Receiving the program to run as an argument.
//All heap allocations are destroyed by the end of the program. No memory leaks.
//All types of exceptions are handled. Please check README.md for more details.
int main(int argc, char *argv[]){
    try{
        nSIM Pr(3);
        Pr.load();
        Pr.run();
        return 0;
    }catch(exception& exp){
        cout << exp.what() << endl;
        return 0;
    }
}