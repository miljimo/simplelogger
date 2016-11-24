#ifndef WARNING_H_LOG
#define WARNING_H_LOG
#include <string>

namespace loggers{
	
	
	class Logger{
		
		public:
			void virtual warning(const std::string message) =0;
			void virtual error(const std::string message)=0;
			void virtual writeln(const std::string message)=0;
			//void virtual debug(std::string title, std::string message);
	};
}

#endif
