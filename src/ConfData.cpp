#include "ConfData.hpp"

ConfData::ConfData(std::string conf_file)
{
    printf("Info: ConfData: constructing objects\n");
    this->res_path = sfp(conf_file).parent_path().string();
    this->conf_file = sfp(conf_file).filename().string();
    this->loadConf();
    printf("Info: ConfData: objects correctly constructed\n");
}
ConfData::~ConfData()
{
    printf("Info: ConfData: deconstructing objects...\n");
    printf("Info: ConfData: objects correctly deconstructed\n");
}

void ConfData::verifyChangeConf()
{
    printf("Info: ConfData: configuration verifying ...\n");
    if (!this->icon_path.empty())
        this->icon_path = (sfp(this->res_path) / this->icon_path).string();

    if (!this->default_image_file.empty())
        this->default_image_file = (sfp(this->res_path) / this->default_image_file).string();

    if (!this->background_image_file.empty())
        this->background_image_file = (sfp(this->res_path) / this->background_image_file).string();

    if (!this->schedules_path.empty())
        this->schedules_path = (sfp(this->res_path) / this->schedules_path).string();

    if (!this->coords_path.empty())
        this->coords_path = (sfp(this->res_path) / this->coords_path).string();

    if (!this->font_file.empty())
        this->font_file = (sfp(this->res_path) / this->font_file).string();

    if (!this->state_file.empty())
        this->state_file = (sfp(this->res_path) / this->state_file).string();

    if (!this->exec_path.empty())
        this->exec_path = (sfp(this->res_path) / this->exec_path).string();

    if (!this->exec_path_in.empty())
        this->exec_path_in = (sfp(this->exec_path) / this->exec_path_in).string();

    if (!this->exec_path_out.empty())
        this->exec_path_out = (sfp(this->exec_path) / this->exec_path_out).string();

    // if (!this->change_image_exposure_file.empty())
    //     this->change_image_exposure_file = sfp(this->exec_path) / this->change_image_exposure_file;

    // if (!this->find_coords_inside_week_schedule_file.empty())
    //     this->find_coords_inside_week_schedule_file = sfp(this->exec_path) / this->find_coords_inside_week_schedule_file;

    // if (!this->translate_coords_to_json_file.empty())
    //     this->translate_coords_to_json_file = sfp(this->exec_path) / this->translate_coords_to_json_file;

    this->schedule_fade_mask = (this->schedule_fade_mask > 255 ? 255 : this->schedule_fade_mask);
    printf("Info: ConfData: configuration verified\n");
}

void ConfData::loadConf()
{
    int retry_counter = 0;
    Json conf_json;
    sfp conf_file_path = sfp(this->res_path) / this->conf_file;
    std::ifstream ifile(conf_file_path);
    while (!ifile.good() && retry_counter < 2)
    {
        if (retry_counter == 1)
        {
            printf("ERROR: ConfData: can not open created data template file!\n");
            printf("Info: ConfData: exiting...\n");
            exit(1);
        }
        printf("Warning: ConfData: can not open data file '%s'!\n", conf_file_path.string().c_str());
        printf("Info: ConfData: creating data file template...\n");
        std::ofstream ofile(conf_file_path);
        if (!ofile.good())
        {
            printf("ERROR: ConfData: can not create data file template!\n");
            printf("Info: ConfData: exiting...\n");
            exit(1);
        }
        printf("Info: ConfData: created '%s' file template successfully\n", conf_file_path.string().c_str());

        ofile << this->buildConfFileTemplate();
        ofile.close();
        ifile.open(conf_file_path);
        retry_counter++;
    }
    ifile >> conf_json;
    ifile.close();
    printf("Info: ConfData: configuration loaded from '%s'\n", (this->res_path + this->conf_file).c_str());
#define JTC JsonRead::toVar(conf_json
    JTC, {"Window Title"}, this->window_title);
    JTC, {"Icon Path"}, this->icon_path);
    JTC, {"Window Size"}, this->window_size);
    JTC, {"Window Position"}, this->window_position);
    JTC, {"Window Margin"}, this->window_margin);
    JTC, {"Schedule Position"}, this->schedule_position);
    JTC, {"Default Image File"}, this->default_image_file);
    JTC, {"Background Image File"}, this->background_image_file);
    JTC, {"Schedules Path"}, this->schedules_path);
    JTC, {"Coords Path"}, this->coords_path);
    JTC, {"Font File"}, this->font_file);
    JTC, {"State File"}, this->state_file);
    JTC, {"Frame Rate", "active"}, this->applicationActiveFrameRate);
    JTC, {"Frame Rate", "idle"}, this->applicationIdleFrameRate);
    JTC, {"Schedule Image Extension"}, this->schedule_image_extension);
    JTC, {"Button Data Extension"}, this->button_data_extension);
    JTC, {"Schedule Fade Mask"}, this->schedule_fade_mask);
    JTC, {"Log Save Schedule List"}, this->save_schedule_list_logs);
    JTC, {"Logs In CMD"}, this->logs_in_cmd);
    JTC, {"Display CMD"}, this->display_cmd);
    JTC, {"Reverse Scroll Direction"}, this->reversed_scroll_direction);
    JTC, {"Exec Path"}, this->exec_path);
    JTC, {"Exec Path Input"}, this->exec_path_in);
    JTC, {"Exec Path Output"}, this->exec_path_out);
    JTC, {"Exec Files", "change image exposure"}, this->change_image_exposure_file);
    JTC, {"Exec Files", "find coords inside week schedule"}, this->find_coords_inside_week_schedule_file);
    JTC, {"Exec Files", "translate coords to json"}, this->translate_coords_to_json_file);

