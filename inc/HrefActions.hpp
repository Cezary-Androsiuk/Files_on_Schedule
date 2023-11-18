#ifndef HREFACTIONS_HPP
#define HREFACTIONS_HPP

#include <cstdio>
#include <string>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#include <ShObjIdl.h>
#endif

#include "SimpleGUI.hpp"

class HrefActions
{
    struct ButtonData
    {
        sgui::Button *button;
        std::string href;
    };
    static void addFileHrefActionLinux(ButtonData *bd);
    static void addFileHrefActionWindows(ButtonData *bd);
    static void addDirHrefActionLinux(ButtonData *bd);
    static void addDirHrefActionWindows(ButtonData *bd);

public:
    static void useHrefsAction(void *bd);
    static void addFileHrefAction(void *bd);
    static void addDirHrefAction(void *bd);
    static void deleteHrefsAction(void *bd);
};

#endif