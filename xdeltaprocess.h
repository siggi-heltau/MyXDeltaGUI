#ifndef XDELTAPROCESS_H
#define XDELTAPROCESS_H

#include <QThread>
#include <QDebug>
#include "helperfunctions.h"

enum XDELTA_OPERATION { XDELTA_PATCH, XDELTA_CREATE_PATCH };

class XDeltaWorker : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE {
        QString qstrCommand;
        if(forceOverwrite)
            qstrCommand = "xdelta3-3.0.11-i686.exe -f %1 -s %2 %3 %4";
        else
            qstrCommand = "xdelta3-3.0.11-i686.exe %1 -s %2 %3 %4";

        switch(operation) {
        case XDELTA_PATCH:
            qstrCommand = qstrCommand.arg("-d")
                    .arg(oldFilename)
                    .arg(patchFilename)
                    .arg(newFilename);
            qDebug() << siplas::qt::toWindows1252(qstrCommand).constData() ;
            system( siplas::qt::toWindows1252(qstrCommand).constData() );
            emit donePatch();
            break;
        case XDELTA_CREATE_PATCH:
            qstrCommand = qstrCommand.arg("-e")
                    .arg(oldFilename)
                    .arg(newFilename)
                    .arg(patchFilename);
            qDebug() << siplas::qt::toWindows1252(qstrCommand).constData() ;
            system( siplas::qt::toWindows1252(qstrCommand).constData() );
            emit doneCreateDelta();
            break;
        default:
            break;
        }

    }
public:
    XDeltaWorker(QObject *parent = Q_NULLPTR);
    void setFilenames(const QString &qstrOldfilename,
                      const QString &qstrNewfilename,
                      const QString &qstrPatchfilename);
    void setOperation( int mode );

signals:
    void donePatch();
    void doneCreateDelta();


private:
    int operation;
    QString newFilename;
    QString oldFilename;
    QString patchFilename;
    bool forceOverwrite;

};

#endif // XDELTAPROCESS_H
