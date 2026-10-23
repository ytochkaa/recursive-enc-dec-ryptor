#include "directory_wolker.h"

#include <iostream>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>

/*QFileInfo
exists()    существует ли путь
isSymLink() ссылка ли это
isDir()     папка ли это
isFile()	файл ли это

QDirIterator
hasNext()   остались ли ещё необойдённые элементы
next()	    переходит к следующему элементу и возвращаеты его путь (QString)
*/
void dirWolker (const QString &pathfor){

    QFileInfo pathInfo(pathfor);

    if (!pathInfo.exists()){
        std::cout << "it path does not exist" << std:: endl;
        return;
    }

// pathInfo.filePath().toStdString() сведенья о файле -> текст в формате Qt -> тот же текст в формате стандартного C++

    if (pathInfo.isSymLink()) {
        std::cout << "it is link on file/directory" << std:: endl;
        return;
    } else if (pathInfo.isFile()){
        std::cout << "it is file: " << pathInfo.filePath().toStdString() << std::endl;
        return;
    } else if (pathInfo.isDir()){
        std::cout << "it is directory" << std::endl;

        // QDirIterator (const QString &path,                           - где обходить: путь к папке
        //                   QDir::Filters filters,                     - что показывать: флаги QDir::..., склеиваются через |
        //                   IteratorFlags flags = NoIteratorFlags);    - как обходить: Subdirectories - заходить в подпапки,
        //                                                                по умолчанию (NoIteratorFlags) только верхний уровень
        // QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot - какие записи показывать: файлы и папки, без "." и ".."
        QDirIterator pathIteratro(pathfor, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

        while (pathIteratro.hasNext()){
            pathIteratro.next();
            QFileInfo entry = pathIteratro.fileInfo();

            if (entry.isSymLink()) {
                std::cout << "it is link on file/directory: " << entry.filePath().toStdString() << std::endl;
            } else if (entry.isFile()){
                std::cout << "it is file: " << entry.filePath().toStdString() << std::endl;
            } else if (entry.isDir()){
                std::cout << "it is directory: " << entry.filePath().toStdString() << std::endl;
            }
        }
    }
}



    