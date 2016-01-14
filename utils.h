#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <chrono>
#include <iosfwd>
#include <QString>
#include <QList>

const QString APPLICATION_NAME = "DIAmini Bootloader";

size_t CountLinesInAFile(std::string file);
QStringList GetAviableSerialPorts();

class Timer
{
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::duration<double, std::ratio<1> > Second;

public:
	Timer() : m_Start(Clock::now())
	{
	}

	void reset()
	{
		m_Start = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>
				(Clock::now() - m_Start).count();
	}

private:
	std::chrono::time_point<Clock> m_Start;
};

#endif // UTILS_H
