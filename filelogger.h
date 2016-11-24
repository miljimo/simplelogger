#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H
#include <iostream>
#include <fstream>

#include "logger.h"
#include <mutex>



namespace loggers{

	class FileLogger:public Logger
	{
	private:
		std::ofstream *writer;
		std::ifstream *reader;
		std::string filename;
		std::mutex mutexWrite;
		std::mutex mutexOpen;
		static int counter;		
	public:
		  FileLogger(const std::string filename);
		  //implementation fo writer functions
		  virtual void writeln(const std::string message);
		  virtual void writeln(const int message);
		  virtual void writeln(const float message);
		  virtual void writeln(const double message);		  
		  FileLogger & operator <<(const std::string message);
		  FileLogger & operator <<(const double message);
		  FileLogger & operator <<(const int message);
		  FileLogger & operator <<(const float message);
		  //overriding of the warning functions
		  void virtual warning(const std::string message);
		  void virtual error(const std::string message);
		  
		 ~FileLogger();
		 
    private:
    	  void open();
    	  std::string currentTime();
    	  void log(const std::string message, const std::string type);
	};
}

#endif
