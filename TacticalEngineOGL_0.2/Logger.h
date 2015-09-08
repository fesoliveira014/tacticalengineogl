#ifndef _LOGGER_FILE_H_
#define _LOGGER_FILE_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "Logger.h"

class Logger{
public:

	enum class logType {LOG_ERROR, LOG_WARNING, LOG_INFO};

	explicit Logger(const std::string & fileName, bool console = false) : m_numErrors(0U), m_numWarning(0U), m_console(console) {
		m_file.open(fileName.c_str());

		if (m_file.is_open()) {
			UpdateTimeString();

			m_file << "<" + m_timeString + "> - Session Initiated." << std::endl;
			m_file << std::endl << std::endl;

			if (m_console) {
				std::cout << "<" + m_timeString + "> - Session Initiated." << std::endl;
				std::cout << std::endl << std::endl;
			}
		}
	}

	~Logger() {
		if (m_file.is_open()) {
			UpdateTimeString();
			m_file << std::endl << std::endl;
			m_file << "<" + m_timeString + "> - There were " << m_numWarning << " warnings and " << m_numErrors << " errors." << std::endl;
			m_file << "---------------------------------------" << std::endl;
			m_file << std::endl << std::endl;

			if (m_console) {
				std::cout << std::endl << std::endl;
				std::cout << "<" + m_timeString + "> - There were " << m_numWarning << " warnings and " << m_numErrors << " errors." << std::endl;
				std::cout << "---------------------------------------" << std::endl;
				std::cout << std::endl << std::endl;
			}

			m_file.close();
		}
	}

	friend Logger &operator << (Logger &logger, const logType type) {
		logger.UpdateTimeString();
		switch (type) {
		case Logger::logType::LOG_ERROR:
			logger.m_file << "<" + logger.m_timeString + "> - [ERROR]: ";

			if (logger.m_console) std::cout << "<" + logger.m_timeString + "> - [ERROR]: ";

			++logger.m_numErrors;
			break;

		case Logger::logType::LOG_WARNING:
			logger.m_file << "<" + logger.m_timeString + "> - [WARNING]: ";

			if (logger.m_console) std::cout << "<" + logger.m_timeString + "> - [WARNING]: ";

			++logger.m_numWarning;
			break;

		case Logger::logType::LOG_INFO:
			logger.m_file << "<" + logger.m_timeString + "> - [INFO]: ";
			if (logger.m_console) std::cout << "<" + logger.m_timeString + "> - [INFO]: ";
			break;
		}

		return logger;
	}

	friend Logger &operator << (Logger &logger, const std::string text) {
		logger.m_file << text << std::endl;
		if (logger.m_console) std::cout << text << std::endl;
		return logger;
	}

	void SetConsole(bool option) {
		m_console = option;
	}

	Logger(const Logger &) = delete;
	Logger &operator= (const Logger &) = delete;

protected:
	void UpdateTimeString() {
		m_currentTime = time(0);
		m_now = localtime(&m_currentTime);

		char buff[10];
		_snprintf(buff, sizeof(buff), "%02d:%02d:%02d", m_now->tm_hour, m_now->tm_min, m_now->tm_sec);
		
		m_timeString = buff;
	}

	unsigned int m_numErrors;
	unsigned int m_numWarning;

	std::ofstream m_file;

	time_t m_currentTime;
	struct tm* m_now;
	std::string m_timeString;

	bool m_console;
};

#endif