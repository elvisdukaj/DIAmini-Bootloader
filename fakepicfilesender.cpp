#include <fstream>
#include <QApplication>
#include <QDebug>
#include "fakepicfilesender.h"
#include "programoption.h"

FakePICFileSender::FakePICFileSender()
{
}

FakePICFileSender::~FakePICFileSender()
{
	if( m_Thread.joinable())
		m_Thread.join();
}

void FakePICFileSender::send(QString filename)
{
	std::ifstream fileToSend(filename.toStdString());

	if(!fileToSend)
	{
		emit trasmitError(QString("Impossibile aprire %1").arg(m_FileToSend));
		return;
	}

	for(std::string line; std::getline(fileToSend, line);)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		emit lineSent();
	}

	emit fileSent();
}
