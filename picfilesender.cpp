#include <thread>
#include <fstream>
#include <QtSerialPort/QSerialPort>
#include "utils.h"
#include "programoption.h"
#include "picfilesender.h"

static const int ACKNOWLEDGE_OK = 0x06;
static const int ACKNOWLEDGE_NOK = 0x15;

PICFileSender::PICFileSender(const ProgramOption& options, QObject* parent)
	: QObject(parent), m_Options(options)
{
	m_SerialPort = new QSerialPort(this);
}

void PICFileSender::send(QString filename)
{
	openSerialPort();
	clearSerialPortSignals();

	bool hasErrors = false;
	std::ifstream fileToSend(filename.toStdString());

	if(!fileToSend)
	{
		emit trasmitError(QString("Impossibile aprire %1").arg(filename));
		return;
	}

	for(std::string line; std::getline(fileToSend, line);)
	{
		sendLine(line);

		try
		{
			checkForAck();
		}
		catch( std::exception& exc )
		{
			hasErrors = true;
			emit trasmitError(exc.what());
			break;
		}
	}

	if( !hasErrors )
		emit fileSent();

	m_SerialPort->close();
}

void PICFileSender::openSerialPort()
{
	m_SerialPort->setPortName(m_Options.serialPortName());
	m_SerialPort->open(QSerialPort::ReadWrite);

	throwIfCannotOpenSerialPort();

	m_SerialPort->setBaudRate(QSerialPort::BaudRate(m_Options.baudRate()));
	m_SerialPort->setDataBits(QSerialPort::DataBits(m_Options.dataBits()));
	m_SerialPort->setParity(QSerialPort::Parity(m_Options.parity()));
	m_SerialPort->setStopBits(QSerialPort::StopBits(m_Options.stopBits()));
	m_SerialPort->setFlowControl(QSerialPort::FlowControl(m_Options.flowControl()));
}

void PICFileSender::clearSerialPortSignals()
{
	m_SerialPort->setRequestToSend(false);
	m_SerialPort->setDataTerminalReady(false);
	m_SerialPort->setBreakEnabled(false);
}

int PICFileSender::readACK()
{
	if(m_SerialPort->waitForReadyRead(m_Options.AckTimeout()))
		return m_SerialPort->readAll()[0];
	else
		throw std::invalid_argument("ACK non ricevuto: timeout");
}

void PICFileSender::sendLine(const std::string& line)
{
	std::string lineToSend = line + std::string("\n");

	auto size = line.size();
	auto sentBytes = m_SerialPort->write(line.c_str(), line.size());

	if( sentBytes == -1)
		throw std::runtime_error("Impossibile inviare dati sulla porta seriale");
	else if(sentBytes != size)
		throw std::runtime_error("Non tutti i bytes sono stati inviati");
}

void PICFileSender::checkForAck()
{
	if(readACK() == ACKNOWLEDGE_OK )
		emit lineSent();
	else
		throw std::runtime_error("ACKNOWLEDGE not recieved");
}

void PICFileSender::throwIfCannotOpenSerialPort() const
{
	if(!m_SerialPort->isOpen())
		throw std::runtime_error("Impossibile aprire la porta seriale");
}
