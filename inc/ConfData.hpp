#ifndef CONFDATA_HPP
#define CONFDATA_HPP

#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "JsonRead.hpp"

class ConfData
{
    typedef std::filesystem::path sfp;
    std::string res_path;
    std::string conf_file;

public:
    std::string window_title;
    std::string icon_path;
    sf::Vector2u window_size;
    sf::Vector2i window_position;
    sf::Vector2f window_margin;
    sf::Vector2f schedule_position;
    std::string default_image_file;
    std::string background_image_file;
    std::string schedules_path;
    std::string coords_path;
    std::string font_file;
    std::string state_file;
    unsigned int schedule_fade_mask;
    bool save_schedule_list_logs;
    bool logs_in_cmd;
    bool display_cmd;
    bool reversed_scroll_direction;

    std::string exec_path;
    std::string exec_path_in;
    std::string exec_path_out;
    std::string change_image_exposure_file;
    std::string find_coords_inside_week_schedule_file;
    std::string translate_coords_to_json_file;
    std::string exec_file_extension;

    struct Colors
    {
        struct ButtonColorStates
        {
            sf::Color idle;
            sf::Color hover;
            sf::Color press;
        };
        struct ButtonColorMode
        {
            ButtonColorStates active, deactive;
        };
        struct ButtonColors
        {
            ButtonColorMode deleteMode, standardMode;
        } schedule_buttons;
        sf::Color background;
        ButtonColorStates delete_schedule_button;
        ButtonColorStates add_new_schedule_button;
        sf::Color text;
    } colors;
    std::string schedule_image_extension;
    std::string button_data_extension;
    unsigned int applicationActiveFrameRate;
    unsigned int applicationIdleFrameRate;

private:
    void verifyChangeConf();
    void loadConf();
    std::string buildConfFileTemplate() const;

public:
    ConfData(std::string conf_file);
    ~ConfData();
};

#endif