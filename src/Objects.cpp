#include "Objects.hpp"

void Objects::initData()
{
    this->schedule = new Schedule(this->confdata, *this->window);

    if (!this->font.loadFromFile(this->confdata->font_file))
    {
        printf("ERROR: Objects: error while loading font '%s'\n", this->confdata->font_file.c_str());
        printf("exiting...\n");
        exit(1);
    }

    this->description = new sgui::Label(
        sf::Vector2f(0.f, 885.f),
        sf::Text(DESCRIPTION_CONTENT, this->font, 12U));
    this->description->setColor(this->confdata->colors.text);

    this->deleteScheduleButton = new sgui::Button();
    this->deleteScheduleButton->setPosition(sf::Vector2f(
        this->confdata->window_margin.x + 160.f,
        this->confdata->window_margin.x / 2));
    this->deleteScheduleButton->setSize(sf::Vector2f(160, 30.f));
    this->deleteScheduleButton->setColor(this->confdata->colors.delete_schedule_button.idle);
    this->deleteScheduleButton->setColorHover(this->confdata->colors.delete_schedule_button.hover);
    this->deleteScheduleButton->setColorPress(this->confdata->colors.delete_schedule_button.press);
    this->deleteScheduleConfirmCounter = DELETE_SCHEDULE_CONFIRM_COUNTER_VALUE;
    this->deleteScheduleUpdateTime = DELETE_SCHEDULE_UPDATE_TIME;

    this->deleteScheduleButtonLabel = new sgui::Label();
    this->deleteScheduleButtonLabel->setColor(this->confdata->colors.text);
    this->updateDeleteScheduleButtonText();

    this->addScheduleButton = new sgui::Button();
    this->addScheduleButton->setPosition(sf::Vector2f(
        this->confdata->window_margin.x / 2,
        this->confdata->window_margin.x / 2));
    this->addScheduleButton->setSize(sf::Vector2f(160.f, 30.f));
    this->addScheduleButton->setColor(this->confdata->colors.add_new_schedule_button.idle);
    this->addScheduleButton->setColorHover(this->confdata->colors.add_new_schedule_button.hover);
    this->addScheduleButton->setColorPress(this->confdata->colors.add_new_schedule_button.press);

    this->addScheduleButtonLabel = new sgui::Label(
        sf::Vector2f(
            this->confdata->window_margin.x / 2 + 14 + 2,
            this->confdata->window_margin.x / 2 + 4 + 2),
        sf::Text(
            ADD_SCHEDULE_BUTTON_TEXT,
            this->font,
            ADD_SCHEDULE_BUTTON_TEXT_SIZE));
    this->addScheduleButtonLabel->getText().setStyle(sf::Text::Style::Bold);
    this->addScheduleButtonLabel->setColor(this->confdata->colors.text);

    printf("Info: Objects: data initialized\n");
}

Objects::Objects(const ConfData *confdata, sf::RenderWindow **window) : confdata(confdata), window(window)
{
    printf("Info: Objects: constructing objects\n");
    this->initData();
    printf("Info: Objects: objects correctly constructed\n");
}
Objects::~Objects()
{
    printf("Info: Objects: deconstructing objects...\n");
    delete this->addScheduleButton;
    delete this->deleteScheduleButton;
    delete this->description;
    delete this->schedule;
    printf("Info: Objects: objects correctly deconstructed\n");
}

void Objects::updateDeleteScheduleButtonText()
{
    if (this->deleteScheduleConfirmCounter == DELETE_SCHEDULE_CONFIRM_COUNTER_VALUE)
    {
        this->deleteScheduleButtonLabel->setText(
            sf::Text(
                DELETE_SCHEDULE_BUTTON_TEXT,
                this->font,
                DELETE_SCHEDULE_BUTTON_TEXT_SIZE));
        this->deleteScheduleButtonLabel->setPosition(
            sf::Vector2f(
                this->confdata->window_margin.x + 160.f + 4.f + 2,
                this->confdata->window_margin.x / 2 + 4.f + 2));
    }
    else
    {
        this->deleteScheduleButtonLabel->setText(
            sf::Text(
                std::to_string(deleteScheduleConfirmCounter),
                this->font,
                DELETE_SCHEDULE_BUTTON_TEXT_SIZE));
        this->deleteScheduleButtonLabel->setPosition(
            sf::Vector2f(
                this->confdata->window_margin.x + 160.f + 73.f + 2,
                this->confdata->window_margin.x / 2 + 4.f + 2));
    }
    this->deleteScheduleButtonLabel->getText().setStyle(sf::Text::Style::Bold);
}   

