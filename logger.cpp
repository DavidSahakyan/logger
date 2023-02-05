#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>
#include <unistd.h>
#include <direct.h>

class Logger
{
public:
    Logger()
    {
        this->logfile.open("logfile.txt", std::ofstream::app);

        if(!logfile.is_open())
        {
            std::cout<<"logfile is not open";
        }
        else
        {
            auto date_time = std::chrono::system_clock::now();
            std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
            logfile<<"LOGFILE STARTED AT  "<<std::ctime(&log_time);
            logfile<<"------------------------------------------"<<std::endl;
        }
    }


    template <typename T>
    void ilog(T info)
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        this->logfile<< "INFO"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
    }

    template <typename T>
    void elog(T info)
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        this->logfile << "ERROR"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
    }

     template <typename T>
    void wLog(T info)
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        this->logfile<< "WARNING"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
    }


    ~Logger()
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        this->logfile<<"logfile was closed at "<< std::ctime(&log_time);
        this->logfile<<"------------------------------------------"<<std::endl;
        logfile.close();
    }

private:
    std::ofstream logfile;

    char buff[50]; 
    std::string path = getcwd(buff, 100);
};

int main()
{
    Logger file;
    file.ilog("INFO LOG CREATED");
    file.elog("ERROR LOG CREATED");
    
}