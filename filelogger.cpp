#include "filelogger.h"
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace loggers;


int FileLogger::counter =0;

FileLogger::FileLogger(const std::string filename)
{
	try{
		this->filename = (std::string)filename;
        this->writer = new std::ofstream();
        this->open();
	}catch(...){
        if(this->writer->is_open()){
        	 this->writer->close();
        }
		throw;
	}
   
}

/**
 Implementation of the writer writeln functions for the logger
*/

void FileLogger::writeln(const std::string message){
	//resolve race condition problem to make the function thread free	
    log(message, "log"); 
}

 void FileLogger::log(const std::string message, const std::string type){
 	 std::lock_guard<std::mutex> locker(this->mutexWrite);
 	 this->open();
 	 if(this->writer->good()){
 	 	std::string time  = this->currentTime();
 		(*this->writer)<<"fid="<<(++FileLogger::counter)<<";type="<<type<<";msg="<< message <<";time="<<time;
	 }	
 	
 }

void FileLogger::writeln(const int message){
    this->writeln(std::to_string(message));
}
void FileLogger::writeln(const float message){
    this->writeln(std::to_string(message));
   
}
void FileLogger::writeln(const double message){
    this->writeln(std::to_string(message));
}


FileLogger & FileLogger::operator <<(const std::string message){
    this->writeln(message);	
	return *this;
}

FileLogger & FileLogger::operator <<(const float message){
	this->writeln(message);
	return (*this);
}

FileLogger & FileLogger::operator <<(const double message){
	this->writeln(message);
	return (*this);
}

FileLogger & FileLogger::operator <<(const int message){
	this->writeln(message);
	return (*this);
}


/**
  Implementation of the warning function 
*/

void FileLogger::warning(const std::string  __warning){
	this->log(__warning, "warning");
}

void FileLogger::error(const std::string error){
    this->log(error, "error");
}



void FileLogger::open()
{
	std::lock_guard<std::mutex> locker(this->mutexOpen);
	if(!this->writer->is_open()){
	  this->writer->open(this->filename);
	}
}

 std::string FileLogger::currentTime(){
 	std::time_t result  = std::time(nullptr);
	std::string time  = std::ctime(&result);
	return time;
 }


FileLogger::~FileLogger(){
	if(this->writer->is_open())
		this->writer->close();	
	delete this->writer;
	if(this->reader->is_open())
		this->reader->close();
	delete this->reader;
}
