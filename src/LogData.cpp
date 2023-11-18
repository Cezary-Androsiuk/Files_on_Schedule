#include "LogData.hpp"

bool LogData::enabledLogFile = false;

void LogData::enableLogFile(std::filesystem::path logs_path)
{
    // return; // best way to disable log data XD
    printf("Info: LogData: enabling log file...\n");
    if (LogData::enabledLogFile)
    {
        printf("Info: LogData: log file is already enabled\n");
        return;
    }
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    struct tm timeinfo;
#ifdef linux
    localtime_r(&currentTime, &timeinfo);
#endif
#ifdef _WIN32
    localtime_s(&timeinfo, &currentTime);
#endif

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y%m%d-%H%M%S", &timeinfo);

    auto log_file_path = std::filesystem::path(logs_path) / (std::string(buffer) + ".log");

    FILE *file;
    file = freopen(log_file_path.string().c_str(), "a", stdout);
    if (file == NULL)
    {
        freopen("/dev/tty", "w", stdout);
        printf("Warning: LogData: can not open stdout log file '%s'\n", log_file_path.string().c_str());
        printf("Info: LogData: stdout redirected to terminal\n");
    }
    else
    {
        printf("Info: LogData: log file for stdout enabled\n");
    }
    file = freopen(log_file_path.string().c_str(), "a", stderr);
    if (file == NULL)
    {
        freopen("/dev/tty", "w", stderr);
        printf("Warning: LogData: can not open stderr log file '%s'\n", log_file_path.string().c_str());
        printf("Info: LogData: stderr redirected to terminal\n");
    }
    else
    {
        printf("Info: LogData: log file for stderr enabled\n");
    }

    LogData::enabledLogFile = true;
}

void LogData::disableLogFile()
{
    printf("Info: LogData: disabling log file...\n");
    if (!LogData::enabledLogFile)
    {
        printf("log file was not enabled\n");
        return;
    }

    freopen("/dev/tty", "w", stdout);
    freopen("/dev/tty", "w", stderr);
    printf("Info: LogData: log file disabled\n");
}