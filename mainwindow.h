#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
	}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_btnBrowseOldFile_clicked();

	void on_btnBrowseNewFile_clicked();

	void on_btnBrowsePatchFile_clicked();

	void on_btnAction_clicked();

	QString showFileDialog();
	void startProgressBarShowBusy();
	void stopProgressBarShowBusy();
	void toggleProgressBarActivity();

	void on_txtOldFile_editingFinished();

	void on_txtNewFile_editingFinished();

	void on_txtPatchFile_editingFinished();

    void showDoneDialog();

    void on_radioCreatePatch_toggled(bool checked);

    void on_radioApplyPatch_toggled(bool checked);

public slots:
    void onXdeltaCreatePatchFinished();
    void onXdeltePatchFileFinished();

private:
	Ui::MainWindow *ui;

	QString oldFilename;
	QString newFilename;
	QString patchFilename;

    int operation;

};

#endif // MAINWINDOW_H
