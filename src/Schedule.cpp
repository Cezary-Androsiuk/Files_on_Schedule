#include "Schedule.hpp"

void Schedule::loadState()
{
    Json state_json;
    std::ifstream ifile(this->confdata->state_file);
    if (ifile.good())
    {
        ifile >> state_json;
        ifile.close();
        JsonRead::toVar(state_json, {"Current Page"}, this->schedule_page.current);
    }
    else
    {
        this->schedule_page.current = STATE_FILE_ARG_01_DEFAULT;
        printf("Warning: Schedule: can not open '%s' setted all states to DEFAULT\n", this->confdata->state_file.c_str());
    }

    this->schedule_page.previous = SIZE_MAX;
    this->schedule_page.next = this->schedule_page.current;
    printf("Info: Schedule: schedule state loaded\n");
}

void Schedule::initObjects()
{

    if (!this->font.loadFromFile(confdata->font_file))
    {
        printf("Warning: Schedule: can not load font from '%s'\n", confdata->font_file.c_str());
    }

    if (this->confdata->save_schedule_list_logs)
        printf("Info: Schedule: loading available schedules :\n\t[");
    int scheduleIndex = 0;
    for (const auto &file : std::filesystem::directory_iterator(this->confdata->schedules_path))
    {
        std::string scheduleFileName = file.path().filename().stem().string();
        this->schedule_list.push_back(scheduleFileName);
        if (this->confdata->save_schedule_list_logs)
            printf("%4d: %s, ", scheduleIndex++, scheduleFileName.c_str());
    }
    if (this->confdata->save_schedule_list_logs)
        printf("]\n");

    this->empty_container_protection = false;
    if (this->schedule_list.empty())
    {
        printf("Info: Schedule: empty container protection enabled\n");
        this->empty_container_protection = true;
        return;
    }

    if (this->schedule_page.current > this->schedule_list.size() - 1)
        this->schedule_page.next = this->schedule_list.size() - 1;

    std::sort(this->schedule_list.begin(), this->schedule_list.end());

    this->imageBox_schedule = new sgui::ImageBox(this->confdata->default_image_file.c_str());
    this->imageBox_schedule->setPosition(this->confdata->schedule_position);

    this->imageBox_schedule_background = new sgui::ImageBox(this->confdata->background_image_file.c_str());
    this->imageBox_schedule_background->setPosition(this->confdata->schedule_position);

    this->schedule_fade_mask = new sf::RectangleShape(
        sf::Vector2f(this->imageBox_schedule_background->getSize()));
    this->schedule_fade_mask->setPosition(this->imageBox_schedule_background->getPosition());
    this->schedule_fade_mask->setFillColor(
        sf::Color(
            this->confdata->colors.background.r,
            this->confdata->colors.background.g,
            this->confdata->colors.background.b,
            this->confdata->schedule_fade_mask));

    this->label_date = new sgui::Label(
        sf::Vector2f(this->confdata->window_margin.x / 2, 40.f),
        sf::Text(
            "", this->font, 30U));
    this->label_date->setFont(this->font);
    this->label_date->setColor(this->confdata->colors.text);

    this->deleteModeInfo = new sgui::Label(
        sf::Vector2f(
            this->confdata->window_size.x / 2 + this->confdata->window_margin.x / 2 - 110.f,
            this->confdata->schedule_position.y + 20.f),
        sf::Text(
            "DELETE MODE",
            this->font,
            40U));
    this->deleteModeInfo->setColor(sf::Color(255, 0, 0, 150));

    this->actionState = ActionState::UseHrefState;
    this->actionStateChanged = false;

    this->updateSchedule();
}

void Schedule::saveState()
{
    Json state_json;
    state_json["Current Page"] = this->schedule_page.current;

    std::ofstream ofile(this->confdata->state_file);
    ofile << state_json.dump(4);
    ofile.close();
    printf("Info: Schedule: application state was saved to '%s'\n", this->confdata->state_file.c_str());
}

Schedule::Schedule(const ConfData *confdata, sf::RenderWindow *window) : confdata(confdata), window(window)
{
    printf("Info: Schedule: constructing objects\n");
    this->loadState();
    this->initObjects();
    printf("Info: Schedule: objects correctly constructed\n");
}

Schedule::~Schedule()
{
    printf("Info: Schedule: deconstructing objects...\n");
    if (this->empty_container_protection)
    {
        printf("Info: Schedule: objects correctly deconstructed by using empty containter protection\n");
        return;
    }
    this->saveState();
    this->saveButtonData();

    delete this->schedule_fade_mask;
    delete this->imageBox_schedule_background;
    delete this->imageBox_schedule;
    delete this->label_date;
    delete this->deleteModeInfo;

    for (const auto &b : this->buttons_single_lesson)
        delete b.button;
    printf("Info: Schedule: objects correctly deconstructed\n");
}

