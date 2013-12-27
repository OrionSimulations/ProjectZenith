#include "launcher/launchbase.h"

int main(int argc, char **argv)
{
    QApplication launch(argc,argv);
    launchBase launcher;
    launcher.show();
    return launch.exec();
}
