#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "programoption.h"

namespace Ui {
class MainWindow;
}

class PICFileSender;
class SerialPortDialog;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void fillAviableSerialPortsAndSelectCurrent();

private:
	void setProgressBarMaximumValue();
	void enableWindowForSending();
	void disableWindowForSending();

private slots:
	// windows events
	void onOpen(bool checked);
	void onClose(bool checked);
	void onProgram(bool checked);

	// file transfer events
	void onLineSent();
	void onTrasmitError(QString message);
	void onFileSent();

private:
	bool getHEXFilename();
	void selectItemWithLastPort();

private:
	QString m_Filename;
	size_t m_Progress = 0;

	ProgramOption m_Option;
	PICFileSender* m_FileSender;

private:
	Ui::MainWindow *ui;
	void disableControlForSending();
	void enableControlAfterSending();
};

#endif // MAINWINDOW_H
