#ifndef XDELTAPROCESS_H
#define XDELTAPROCESS_H

#include <QObject>

class XDeltaWorker : public QObject
{
public:
	XDeltaWorker();

public slots:
	void doWork(const QString &parameter);
};

#endif // XDELTAPROCESS_H
