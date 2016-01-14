#include <algorithm>
#include <fstream>
#include <QtSerialPort/QSerialPortInfo>
#include "utils.h"

using namespace std;

size_t CountLinesInAFile(string file)
{
	ifstream inFile(file);
	return count(istreambuf_iterator<char>(inFile),
		  istreambuf_iterator<char>(), '\n');
}

QStringList GetAviableSerialPorts()
{
	auto aviableSerialPortInfoList = QSerialPortInfo::availablePorts();

	QStringList result;

	transform(begin(aviableSerialPortInfoList), end(aviableSerialPortInfoList),
			  back_inserter(result), [](const QSerialPortInfo& serialPortInfo)
	{
		return serialPortInfo.portName();
	});

	return result;
}
