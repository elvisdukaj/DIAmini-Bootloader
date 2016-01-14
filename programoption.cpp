#include <QSettings>
#include <QtSerialPort/QSerialPort>
#include "utils.h"
#include "programoption.h"

static const QString ORGANIZATION_NAME = "Elice Soft";

ProgramOption::ProgramOption()
{
	load();
}

void ProgramOption::setSerialPortName(QString serialPortName)
{
	m_LastSerialPort = serialPortName;
	save();
}

void ProgramOption::setBaudRate(int baud)
{
	m_Baudrate = baud;
	save();
}

void ProgramOption::lastFilePath(QString filePath)
{
	m_LastFilePath = filePath;
	save();
}

void ProgramOption::setStopBits(int stopBits)
{
	m_StopBits = stopBits;
	save();
}

void ProgramOption::setParity(int parity)
{
	m_Parity = parity;
	save();
}

void ProgramOption::setDataBits(int dataBits)
{
	m_DataBits = dataBits;
	save();
}

void ProgramOption::setFlowControl(int flow)
{
	m_FlowControl = flow;
	save();
}

void ProgramOption::setAckTimeout(int timeout)
{
	m_AckTimeout = timeout;
	save();
}

static const QString OPTION_FILENAME("options.ini");

void ProgramOption::load()
{
	QSettings settings(OPTION_FILENAME, QSettings::IniFormat);

	m_LastFilePath = settings.value("LastFilePath", ".").toString();

	settings.beginGroup("SerialPortSettings");
	m_LastSerialPort = settings.value("Name", "COM1").toString();
	m_Baudrate = settings.value("Baudrate", QSerialPort::Baud38400).toInt();
	m_DataBits = settings.value("DataBits", QSerialPort::Data8).toInt();
	m_Parity = settings.value("Parity", QSerialPort::NoParity).toInt();
	m_StopBits = settings.value("StopBits", QSerialPort::OneStop).toInt();
	m_FlowControl = settings.value("FlowControl", QSerialPort::NoFlowControl).toInt();
	settings.endGroup();

	settings.beginGroup("Communication");
	m_AckTimeout = settings.value("AckTimeoutMs", 1000).toInt();
	settings.endGroup();
}

void ProgramOption::save()
{
	QSettings settings(OPTION_FILENAME, QSettings::IniFormat);

	settings.setValue("LastFilePath", m_LastFilePath);

	settings.beginGroup("SerialPortSettings");
	settings.setValue("Name", m_LastSerialPort );
	settings.setValue("Baudrate", m_Baudrate);
	settings.setValue("DataBits", m_DataBits);
	settings.setValue("Parity", m_Parity);
	settings.setValue("StopBits", m_StopBits);
	settings.setValue("FlowControl", m_FlowControl);
	settings.endGroup();

	settings.beginGroup("Communication");
	settings.setValue("AckTimeoutMs", m_AckTimeout);
	settings.endGroup();
}
