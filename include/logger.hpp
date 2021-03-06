#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "common.hpp"

/**
 * Singleton class to log data periodically from
 * node, flow and link and store at LOGGER_OUTPUT
 */
class Logger{
	public:
		static Logger* getInstance();

		template<typename T>
		void log_num(T data)
		{
			current_line.push_back(std::to_string(data));
		}

		void log_str(std::string data_str)
		{
			current_line.push_back(data_str);
		}

		void prepare()
		{
			current_line.clear();
		}

		void flush_current_line();

		~Logger();
    
	private:
		Logger(std::string);

		static Logger* logger;

		std::ofstream file;
		std::vector<std::string> current_line;
};
#endif
