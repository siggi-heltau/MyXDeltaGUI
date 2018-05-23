#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "xdeltaprocess.h"


#include <QFileDialog>
#include <QMessageBox>

const char *xdeltaFilter = "XDelta Dateien (*.xdelta);;Alle Dateien (*.*)";
const char *abbildFilter = "Abbild Dateien (*.img *.bin *.raw *.iso);;Alle Dateien (*.*)";

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->progressBar->setValue(0);
    operation = XDELTA_CREATE_PATCH;
}

MainWindow::~MainWindow()
{    
	delete ui;
}

void MainWindow::on_btnBrowseOldFile_clicked()
{
	oldFilename = showFileDialog();
	ui->txtOldFile->setText( oldFilename );
}


void MainWindow::on_btnBrowseNewFile_clicked()
{
    if(operation == XDELTA_PATCH) {
	newFilename = QFileDialog::getSaveFileName(
                this, "Neue Datei zum erstellen suchen ...",
				QDir::homePath(),
                QString::fromLatin1(abbildFilter));
    } else if(operation == XDELTA_CREATE_PATCH) {
        newFilename = QFileDialog::getOpenFileName(
                    this, "Neue vorhandene Datei suchen ...",
                    QDir::homePath(),
                    QString::fromLatin1(abbildFilter));
    }
	ui->txtNewFile->setText( newFilename );
}


void MainWindow::on_btnBrowsePatchFile_clicked()
{
    if(operation == XDELTA_PATCH) {
        patchFilename = QFileDialog::getOpenFileName(
                    this, "Patch Datei suchen ...",
                    QDir::homePath(),
                    QString::fromLatin1(xdeltaFilter));
    } else if (operation == XDELTA_CREATE_PATCH) {
        patchFilename = QFileDialog::getSaveFileName(
                    this, "Patch Datei zum speichern suchen ...",
                    QDir::homePath(),
                    QString::fromLatin1(xdeltaFilter));
    }
	ui->txtPatchFile->setText( patchFilename );
}


void MainWindow::on_btnAction_clicked()
{
	if ( !newFilename.isEmpty() && !oldFilename.isEmpty() && !patchFilename.isEmpty()) {
		// progress bar aktiv setzen
		toggleProgressBarActivity();

        // xdelta worker thread erzeugen
        XDeltaWorker *xdeltaWorker = new XDeltaWorker(this);
        xdeltaWorker->setFilenames(
                    oldFilename,
                    newFilename,
                    patchFilename);
        xdeltaWorker->setOperation( operation );

        QObject::connect(xdeltaWorker, SIGNAL(doneCreateDelta()), this,
                         SLOT(onXdeltaCreatePatchFinished()));
        QObject::connect(xdeltaWorker, SIGNAL(donePatch()), this,
                         SLOT(onXdeltePatchFileFinished()));
        QObject::connect(xdeltaWorker, SIGNAL(finished()), xdeltaWorker,
                         SLOT(deleteLater()));

        xdeltaWorker->start();

	}
}


QString MainWindow::showFileDialog()
{
	QString fileName = QFileDialog::getOpenFileName(
				this, "Alte Datei suchen ...",
				QDir::homePath(),
                QString::fromLatin1(abbildFilter));

	return fileName;
}

void MainWindow::startProgressBarShowBusy()
{
	ui->progressBar->setMinimum(0);
	ui->progressBar->setMaximum(0);
}

void MainWindow::stopProgressBarShowBusy()
{
	ui->progressBar->setMinimum(0);
	ui->progressBar->setMaximum(1);
}

void MainWindow::toggleProgressBarActivity()
{
	if(ui->progressBar->minimum() == 0 && ui->progressBar->maximum() == 0) {
		stopProgressBarShowBusy();
	} else {
		startProgressBarShowBusy();
	}
}

void MainWindow::on_txtOldFile_editingFinished()
{
	oldFilename = ui->txtOldFile->text();
}

void MainWindow::on_txtNewFile_editingFinished()
{
	newFilename = ui->txtNewFile->text();
}

void MainWindow::on_txtPatchFile_editingFinished()
{
    patchFilename = ui->txtPatchFile->text();
}

void MainWindow::showDoneDialog()
{
    QMessageBox::information(
                this, "Finito",
                "Worker thread finished...");
}

void MainWindow::onXdeltaCreatePatchFinished()
{
    stopProgressBarShowBusy();
    showDoneDialog();
}

void MainWindow::onXdeltePatchFileFinished()
{
    stopProgressBarShowBusy();
    showDoneDialog();
}

void MainWindow::on_radioCreatePatch_toggled(bool checked)
{
    if(checked) {
        operation = XDELTA_CREATE_PATCH;
    }
}

void MainWindow::on_radioApplyPatch_toggled(bool checked)
{
    if(checked) {
        operation = XDELTA_PATCH;
    }
}
