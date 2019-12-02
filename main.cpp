#include "nSIM.h"
#include <string>
#include<cstring>
using namespace std;


//Receiving the number of processers to run as an argument.
//All heap allocations are destroyed by the end of the program. No memory leaks.
//All types of exceptions are handled. Please check README.md for more details.
int main(int argc, char *argv[]){

    if(argc == 1) {
    cout << "Please specify the number of cores on the processers through the command line; read the README.md for more details" << endl;
    return 0;
    }

    try{
        nSIM Pr(stoi(argv[1]));
        cout << "Please insert the programs you want to run on the " << argv[1] << "cores, each in a separate line -For more details about the formatting refer to the README.md-: \n";
        Pr.load();
        Pr.run();
        return 0;
    }catch(exception& exp){
        cout << exp.what() << endl;
        return 0;
    }
}