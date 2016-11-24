#ifndef INTERFACE_LOGGER_H
#define INTERFACE_LOGGER_H

	#include <string>

	namespace  loggers
	{
		class IWriter {
		 public:
		 	virtual void writeln(const std::string message)=0;
	    };
	}

#endif
