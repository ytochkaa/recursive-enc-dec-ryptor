#include "directory_wolker.h"

#include <QCoreApplication>
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

void DirectoryWalker::classifierFiles(const QFileInfo &entry){

    if (entry.isSymLink()) {
        filesSkip.append(entry.filePath() + " - link");
    } else if (entry.isDir()) {
        return; // сами папки не шифруем, их содержимое перебирает walker
    } else if (!entry.isFile()) {
        filesSkip.append(entry.filePath() + " - not a regular file");
    } else if (entry.absoluteFilePath() == QCoreApplication::applicationFilePath()) {
        filesSkip.append(entry.filePath() + " - the program itself");
    } else {
        filesOperations.append(entry.filePath());
    }
}

void DirectoryWalker::walker(const QString &path){

    filesOperations.clear();
    filesSkip.clear();

    QFileInfo pathInfo(path);
    classifierFiles(pathInfo);

    // Файл и ссылку уже обработали, в ссылку на папку заходить нельзя
    if (!pathInfo.isDir() || pathInfo.isSymLink()) {
        return;
    }

    // QDirIterator (const QString &path,                           - где обходить: путь к папке
    //                   QDir::Filters filters,                     - что показывать: флаги QDir::..., склеиваются через |
    //                   IteratorFlags flags = NoIteratorFlags);    - как обходить: Subdirectories - заходить в подпапки,
    //                                                                по умолчанию (NoIteratorFlags) только верхний уровень
    // QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot - какие записи показывать: файлы и папки, без "." и ".."
    // Hidden - скрытые файлы, System - чтобы битые ссылки и системные файлы попали в отчёт
    // Флаг Subdirectories не используем: с ним итератор заходит в junction-точки.
    // Поэтому папки обходим сами: в dirsToVisit кладём только настоящие папки, не ссылки
    QStringList dirsToVisit{path};

    while (!dirsToVisit.isEmpty()){
        QDirIterator pathIteratro(dirsToVisit.takeLast(), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);

        while (pathIteratro.hasNext()){
            pathIteratro.next();
            const QFileInfo entry = pathIteratro.fileInfo();
            classifierFiles(entry);

            if (entry.isDir() && !entry.isSymLink()) {
                dirsToVisit.append(entry.filePath());
            }
        }
    }
}
