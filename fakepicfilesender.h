#ifndef FAKEPICFILESENDER_H
#define FAKEPICFILESENDER_H

#include <thread>
#include <QObject>
#include <QString>

class FakePICFileSender : public QObject {
	Q_OBJECT

public:
	FakePICFileSender();
	~FakePICFileSender();

	void send(QString filename);

signals:
	void lineSent();
	void trasmitError(QString message);
	void fileSent();

private:
	void trasmitFileAsync();

private:
	QString m_FileToSend;
	std::thread m_Thread;
};


#endif // FAKEPICFILESENDER_H
