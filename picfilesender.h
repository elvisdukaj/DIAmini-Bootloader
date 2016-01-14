#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>

class ProgramOption;
class QSerialPort;

class PICFileSender : public QObject
{
	Q_OBJECT

public:
	PICFileSender(const ProgramOption& options, QObject* parent);
	void send(QString filename);

signals:
	void lineSent();
	void trasmitError(QString message);
	void fileSent();

private:
	void sendLine(const std::string& line);
	void openSerialPort();
	void clearSerialPortSignals();
	int readACK();
	void checkForAck();
	void throwIfCannotOpenSerialPort() const;

private:
	const ProgramOption& m_Options;
	QSerialPort* m_SerialPort;
};

#endif // FILESENDER_H
