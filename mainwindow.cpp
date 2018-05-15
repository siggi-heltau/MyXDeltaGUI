#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->progressBar->setValue(0);

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
	newFilename = QFileDialog::getSaveFileName(
				this, "Neue Datei suchen ...",
				QDir::homePath(),
				QString::fromLatin1("*.*"));
	ui->txtNewFile->setText( newFilename );
}


void MainWindow::on_btnBrowsePatchFile_clicked()
{
	patchFilename = showFileDialog();
	ui->txtPatchFile->setText( patchFilename );
}


void MainWindow::on_btnAction_clicked()
{
	if ( !newFilename.isEmpty() && !oldFilename.isEmpty() && !patchFilename.isEmpty()) {
		// progress bar aktiv setzen
		toggleProgressBarActivity();
		// xdelta aufrufen
		// progress bar inaktiv setzen
		popen()

	}
}


QString MainWindow::showFileDialog()
{
	QString fileName = QFileDialog::getOpenFileName(
				this, "Alte Datei suchen ...",
				QDir::homePath(),
				QString::fromLatin1("*.*"));

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