#ifdef linux
    JTC, {"Exec Files Extension", "linux"}, this->exec_file_extension);
#elif _WIN32
    JTC, {"Exec Files Extension", "windows"}, this->exec_file_extension);
#endif

    JTC, {"Colors", "Text"}, this->colors.text);
    JTC, {"Colors", "Background"}, this->colors.background);
    JTC, {"Colors", "Delete Schedule Button", "idle"}, this->colors.delete_schedule_button.idle);
    JTC, {"Colors", "Delete Schedule Button", "hover"}, this->colors.delete_schedule_button.hover);
    JTC, {"Colors", "Delete Schedule Button", "press"}, this->colors.delete_schedule_button.press);
    JTC, {"Colors", "Add New Schedule Button", "idle"}, this->colors.add_new_schedule_button.idle);
    JTC, {"Colors", "Add New Schedule Button", "hover"}, this->colors.add_new_schedule_button.hover);
    JTC, {"Colors", "Add New Schedule Button", "press"}, this->colors.add_new_schedule_button.press);

    JTC, {"Colors", "Buttons", "DeleteMode", "Active", "idle"}, this->colors.schedule_buttons.deleteMode.active.idle);
    JTC, {"Colors", "Buttons", "DeleteMode", "Active", "hover"}, this->colors.schedule_buttons.deleteMode.active.hover);
    JTC, {"Colors", "Buttons", "DeleteMode", "Active", "press"}, this->colors.schedule_buttons.deleteMode.active.press);

    JTC, {"Colors", "Buttons", "DeleteMode", "Deactive", "idle"}, this->colors.schedule_buttons.deleteMode.deactive.idle);
    JTC, {"Colors", "Buttons", "DeleteMode", "Deactive", "hover"}, this->colors.schedule_buttons.deleteMode.deactive.hover);
    JTC, {"Colors", "Buttons", "DeleteMode", "Deactive", "press"}, this->colors.schedule_buttons.deleteMode.deactive.press);

    JTC, {"Colors", "Buttons", "StandardMode", "Active", "idle"}, this->colors.schedule_buttons.standardMode.active.idle);
    JTC, {"Colors", "Buttons", "StandardMode", "Active", "hover"}, this->colors.schedule_buttons.standardMode.active.hover);
    JTC, {"Colors", "Buttons", "StandardMode", "Active", "press"}, this->colors.schedule_buttons.standardMode.active.press);

    JTC, {"Colors", "Buttons", "StandardMode", "Deactive", "idle"}, this->colors.schedule_buttons.standardMode.deactive.idle);
    JTC, {"Colors", "Buttons", "StandardMode", "Deactive", "hover"}, this->colors.schedule_buttons.standardMode.deactive.hover);
    JTC, {"Colors", "Buttons", "StandardMode", "Deactive", "press"}, this->colors.schedule_buttons.standardMode.deactive.press);

    printf("Info: ConfData: configuration moved to memory\n");
    this->verifyChangeConf();
}

