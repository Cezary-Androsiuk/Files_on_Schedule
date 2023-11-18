#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <SFML/Graphics.hpp>

#include "SimpleGUI.hpp"
#include "ConfData.hpp"
#include "Schedule.hpp"
#include "UpdateSchedule.hpp"

#define DESCRIPTION_CONTENT "\
ESC: Exit Application;   \
Left: Prevoius Week;   \
Right: Next Week;   \
Home: First Week;   \
End: Last Week;   \
Del: Enable/Disable Delete Href Mode;\n\
Plus: Add New Schedule;   \
Minus: Delete This Schedule;   \
Mouse Wheel Scroll: Previous/Next Week\n\
Mouse LB / RB: Open Href Associated With Lesson;    \
Mouse LB: Add File To Lesson;    \
Mouse RB: Add Directory To Lesson;    \
"

#define ADD_SCHEDULE_BUTTON_TEXT "Add New Schedule"
#define ADD_SCHEDULE_BUTTON_TEXT_SIZE 13u

#define DELETE_SCHEDULE_BUTTON_TEXT "Delete This Schedule"
#define DELETE_SCHEDULE_BUTTON_TEXT_SIZE 13u

#define DELETE_SCHEDULE_CONFIRM_COUNTER_VALUE 6
#define DELETE_SCHEDULE_UPDATE_TIME sf::milliseconds(2000)

class Objects
{
    const ConfData *const confdata;
    sf::RenderWindow **const window;

public:
    sf::Font font;

    sgui::Button *deleteScheduleButton;
    sgui::Label *deleteScheduleButtonLabel;
    int deleteScheduleConfirmCounter;
    sf::Clock clock;
    sf::Time deleteScheduleUpdateTime;

    sgui::Button *addScheduleButton;
    sgui::Label *addScheduleButtonLabel;

    sgui::Label *description;

    Schedule *schedule;
    void initData();

public:
    Objects(const ConfData *confdata, sf::RenderWindow **window);
    ~Objects();

private:
    void updateDeleteScheduleButtonText();
    void updateDeleteScheduleConfirmCounter();
    void addScheduleAction();
    void deleteScheduleAction();

public:
    void event(const sf::Event &event);
    void update();
    void render(sf::RenderTarget *window) const;
};

#endif