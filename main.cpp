#include <iostream>
#include <fstream>
#include <string>
#include "filelogger.h"
#include <thread>



using namespace loggers;


 void funct(FileLogger *logger){
 	for(int i=0 ; i < 100 ; i++)
 	 logger->warning("from thread "+std::to_string(i));
 	 
 }
 
 void func2(FileLogger *logger){
 	for(int i=0 ; i < 10000 ; i++)
 	 logger->error("from thread2 "+std::to_string(i));
 	
 }
int main (int arg , char * args[]){
    
    FileLogger *logger=new FileLogger("app.log");
    
    std::thread t1(funct, logger);
    std::thread t2(func2, logger);
    for (int i=0; i < 100; i++){
    	//logger->writeln("Image Logging " + std::to_string(i));
    	(*logger) <<1<<"Parent again";
	}
	t1.join();
	t2.join();
	return 0;
}