std::string ConfData::buildConfFileTemplate() const
{
    Json conf_json_template = Json::parse(
        R"(
        {
            "Window Title": "Schedule Visualizer",
            "Icon Path": "app_icon.png",
            "Window Size": {
                "x": 750,
                "y": 854
            },
            "Window Position": {
                "x": 575,
                "y": 40
            },
            "Window Margin": {
                "x": 20.0,
                "y": 80.0
            },
            "Schedule Position": {
                "x": 10.0,
                "y": 80.0
            },
            "Default Image File": "default.png",
            "Background Image File": "schedule_background.png",
            "Schedules Path": "schedules",
            "Coords Path": "coords",
            "Font File": "fonts/OpenSans-Regular.ttf",
            "State File": "state.json",
            "Schedule Image Extension": ".png",
            "Button Data Extension": ".buttondata.json",
            "Frame Rate" : {
                "idle" : 10,
                "active" : 30
            },
            "Log Save Schedule List": false,
            "Logs In CMD": true,
            "Display CMD": false,
            "Reverse Scroll Direction": false,
            "Exec Path" : "exec",
            "Exec Path Input": "in",
            "Exec Path Output": "out",
            "Exec Files": {
                "change image exposure": "change_image_exposure.py",
                "find coords inside week schedule": "find_coords_inside_week_schedule.py",
                "translate coords to json": "translate_coords_to_json"
            },
            "Exec Files Extension": {
                "linux": ".out",
                "windows": ".exe"
            },
            "Schedule Fade Mask": 40,
            "Colors" : {
                "Background" : {
                    "r": 30, 
                    "g": 30, 
                    "b": 30, 
                    "a": 255
                },
                "Delete Schedule Button":{
                    "idle" : {
                        "r": 200,
                        "g": 60,
                        "b": 60,
                        "a": 180
                    },
                    "hover" : {
                        "r": 160,
                        "g": 60,
                        "b": 60,
                        "a": 180
                    },
                    "press" : {
                        "r": 240,
                        "g": 60,
                        "b": 60,
                        "a": 180
                    }
                },
                "Add New Schedule Button":{
                    "idle" : {
                        "r": 60, 
                        "g": 200,
                        "b": 60,
                        "a": 180
                    },
                    "hover" : {
                        "r": 60, 
                        "g": 160,
                        "b": 60,
                        "a": 180
                    },
                    "press" : {
                        "r": 60, 
                        "g": 240,
                        "b": 60,
                        "a": 180
                    }
                },
                "Buttons" : {
                    "DeleteMode" : {
                        "Active" : {
                            "idle" : {
                                "r": 220, 
                                "g": 20, 
                                "b": 20, 
                                "a": 60
                            },
                            "hover" : {
                                "r": 250, 
                                "g": 20, 
                                "b": 20, 
                                "a": 60
                            },
                            "press" : {
                                "r": 200, 
                                "g": 20, 
                                "b": 20, 
                                "a": 60
                            }
                        },
                        "Deactive" : {
                            "idle" : {
                                "r": 220, 
                                "g": 20, 
                                "b": 20, 
                                "a": 10
                            },
                            "hover" : {
                                "r": 250, 
                                "g": 20, 
                                "b": 20, 
                                "a": 10
                            },
                            "press" : {
                                "r": 200, 
                                "g": 20, 
                                "b": 20, 
                                "a": 10
                            }
                        }
                    },
                    "StandardMode" : {
                        "Active" : {
                            "idle" : {
                                "r": 0, 
                                "g": 0, 
                                "b": 0, 
                                "a": 0
                            },
                            "hover" : {
                                "r": 60, 
                                "g": 60, 
                                "b": 60, 
                                "a": 30
                            },
                            "press" : {
                                "r": 30, 
                                "g": 30, 
                                "b": 30, 
                                "a": 60}
                        },
                        "Deactive" : {
                            "idle" : {
                                "r": 50, 
                                "g": 50, 
                                "b": 50, 
                                "a": 120
                            },
                            "hover" : {
                                "r": 60, 
                                "g": 60, 
                                "b": 60, 
                                "a": 100
                            },
                            "press" : {
                                "r": 30, 
                                "g": 30, 
                                "b": 30, 
                                "a": 160
                            }
                        }
                    }
                },
                "Text": {
                    "r": 255, 
                    "g": 255, 
                    "b": 255, 
                    "a": 150
                }
                
            }
        }
        )");
    return conf_json_template.dump(4);
}