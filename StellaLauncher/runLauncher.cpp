#include "launchbase.h"
#include <Stella/stella.h>
#include <iostream>

/*//Qt module launcher. Retained as a secondary option.
int main(int argc, char **argv)
{
    QApplication launch(argc,argv);
    launchBase launcher;
    launcher.show();
    return launch.exec();
}
//*/

int main(int argc, char **argv)
{
	auto Framework = Stella::init(argv[0]);
	Stella::free(Framework);
	getchar();
    return 0;
}
