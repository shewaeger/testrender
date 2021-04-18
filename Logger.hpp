//
// Created by shewa on 18.04.2021.
//

#ifndef TESTRENDER_LOGGER_HPP
#define TESTRENDER_LOGGER_HPP


#include <iostream>

class Logger {
private:

	static Logger *logger;
	Logger() = default;

	static Logger & getLogger() {
		if(!logger) {
			logger = new Logger();
		}
		return *logger;
	}
public:
	static void info(const char * message) {
		std::cout << "[INFO] " << message << std::endl;
	};

	static void error(const char * message) {
		std::cerr << "[ERROR] " << message << std::endl;
	}

	static void warning(const char * message) {
		std::cout << "[WARNING] " << message << std::endl;
	}

	static void print(const char * message) {
		std::cout << message;
	}

	static void println(const char * message) {
		std::cout << message << std::endl;
	}
};

Logger* Logger::logger = nullptr;

#endif //TESTRENDER_LOGGER_HPP
