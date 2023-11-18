#ifndef LOGDATA_HPP
#define LOGDATA_HPP

#include <cstdio>
#include <string>
#include <chrono>
// #include <fstream>
#include <filesystem>

class LogData
{
    // solution from https://stackoverflow.com/questions/16284629/undefined-reference-to-static-variable-c
    static bool enabledLogFile;

    // // std::cout   std::cerr
    // std::ofstream log_file;
    // std::streambuf *org_cout;
    // std::streambuf *org_cerr;

public:
    static void enableLogFile(std::filesystem::path logs_path);
    static void disableLogFile();
};

#endif