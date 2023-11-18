#include <Window.hpp>

void Window::initData()
{
    if (!std::filesystem::exists(RES_PATH))
    {
        printf("Error: Window: missing rerource path\n");
        printf("Info: Window: exiting ...\n");
        std::cin.get();
        exit(1);
    }

    if (std::filesystem::exists(RES_PATH / ONE_RUN_AT_ONCE_FILE))
    {
        printf("Error: Window: application is already running\n");
        printf("Quick Tip: Window: if you know that application is not opened right now, ");
        printf("open '%s' file in notepad, read what is inside and then delete\n",
               (std::filesystem::current_path() / RES_PATH / ONE_RUN_AT_ONCE_FILE).string().c_str());
        printf("Info: Window: exiting ...\n");
        std::cin.get();
        exit(1);
    }
    else
    {
        std::fstream file(RES_PATH / ONE_RUN_AT_ONCE_FILE, std::ios::out);
        file << "APPLICATION MIGHT STILL OPENED :)\nIF SO, DO NOT DELETE THIS FILE TO AVOID SCHEDULE DATA CORRUPTION!\n";
        file.close();
    }

    this->confdata = new const ConfData((RES_PATH / CONF_FILE).string());

    if (!this->confdata->display_cmd)
    {
        // if(this->confdata->display_cmd){
#ifdef linux
        printf("Warning: Window: unable to change visibility of terminal in Linux\n");
#elif _WIN32
        // disable visibility of terminal
        HWND hWnd = GetConsoleWindow();
        ShowWindow(hWnd, SW_HIDE);

        // // enable visibility of terminal
        // HWND hWnd = GetConsoleWindow();
        // ShowWindow(hWnd, SW_RESTORE);
#endif
    }
    if (!this->confdata->logs_in_cmd)
        LogData::enableLogFile(RES_PATH / LOGS_PATH);

    this->objects = new Objects(this->confdata, &this->window);

    printf("Info: Window: data initialized\n");
}

void Window::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    unsigned int window_x_size = this->confdata->window_size.x + this->confdata->window_margin.x;
    unsigned int window_y_size = this->confdata->window_size.y + this->confdata->window_margin.y;
    this->window = new sf::RenderWindow(
        sf::VideoMode(window_x_size, window_y_size), this->confdata->window_title.c_str(), sf::Style::Close, settings);
    this->window->clear(sf::Color(30, 30, 30));
    // fflush output to file because here opengl can display warning "Setting vertical sync not supported" and this is only stderr in application
    fflush(stdout);
    fflush(stderr);

    // printf("%d %d\n", this->window->getPosition().x, this->window->getPosition().y);
    this->window->setPosition(this->confdata->window_position);

    sf::Image icon;
    if (icon.loadFromFile(this->confdata->icon_path))
    {
        this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else
    {
        printf("Warning: Window: can not load icon '%s'\n", this->confdata->icon_path.c_str());
    }
    printf("Info: Window: window initialized\n");
}

void Window::deletingObjects()
{
    delete this->objects;
    delete this->confdata;
    if (std::filesystem::exists(RES_PATH / ONE_RUN_AT_ONCE_FILE))
    {
        std::filesystem::remove(RES_PATH / ONE_RUN_AT_ONCE_FILE);
    }
    else
    {
        printf("Warning: Window: file '%s' was already deleted. Schedule data might be corrupted!\n", (RES_PATH / ONE_RUN_AT_ONCE_FILE).string().c_str());
    }
    printf("Info: Window: objects deleted\n");
}

Window::Window(const int argc, const char **argv)
{
    printf("Info: Window: constructing objects\n");
    this->initData();
    this->initWindow();
    printf("Info: Window: objects correctly constructed\n");
}

Window::~Window()
{
    printf("Info: Window: deconstructing objects...\n");
    delete this->window;
    this->deletingObjects();
    printf("Info: Window: objects correctly deconstructed\n");
    LogData::disableLogFile();
}

void Window::update_event()
{
    while (this->window->pollEvent(this->event))
    {
        if (event.type == sf::Event::Closed)
        {
            this->window->close();
            printf("Info: Window:   event: Closed\n");
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            this->window->close();
            printf("Info: Window:   event: KeyPressed, key: Keyboard: Escape\n");
        }

        this->objects->event(this->event);
    }
}

void Window::update_window()
{
    if (this->window->hasFocus())
        this->window->setFramerateLimit(this->confdata->applicationActiveFrameRate);
    else
        this->window->setFramerateLimit(this->confdata->applicationIdleFrameRate);
}

void Window::update()
{
    this->update_window();
    this->update_event();
    this->objects->update();
}

void Window::render() const
{
    this->window->clear(this->confdata->colors.background);

    this->objects->render(window);

    this->window->display();
}

const bool Window::running() const
{
    return this->window->isOpen();
}