void Schedule::saveButtonData()
{
    printf("Info: Schedule: saving buttons data: last page: %ld, current page: %ld, next page: %ld, existing buttons: %ld\n",
           this->schedule_page.previous, this->schedule_page.current, this->schedule_page.next, this->buttons_single_lesson.size());

    // to avoid saving data right at application start
    if (this->schedule_page.previous == SIZE_MAX)
    {
        printf("Info: Schedule: saved was skipped\n");
        return;
    }

    Json button_json;
    for (const auto &bd : this->buttons_single_lesson)
    {
        std::string button_name = bd.button->getName();
        auto pos = bd.button->getPosition() - this->confdata->schedule_position;
        ;
        button_json[button_name]["rect"]["left"] = pos.x;
        button_json[button_name]["rect"]["top"] = pos.y;
        auto size = bd.button->getSize();
        button_json[button_name]["rect"]["width"] = size.x;
        button_json[button_name]["rect"]["height"] = size.y;
        button_json[button_name]["href"] = bd.href;
        printf("Info: Schedule: %s data was storred in json variable\n", button_name.c_str());
    }

    auto list_name = this->schedule_list[this->schedule_page.current];
    if (!list_name.empty())
    {
        auto buttons_file = sfp(this->confdata->coords_path) / (list_name + this->confdata->button_data_extension);
        std::ofstream ofile(buttons_file);
        if (!ofile.good())
        {
            printf("Warning: Schedule: can not save button data file '%s'\n", buttons_file.string().c_str());
            return;
        }
        ofile << button_json.dump(4);
        ofile.close();
        printf("Info: Schedule: all buttons was saved in '%s'\n", buttons_file.string().c_str());
    }
    else
    {
        printf("Warning: Schedule: button data will not be saved, because list_name is empty.\n");
    }
}

void Schedule::loadButtonData()
{
    printf("Info: Schedule: reading button data from '%s' ...\n",
           (this->schedule_list[this->schedule_page.current] + this->confdata->button_data_extension).c_str());
    auto list_name = this->schedule_list[this->schedule_page.current];
    auto button_file = sfp(this->confdata->coords_path) / (list_name + this->confdata->button_data_extension);
    Json button_json;
    std::ifstream ifile(button_file);
    if (!ifile.good())
    {
        printf("Warning: Schedule: can not read button data file '%s'\n", button_file.string().c_str());
        return;
    }
    ifile >> button_json;
    ifile.close();
    printf("Info: Schedule: button data was storred in json variable\n");

    for (auto &button : button_json.items())
    {
        if (button.key().find("Button_", 0) == 0)
        {
            sf::FloatRect buttonBounds;
            JsonRead::toVar(button.value(), {"rect"}, buttonBounds);
            buttonBounds.left += this->confdata->schedule_position.x;
            buttonBounds.top += this->confdata->schedule_position.y;

            ButtonData bd = {
                .button = new sgui::Button(buttonBounds, button.key())};
            JsonRead::toVar(button.value(), {"href"}, bd.href);

            this->setButtonColor(&bd);

            this->buttons_single_lesson.push_back(bd);
            printf("Info: Schedule: %s data was setted\n", button.key().c_str());
        }
    }
    printf("Info: Schedule: all buttons was loaded\n");
}

void Schedule::setButtonColor(ButtonData *bd)
{
    const int ButtonActive = 1u << 7; // button contains at least one href
    int buttonState = this->actionState;
    if (!bd->href.empty())
        buttonState |= ButtonActive;

    switch (buttonState)
    {
    case ActionState::UseHrefState | ButtonActive:
        bd->button->setColor(this->confdata->colors.schedule_buttons.standardMode.active.idle);
        bd->button->setColorHover(this->confdata->colors.schedule_buttons.standardMode.active.hover);
        bd->button->setColorPress(this->confdata->colors.schedule_buttons.standardMode.active.press);
        break;
    case ActionState::DeleteHrefState | ButtonActive:
        bd->button->setColor(this->confdata->colors.schedule_buttons.deleteMode.active.idle);
        bd->button->setColorHover(this->confdata->colors.schedule_buttons.deleteMode.active.hover);
        bd->button->setColorPress(this->confdata->colors.schedule_buttons.deleteMode.active.press);
        break;
    case ActionState::UseHrefState:
        bd->button->setColor(this->confdata->colors.schedule_buttons.standardMode.deactive.idle);
        bd->button->setColorHover(this->confdata->colors.schedule_buttons.standardMode.deactive.hover);
        bd->button->setColorPress(this->confdata->colors.schedule_buttons.standardMode.deactive.press);
        break;
    case ActionState::DeleteHrefState:
        bd->button->setColor(this->confdata->colors.schedule_buttons.deleteMode.deactive.idle);
        bd->button->setColorHover(this->confdata->colors.schedule_buttons.deleteMode.deactive.hover);
        bd->button->setColorPress(this->confdata->colors.schedule_buttons.deleteMode.deactive.press);
        break;

    default:
        break;
    }

    printf("Info: Schedule: %s color setted to:   active: %s   state: %s%s\n",
           bd->button->getName().toAnsiString().c_str(),
           (ButtonActive ? "true" : "false"),
           (this->actionState == ActionState::UseHrefState ? "UseHrefState" : ""),
           (this->actionState == ActionState::DeleteHrefState ? "DeleteHrefState" : ""));
}

