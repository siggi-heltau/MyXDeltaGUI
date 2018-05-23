#include "xdeltaprocess.h"

XDeltaWorker::XDeltaWorker(QObject *parent): QThread (parent),
    operation(-1),
    forceOverwrite(false)
{

}

void XDeltaWorker::setFilenames(const QString &qstrOldfilename, const QString &qstrNewfilename, const QString &qstrPatchfilename)
{
    oldFilename = qstrOldfilename;
    newFilename = qstrNewfilename;
    patchFilename = qstrPatchfilename;
}

void XDeltaWorker::setOperation(int mode)
{
    operation = mode;
}
