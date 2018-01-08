#ifndef SEG2STOSEGYS_H
#define SEG2STOSEGYS_H

#include <QObject>

class Seg2File;
class SegyFile;

class Seg2sToSegys : public QObject
{
    Q_OBJECT
public:
    explicit Seg2sToSegys(QObject *parent = 0);

    void setSeg2FileNames(const QStringList &files);
    void loadSeg2Files();

    void saveAsSegys(const QString &fileName);

    QList<Seg2File*> seg2files;
    QList<SegyFile*> segyfiles;
    QStringList seg2fileNames;

    void clearSeg2Files();
    void clearSegyFiles();

};

#endif // SEG2STOSEGYS_H
