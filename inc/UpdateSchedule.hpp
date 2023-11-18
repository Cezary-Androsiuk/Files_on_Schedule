#ifndef UPDATESCHEDULE_HPP
#define UPDATESCHEDULE_HPP

#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#endif

#include "ConfData.hpp"
#include "JsonRead.hpp"

class UpdateSchedule
{
    typedef std::filesystem::path sfp;
    static size_t getRecentlyOpenedScheduleId(const ConfData *const confdata);
    static std::string getScheduleNameById(const ConfData *const confdata, size_t id);
    static int checkifAllFilesExist(const ConfData *const confdata, std::string name);

public:
    static void deleteRecentlyOpenedSchedule(const ConfData *const confdata);

private:
    static int askforFileName(std::string &file);
    static int runExec(const std::string &file, std::vector<std::string> args);
    static int runPython(const std::string &file);

public:
    static void addNewSchedule(const ConfData *const confdata);
};

#endif