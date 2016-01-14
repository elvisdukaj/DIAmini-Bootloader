#ifndef PROGRAMOPTION_H
#define PROGRAMOPTION_H

#include <QString>

class ProgramOption
{
public:
	ProgramOption();

	QString serialPortName() const { return m_LastSerialPort; }
	void setSerialPortName(QString serialPortName);

	int baudRate() const { return m_Baudrate; }
	void setBaudRate(int baud);

	QString filePath() const { return m_LastFilePath; }
	void lastFilePath(QString filePath);

	int stopBits() const { return m_StopBits; }
	void setStopBits(int stopBits);

	int parity() const { return m_Parity; }
	void setParity(int parity);

	int dataBits() const { return m_DataBits; }
	void setDataBits(int dataBits);

	int flowControl() const { return m_FlowControl; }
	void setFlowControl(int flow);

	int AckTimeout() const { return m_AckTimeout; }
	void setAckTimeout(int timeout);

private:
	void load();
	void save();

private:
	QString m_LastSerialPort;
	int m_Baudrate;
	int m_StopBits;
	int m_Parity;
	int m_DataBits;
	int m_FlowControl;
	int m_AckTimeout;
	QString m_LastFilePath;
};

#endif // PROGRAMOPTION_H
