#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define LOGGER_OUTPUT "output.csv"
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

		void flush_current_line();

	private:
		Logger(std::string);
		~Logger();
		static Logger* logger;

		std::ofstream file;
		std::vector<std::string> current_line;
};
#endif