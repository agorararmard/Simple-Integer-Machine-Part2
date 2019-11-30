#include "Processor.h"
#include <string>
using namespace std;


//Receiving the program to run as an argument.
//All heap allocations are destroyed by the end of the program. No memory leaks.
//All types of exceptions are handled. Please check README.md for more details.
int main(int argc, char *argv[]){
    try{
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
    }
}