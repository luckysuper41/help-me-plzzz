#include <time.h>
#include "pacmanwindow.h"

Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(0));

    PacmanWindow wnd;
    wnd.show();

    return app.exec();
}
