#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>
#include <direct.h>
#include <mutex>
#include <thread> 

std::mutex mtx;

class Logger
{
public:
    Logger()
    {
        this->logfile.open("logfile.txt", std::ofstream::app);

        if(!logfile.is_open())
        {
            mtx.lock();
            std::cout<<"logfile is not open";
            mtx.unlock();
        }
        else
        {
            auto date_time = std::chrono::system_clock::now();
            std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
            mtx.lock();
            logfile<<"LOGFILE STARTED AT  "<<std::ctime(&log_time);
            logfile<<"------------------------------------------"<<std::endl;
            mtx.unlock();

        }
    }

    template <typename T>
    void ilog(T info, std::string func_name = "")
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        mtx.lock();
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        if(func_name != "")
        {
            this->logfile << "PROGRAMM IS IN " << func_name << std::endl;
        }
        this->logfile<< "INFO"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
        mtx.unlock();
    }

    template <typename T>
    void elog(T info, std::string func_name = "")
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        mtx.lock();
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        if(func_name != "")
        {
             this->logfile << "PROGRAMM IS IN " << func_name << std::endl;
        }
        this->logfile << "ERROR"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
        mtx.unlock();
    }

    template <typename T>
    void wLog(T info, std::string func_name = "")
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        mtx.lock();
        this->logfile << std::ctime(&log_time);
        this->logfile << path << std::endl;
        if(func_name != "")
        {
            this->logfile << "PROGRAMM IS IN " << func_name << std::endl; 
        }
        this->logfile<< "WARNING"<< ":" << info << std::endl;
        logfile<<"------------------------------------------"<<std::endl;
        mtx.unlock();
    }

    ~Logger()
    {
        auto date_time = std::chrono::system_clock::now();
        std::time_t log_time = std::chrono::system_clock::to_time_t(date_time);
        mtx.lock();
        this->logfile<<"logfile was closed at "<< std::ctime(&log_time);
        this->logfile<<"------------------------------------------"<<std::endl;
        mtx.unlock();
        logfile.close();
    }

private:
    std::ofstream logfile;

    char buff[50]; 
    std::string path = _getcwd(buff, 100);

    std::string func_name; 
};

int main()
{
    Logger file;
    file.ilog("INFO LOG CREATED", "some_func");
    file.elog("ERROR LOG CREATED", "other_func");
}