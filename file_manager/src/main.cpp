#include <iostream>
#include <QtWidgets>
#include "FileManagerClass/FileManagerClass.hpp"


int main(int args, char** argv)
{
    QApplication* app = new QApplication(args, argv);
    FileManagerClass file_manager(app, nullptr);
    
    file_manager.resize(300, 200);
    file_manager.show();

    return app->exec();
}

