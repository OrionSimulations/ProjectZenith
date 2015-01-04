#include "launchbase.h"
#include <Zenith/zenith.h>
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

using namespace Zenith;

int main(int argc, char **argv)
{
	//auto Framework = Zenith::init(argv[0]);
	auto Framework = init(argv[0]);
	//Zenith::free(Framework);
	free(Framework);
	getchar();
    return 0;
}