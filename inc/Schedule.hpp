#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <cstdio>
#include <fstream>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "SimpleGUI.hpp"
#include "ConfData.hpp"
#include "JsonRead.hpp"
#include "HrefActions.hpp"

#define STATE_FILE "./res/state.json"
#define STATE_FILE_ARG_01_DEFAULT 0

class Schedule
{
    typedef std::filesystem::path sfp;
    const ConfData *const confdata;
    sf::RenderWindow *const window;
    sf::Font font;
    // public:
    struct SchedulePage
    {
        size_t previous;
        size_t current;
        size_t next;
    } schedule_page;

    std::vector<std::string> schedule_list;

    enum ActionState
    {
        UseHrefState,
        DeleteHrefState
    } actionState;
    bool actionStateChanged;

    struct ButtonData
    {
        sgui::Button *button;
        std::string href;
    };
    std::vector<ButtonData> buttons_single_lesson;

    sgui::ImageBox *imageBox_schedule, *imageBox_schedule_background;
    sf::RectangleShape *schedule_fade_mask;
    sgui::Label *label_date;
    sgui::Label *deleteModeInfo;
    bool empty_container_protection;

private:
    void loadState();
    void initObjects();

    void saveState();

public:
    Schedule(const ConfData *confData, sf::RenderWindow *window);
    ~Schedule();

private:
    void saveButtonData();
    void loadButtonData();
    void setButtonColor(ButtonData *bd);
    void updateSchedule();

    inline void schedulePageChangeToRight();
    inline void schedulePageChangeToLeft();

public:
    void event(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *window) const;
};

#endif