#include <iostream>
#include <string>
#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <QStringList>

#include "directory_wolker/directory_wolker.h"

int main(int argc, char *argv[]) {
    // Нужен для QCoreApplication::applicationFilePath()
    QCoreApplication app(argc, argv);

    std::string pathToFileOrDir;
    std::cout << "Enter the path to the file or directory" << std::endl;
    std::getline(std::cin, pathToFileOrDir);

    const QString path = QString::fromStdString(pathToFileOrDir);
    const QFileInfo pathInfo(path);

    // путь пустой/несуществует/это ссылка
    if (path.isEmpty() || (!pathInfo.exists() && !pathInfo.isSymLink())) {
        std::cout << "This path does not exist" << std::endl;
        return 1;
    }

    DirectoryWalker directoryWalker;
    directoryWalker.walker(path);

    const QStringList filesToProcess = directoryWalker.GetFilesOperations();
    const QStringList filesSkipped = directoryWalker.GetFilesSkip();

    // toStdString(): текст в формате Qt -> тот же текст в формате стандартного C++
    std::cout << "Files to process:" << std::endl;
    for (int i = 0; i < filesToProcess.size(); i++) {
        std::cout << "  " << filesToProcess[i].toStdString() << std::endl;
    }

    if (filesToProcess.isEmpty()) {
        std::cout << "Nothing to process" << std::endl;
    }

    std::cout << "Skipped:" << std::endl;
    for (int i = 0; i < filesSkipped.size(); i++) {
        std::cout << "  " << filesSkipped[i].toStdString() << std::endl;
    }

    if (filesSkipped.isEmpty()) {
        std::cout << "Nothing to skip" << std::endl;
    }

    return 0;
}
