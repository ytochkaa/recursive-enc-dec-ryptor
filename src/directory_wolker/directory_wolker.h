#ifndef DIRECTORY_WALKER_H
#define DIRECTORY_WALKER_H

#include <QString>
#include <QFileInfo>
#include <QStringList>

class DirectoryWalker
{

public:
    // обход
    void walker(const QString &path);

    // файлы для шифрования/расшифрования
    QStringList GetFilesOperations() const{
        return filesOperations;
    }

    // пропущенные файлы в виде "путь - причина"
    QStringList GetFilesSkip() const{
        return filesSkip;
    }

private:
    QStringList filesOperations;
    QStringList filesSkip;

    // filesOperations or filesSkip
    void classifierFiles(const QFileInfo &entry);

};

#endif