void Objects::updateDeleteScheduleConfirmCounter()
{
    if (this->deleteScheduleConfirmCounter == DELETE_SCHEDULE_CONFIRM_COUNTER_VALUE)
    {
        this->deleteScheduleUpdateTime = DELETE_SCHEDULE_UPDATE_TIME;
        return;
    }

    if (this->clock.getElapsedTime().asMilliseconds() >= this->deleteScheduleUpdateTime.asMilliseconds())
    {
        this->deleteScheduleConfirmCounter++;
        this->updateDeleteScheduleButtonText();
        this->deleteScheduleUpdateTime = sf::milliseconds(
            DELETE_SCHEDULE_UPDATE_TIME.asMilliseconds() / 4);
        this->clock.restart();
        printf("Info: Objects: delete schedule confirm counter incremented to %d\n",
               this->deleteScheduleConfirmCounter);
    }
}

void Objects::addScheduleAction()
{
    printf("Info: Objects: adding schedule ...\n");
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Wait))
        (*this->window)->setMouseCursor(cursor);

    delete this->schedule;
    
    try
    {
        UpdateSchedule::addNewSchedule(this->confdata);
    }
    catch(const std::exception& e)
    {
        printf("Error: Objects: error while adding schedule  error: %s\n", e.what());
    }
    

    this->schedule = new Schedule(this->confdata, *this->window);

    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        (*this->window)->setMouseCursor(cursor);
    
    printf("Info: Objects: adding schedule finished\n");
}

void Objects::deleteScheduleAction()
{
    this->deleteScheduleConfirmCounter--;
    this->updateDeleteScheduleButtonText();
    this->clock.restart();

    printf("Info: Objects: delete schedule confirm counter decremented to %d\n",
           this->deleteScheduleConfirmCounter);

    if (this->deleteScheduleConfirmCounter > 0)
        return;

    this->deleteScheduleConfirmCounter = DELETE_SCHEDULE_CONFIRM_COUNTER_VALUE;
    this->updateDeleteScheduleButtonText();

    printf("Info: Objects: deleting schedule ...\n");
    delete this->schedule;

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Wait))
        (*this->window)->setMouseCursor(cursor);

    try
    {
        UpdateSchedule::deleteRecentlyOpenedSchedule(this->confdata);
    }
    catch(const std::exception& e)
    {
        printf("Error: Objects: error while deleting schedule  error: %s\n", e.what());
    }

    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        (*this->window)->setMouseCursor(cursor);

    this->schedule = new Schedule(this->confdata, *this->window);

    printf("Info: Objects: deleting schedule finished\n");
}

void Objects::event(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add))
    {
        this->addScheduleAction();
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: + sign (Equal or Add)\n");
    }
    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract))
    {
        this->deleteScheduleAction();
        printf("Info: Schedule:   event: KeyPressed, key: Keyboard: - sign (Hyphen or Subtract)\n");
    }

    this->addScheduleButton->event(event);
    this->deleteScheduleButton->event(event);
    this->addScheduleButtonLabel->event(event);
    this->deleteScheduleButtonLabel->event(event);

    this->description->event(event);
    this->schedule->event(event);
}
void Objects::update()
{
    this->addScheduleButton->update();
    this->deleteScheduleButton->update();
    this->addScheduleButtonLabel->update();
    this->deleteScheduleButtonLabel->update();

    if (this->addScheduleButton->getClick())
        this->addScheduleAction();
    if (this->deleteScheduleButton->getClick())
        this->deleteScheduleAction();

    this->updateDeleteScheduleConfirmCounter();

    this->description->update();
    this->schedule->update();
}
void Objects::render(sf::RenderTarget *window) const
{
    this->addScheduleButton->render(window);
    this->deleteScheduleButton->render(window);
    this->addScheduleButtonLabel->render(window);
    this->deleteScheduleButtonLabel->render(window);

    this->description->render(window);
    this->schedule->render(window);
}