void Schedule::updateSchedule()
{
    printf("Info: Schedule: changing schedule from %ld to page %ld with name '%s' ...\n",
           this->schedule_page.current, this->schedule_page.next, this->schedule_list[this->schedule_page.next].c_str());
    fflush(stdout);
    this->saveButtonData();

    // update control values
    this->actionStateChanged = false;
    this->schedule_page.previous = this->schedule_page.current;
    this->schedule_page.current = this->schedule_page.next;

    auto current_schedule_name = schedule_list[this->schedule_page.current];
    sfp schedule_path = sfp(this->confdata->schedules_path) / (current_schedule_name + this->confdata->schedule_image_extension);

    this->imageBox_schedule->setImagePath(schedule_path.string().c_str());

    this->label_date->setText(
        sf::Text(
            (
                current_schedule_name + "    " +
                std::to_string(this->schedule_page.current + 1) + "/" +
                std::to_string(this->schedule_list.size()))
                .c_str(),
            this->font));

    for (auto b : this->buttons_single_lesson)
        delete b.button;
    this->buttons_single_lesson.clear();

    this->loadButtonData();

    printf("Info: Schedule: changed schedule to page %ld with name '%s'\n",
           this->schedule_page.current, this->schedule_list[this->schedule_page.current].c_str());
}

inline void Schedule::schedulePageChangeToRight()
{
    if (this->schedule_page.next < this->schedule_list.size() - 1)
        this->schedule_page.next++;
}

inline void Schedule::schedulePageChangeToLeft()
{
    if (this->schedule_page.next > 0)
        this->schedule_page.next--;
}

void Schedule::event(const sf::Event &event)
{
    if (this->empty_container_protection)
        return;

    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0) // up
        {
            if (this->confdata->reversed_scroll_direction)
                this->schedulePageChangeToLeft();
            else
                this->schedulePageChangeToRight();
            printf("Info: Schedule:   event: MouseWheelScrolled, delta: + (wheel moved up)\n");
        }
        else if (event.mouseWheelScroll.delta < 0) // down
        {
            if (this->confdata->reversed_scroll_direction)
                this->schedulePageChangeToRight();
            else
                this->schedulePageChangeToLeft();
            printf("Info: Schedule:   event: MouseWheelScrolled, delta: - (wheel moved down)\n");
        }
    }
    else if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left))
    {
        this->schedulePageChangeToLeft();
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: Left\n");
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
    {
        this->schedulePageChangeToRight();
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: Right\n");
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Home)
    {
        this->schedule_page.next = 0;
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: Home\n");
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::End)
    {
        this->schedule_page.next = this->schedule_list.size() - 1;
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: End\n");
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete)
    {
        switch (this->actionState)
        {
        case ActionState::UseHrefState:
            this->actionState = ActionState::DeleteHrefState;
            break;
        case ActionState::DeleteHrefState:
            this->actionState = ActionState::UseHrefState;
            break;
        }
        this->actionStateChanged = true;
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: Delete\n");
    }
    this->imageBox_schedule_background->event(event);
    this->imageBox_schedule->event(event);
    this->label_date->event(event);
    this->deleteModeInfo->event(event);

    for (const auto &b : this->buttons_single_lesson)
        b.button->event(event);
}

void Schedule::update()
{
    if (this->empty_container_protection)
        return;

    this->imageBox_schedule_background->update();

    if (this->schedule_page.current != this->schedule_page.next || this->actionStateChanged)
    {
        this->updateSchedule();
    }

    this->imageBox_schedule->update();
    this->label_date->update();
    this->deleteModeInfo->update();

    for (const auto &b : this->buttons_single_lesson)
        b.button->update();

    for (auto &bd : this->buttons_single_lesson)
    {
        if (bd.button->getClick())
        {
            printf("Info: Schedule: %s pressed\n",
                   bd.button->getName().toAnsiString().c_str());
            const int ButtonActive = 1u << 7;
            int buttonState = this->actionState;
            if (!bd.href.empty())
                buttonState |= ButtonActive;

            switch (buttonState)
            {
            case ActionState::UseHrefState | ButtonActive:
                HrefActions::useHrefsAction(&bd);
                break;
            case ActionState::UseHrefState:
                if (bd.button->getButtonType()) // left button
                    HrefActions::addFileHrefAction(&bd);
                else // right button
                    HrefActions::addDirHrefAction(&bd);
                break;
            case ActionState::DeleteHrefState | ButtonActive:
                HrefActions::deleteHrefsAction(&bd);
                break;
            case ActionState::DeleteHrefState:
                printf("Warning: Schedule: this button does not have any hrefs associated\n");
                break;

            default:
                break;
            }
            this->setButtonColor(&bd);
        }
    }
}

void Schedule::render(sf::RenderTarget *window) const
{
    if (this->empty_container_protection)
        return;

    this->imageBox_schedule_background->render(window);
    this->imageBox_schedule->render(window);
    this->label_date->render(window);
    if (this->actionState == ActionState::DeleteHrefState)
        this->deleteModeInfo->render(window);

    window->draw(*this->schedule_fade_mask);

    for (const auto &b : this->buttons_single_lesson)
        b.button->render(window);
}
