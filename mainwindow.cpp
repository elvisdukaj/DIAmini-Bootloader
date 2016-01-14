#include <fstream>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include "utils.h"
#include "picfilesender.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::fillAviableSerialPortsAndSelectCurrent()
{
	ui->serialPortList->addItems(GetAviableSerialPorts());
	connect(ui->serialPortList, QComboBox::currentTextChanged, [this](const QString& serialPortName)
	{
		m_Option.setSerialPortName(serialPortName);
	});
	selectItemWithLastPort();
}

MainWindow::MainWindow(QWidget */*parent*/) : ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_FileSender = new PICFileSender(m_Option, this);

	connect(ui->loadHex, QPushButton::clicked, this, MainWindow::onOpen);
	connect(ui->program, QPushButton::clicked, this, MainWindow::onProgram);

	connect(m_FileSender, PICFileSender::lineSent, this, MainWindow::onLineSent);
	connect(m_FileSender, PICFileSender::trasmitError, this, MainWindow::onTrasmitError);
	connect(m_FileSender, PICFileSender::fileSent, this, MainWindow::onFileSent);

	fillAviableSerialPortsAndSelectCurrent();
	setWindowTitle(APPLICATION_NAME);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onOpen(bool /*checked*/)
{
	if (getHEXFilename())
	{
		setProgressBarMaximumValue();
		enableWindowForSending();
	}
}

void MainWindow::onClose(bool /*checked*/)
{
	disableWindowForSending();
}

void MainWindow::onProgram(bool /*checked*/)
{
	try
	{
		QApplication::setOverrideCursor(Qt::WaitCursor);
		disableControlForSending();
		m_FileSender->send(m_Filename);
	}
	catch( const std::exception& exc)
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::critical(this, "Errore", exc.what());
	}
}

void MainWindow::onLineSent()
{
	ui->loadHex->setEnabled(!ui->loadHex->isEnabled());
	ui->progressBar->setValue(++m_Progress);
}

void MainWindow::onTrasmitError(QString message)
{
	QApplication::restoreOverrideCursor();
	ui->progressBar->setEnabled(false);
	QMessageBox::critical(this, "Errore", QString("Si e' verificato un problema: %1").arg(message));
}

void MainWindow::onFileSent()
{
	QApplication::restoreOverrideCursor();
	QMessageBox::information(nullptr, "File inviato", "File inviato con successo");
	enableControlAfterSending();
}

bool MainWindow::getHEXFilename()
{
	ProgramOption option;
	m_Filename = QFileDialog::getOpenFileName(
				this,
				"Scegli un file Intel HEX da inviare al PIC",
				option.filePath(),
				"Intel HEX Files (*.hex);;Tutti i file (*.*)");

	if( m_Filename.isEmpty())
		return false;

	option.lastFilePath(QFileInfo(m_Filename).absolutePath());
	m_Progress = 0;
	return true;
}

void MainWindow::selectItemWithLastPort()
{
	ui->serialPortList->setCurrentText(m_Option.serialPortName());
}

void MainWindow::setProgressBarMaximumValue()
{
	std::size_t fileLines = CountLinesInAFile(m_Filename.toStdString());
	ui->progressBar->setMaximum(fileLines);
}

void MainWindow::enableWindowForSending()
{
	setWindowTitle(QString("%1 - %2").arg(APPLICATION_NAME, m_Filename ));
	ui->progressBar->setEnabled(true);
	ui->program->setEnabled(true);
}

void MainWindow::disableWindowForSending()
{
	setWindowTitle(APPLICATION_NAME);
	m_Filename = "";
	ui->loadHex->setEnabled(true);
	ui->progressBar->setEnabled(false);
	ui->program->setEnabled(false);
	ui->progressBar->setValue(0);
}


void MainWindow::disableControlForSending()
{
	m_Progress = 0;
	ui->progressBar->setValue(0);
	ui->program->setEnabled(false);
}

void MainWindow::enableControlAfterSending()
{
	ui->program->setEnabled(true);
}
