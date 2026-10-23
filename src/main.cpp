#include <iostream>
#include <QFileInfo>
#include <QString>

#include "directory_wolker/directory_wolker.h"

int main () {
    std::string PathToFileOrDir;

    std::cout << "Enter the path to the file" << std::endl;
    std::getline(std::cin, PathToFileOrDir);
    
    QString qPathToFileOrDir = QString::fromStdString(PathToFileOrDir);
    dirWolker(qPathToFileOrDir);

    // dirWolker("C:/Users/Dashyla/Desktop/computer_security/Programming/Development of information security tools/Recursive enc(dec)ryptor/recursive-enc-dec-ryptor/test_dir");
    return 0;
}
