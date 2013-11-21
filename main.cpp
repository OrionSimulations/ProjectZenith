#include <iostream>
#include "EngineConfig.h"
#include "processes/makeStarSys.h"
#include <string>

int main(int argc, char **argv) {
    char exit = '`';
    std::cout << "Stella Engine: v." << Engine_Version << endl;
    newStarSys();
    cout << "Destruction of Star System Commencing...";
    while(exit == '`'){
        cout << "Engine Destruction Complete. Exit program now.";
        cin >> exit;
    }
    return 0;
}
