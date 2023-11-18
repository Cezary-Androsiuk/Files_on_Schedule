#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#endif

#include <SFML/Graphics.hpp>

#include "LogData.hpp"
#include "ConfData.hpp"
#include "Objects.hpp"

#define RES_PATH sfp("res")
#define ONE_RUN_AT_ONCE_FILE std::string("app_is_running.info")
#define LOGS_PATH sfp("logs")
#define CONF_FILE std::string("conf.json")

class Window
{
    typedef std::filesystem::path sfp;

    const ConfData *confdata;

    sf::RenderWindow *window;
    sf::Event event;

    Objects *objects;

    void initData();
    void initWindow();

    void deletingObjects();

public:
    Window(const int argc, const char **argv);
    ~Window();

private:
    void update_event();
    void update_window();

public:
    void update();
    void render() const;

    const bool running() const;
};

#endif