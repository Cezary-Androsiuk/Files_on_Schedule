#include "UpdateSchedule.hpp"


size_t UpdateSchedule::getRecentlyOpenedScheduleId(const ConfData *const confdata){
    printf("Info: UpdateSchedule: reading id of recently opened schedule ...\n");
    Json state_json;
    std::ifstream ifile(confdata->state_file);
    size_t schedule_id;
    if (!ifile.good())
    {
        printf("Error: UpdateSchedule: can not read state file '%s'\n", confdata->state_file.c_str());
        return SIZE_MAX;
    }
    ifile >> state_json;
    ifile.close();
    JsonRead::toVar(state_json, {"Current Page"}, schedule_id);
    printf("Info: UpdateSchedule: recently opened schedule id is %ld ...\n", schedule_id);
    return schedule_id;
}

std::string UpdateSchedule::getScheduleNameById(const ConfData *const confdata, size_t id){
    if (confdata->save_schedule_list_logs)
        printf("Info: UpdateSchedule: loading available schedules :\n\t[");
    int scheduleIndex = 0;
    std::vector<std::string> schedule_list;
    for (const auto &file : std::filesystem::directory_iterator(confdata->schedules_path))
    {
        std::string scheduleFileName = file.path().filename().stem().string();
        schedule_list.push_back(scheduleFileName);
        if (confdata->save_schedule_list_logs)
            printf("%4d: %s, ", scheduleIndex++, scheduleFileName.c_str());
    }
    if (confdata->save_schedule_list_logs)
        printf("]\n");


    if (id > schedule_list.size() - 1)
        id = schedule_list.size() - 1;

    std::sort(schedule_list.begin(), schedule_list.end());
    return schedule_list[id];
}

int UpdateSchedule::checkifAllFilesExist(const ConfData *const confdata, std::string name){

    std::string schedule_file = (std::filesystem::path(confdata->schedules_path) / 
        (name + confdata->schedule_image_extension)).string();
    if(!std::filesystem::exists(schedule_file)){
        printf("Error: UpdateSchedule: missing schedule file '%s'\n", schedule_file.c_str());
        return 1;
    }
    std::string coords_file = (std::filesystem::path(confdata->coords_path) / 
        (name + confdata->button_data_extension)).string();
    if(!std::filesystem::exists(coords_file)){
        printf("Error: UpdateSchedule: missing coords file '%s'\n", coords_file.c_str());
        return 1;
    }
    return 0;
}

void UpdateSchedule::deleteRecentlyOpenedSchedule(const ConfData *const confdata)
{
    printf("Info: UpdateSchedule: deleting recenlty opened schedule ...\n");

    size_t schedule_id = UpdateSchedule::getRecentlyOpenedScheduleId(confdata);
    if(schedule_id == SIZE_MAX){
        printf("Error: UpdateSchedule: deleting recently opened schedule interrupted\n");
        return;
    }
    
    std::string deleteScheduleName = UpdateSchedule::getScheduleNameById(confdata, schedule_id);
    if(deleteScheduleName.empty()){
        printf("Error: UpdateSchedule: name of file is empty, deleting recently opened schedule interrupted\n");
        return;
    }

    if(UpdateSchedule::checkifAllFilesExist(confdata, deleteScheduleName)){
        printf("Error: UpdateSchedule: deleting recently opened schedule interrupted\n");
        return;
    }

    std::filesystem::remove(
        std::filesystem::path(confdata->schedules_path) / 
        (deleteScheduleName + confdata->schedule_image_extension)
    );
    std::filesystem::remove(
        std::filesystem::path(confdata->coords_path) / 
        (deleteScheduleName + confdata->button_data_extension)
    );

    printf("Info: UpdateSchedule: deleted recenlty opened schedule\n");
}







int UpdateSchedule::askforFileName(std::string &filename){
#ifdef linux
    // Usage:
    //     zenity [OPTION…]

    // File selection options
    //     --file-selection                                  Display file selection dialog
    //     --filename=FILENAME                               Set the filename
    //     --multiple                                        Allow multiple files to be selected
    //     --directory                                       Activate directory-only selection
    //     --save                                            Activate save mode
    //     --separator=SEPARATOR                             Set output separator character
    //     --confirm-overwrite                               Confirm file selection if filename already exists
    //     --file-filter=NAME | PATTERN1 PATTERN2 ...        Set a filename filter

    printf("Info: UpdateSchedule: select file begin\n");
    char cbuffer[1024] = {0};
    FILE *f = popen("zenity --file-selection", "r");
    fgets(cbuffer, 1024, f);
    filename = cbuffer;
    if (filename.empty())
    {
        printf("Info: UpdateSchedule: operation terminated, no file selected\n");
        return 1;
    }
    filename.pop_back(); // remove \n sign at the end
    printf("Info: UpdateSchedule: adding schedule file named '%s'\n", filename.c_str());
#elif _WIN32
    char buffer[MAX_PATH] = {0};

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a File";

    if (GetOpenFileNameA(&ofn)) {
        std::string filePath(buffer);
        if (filePath.empty()) {
            printf("Warning: UpdateSchedule: operation terminated, empty path\n");
            return 1;
        }
        filename = filePath;
    } else {
        printf("Info: UpdateSchedule: operation terminated, no file selected\n");
        return 1;
    }
#endif
    return 0;
}

int UpdateSchedule::runExec(const std::string &file, std::vector<std::string> args){
#ifdef linux
    std::string command = "./" + file;
#elif _WIN32
    std::string command = ".\\" + file;
#endif
    for(const auto &arg : args)
        command += " " + arg;

    int exitCode = std::system(command.c_str());
    return exitCode;
}

int UpdateSchedule::runPython(const std::string &file){
#ifdef linux
    std::string command = "python3 " + file;
#elif _WIN32
    std::string command = "python " + file;
#endif

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        printf("Error: UpdateSchedule: error while starting command '%s'\n", command.c_str());
        return 1;
    }

    int exitCode = pclose(pipe);
    return exitCode;
}





void UpdateSchedule::addNewSchedule(const ConfData *const confdata)
{
    printf("Info: UpdateSchedule: adding new schedule ...\n");
    
    const auto start_path = std::filesystem::current_path();
    const auto copyOptionsReplace = std::filesystem::copy_options::overwrite_existing;

    std::string filename;
    if(UpdateSchedule::askforFileName(filename)){
        printf("Info: UpdateSchedule: adding new schedule interrupted\n");
        return;
    
    }

    std::filesystem::current_path(start_path); // windows changes path ... windwos is a lot of pain
    
    if(sfp(filename).extension() != ".png"){
        printf("Error: UpdateSchedule: incompatible extensions '%s' expecting schedule.png\n", filename.c_str());
        return;
    }
    if(!std::filesystem::exists(sfp(confdata->exec_path_in))){
        std::filesystem::create_directories(sfp(confdata->exec_path_in));
    }
    if(std::filesystem::exists(sfp(confdata->exec_path_in) / sfp(filename).filename().string())){
        std::filesystem::remove(sfp(confdata->exec_path_in) / sfp(filename).filename().string());
    }
    if(!std::filesystem::copy_file(filename, sfp(confdata->exec_path_in) / sfp(filename).filename().string(), copyOptionsReplace))
    {
        printf("Error: UpdateSchedule: error while copying file from '%s' to '%s'\n", 
            filename.c_str(), (sfp(confdata->exec_path_in) / sfp(filename).filename().string()).string().c_str());
        return;
    }

    if(!std::filesystem::exists(confdata->exec_path_in))
        std::filesystem::create_directory(confdata->exec_path_in);

    if(!std::filesystem::exists(confdata->exec_path_out))
        std::filesystem::create_directory(confdata->exec_path_out);
    
    
    std::filesystem::current_path(start_path / confdata->exec_path);

    // exec files
    if(UpdateSchedule::runPython(confdata->change_image_exposure_file)){
        printf("Error: UpdateSchedule: adding new schedule interrupted while executing python script '%s'\n",
            confdata->change_image_exposure_file.c_str());
        std::filesystem::current_path(start_path);
        return;
    }
    printf("Info: UpdateSchedule: python scipt '%s' executed correctly\n", confdata->change_image_exposure_file.c_str());

    if(UpdateSchedule::runPython(confdata->find_coords_inside_week_schedule_file)){
        printf("Error: UpdateSchedule: adding new schedule interrupted while executing python script '%s'\n",
            confdata->find_coords_inside_week_schedule_file.c_str());
        std::filesystem::current_path(start_path);
        return;
    }
    printf("Info: UpdateSchedule: python scipt '%s' executed correctly\n", confdata->find_coords_inside_week_schedule_file.c_str());

    if(UpdateSchedule::runExec(
        confdata->translate_coords_to_json_file + confdata->exec_file_extension, 
        {"schedules/", sfp(confdata->exec_path_out).filename().string()})
    )
    {
        printf("Error: UpdateSchedule: adding new schedule interrupted while executing exec file '%s'\n",
            (confdata->translate_coords_to_json_file + confdata->exec_file_extension).c_str());
        std::filesystem::current_path(start_path);
        return;
    }
    printf("Info: UpdateSchedule: exec file '%s' executed correctly\n", 
        (confdata->translate_coords_to_json_file + confdata->exec_file_extension).c_str());

    for(const auto &f : std::filesystem::directory_iterator("schedules"))
        std::filesystem::remove(f);

    std::filesystem::current_path(start_path);

    // copy to end paths
    for(const auto &f : std::filesystem::directory_iterator(confdata->exec_path_in)){
        sfp schedule_copy_from = f;
        sfp schedule_copy_to = sfp(confdata->schedules_path) / f.path().filename().string();
        if(!std::filesystem::copy_file(schedule_copy_from, schedule_copy_to, copyOptionsReplace))
        {
            printf("Error: UpdateSchedule: error while copying file from '%s' to '%s'\n", 
                schedule_copy_from.string().c_str(), schedule_copy_to.string().c_str());
            return;
        }
        std::filesystem::remove(schedule_copy_from);
    }

    for(const auto &f : std::filesystem::directory_iterator(confdata->exec_path_out)){
        sfp coords_copy_from = f;
        sfp coords_copy_to = sfp(confdata->coords_path) / f.path().filename().string();
        if(!std::filesystem::copy_file(coords_copy_from, coords_copy_to, copyOptionsReplace))
        {
            printf("Error: UpdateSchedule: error while copying file from '%s' to '%s'\n", 
                coords_copy_from.string().c_str(), coords_copy_to.string().c_str());
            return;
        }
        std::filesystem::remove(coords_copy_from);
    }

    printf("Info: UpdateSchedule: added new schedule\n");
}








// void Schedule::addHrefAction(ButtonData *bd)
// {
// #ifdef linux
//     printf("Info: Schedule: select file start\n");
//     // this->window->setVisible(false);
//     char cbuffer[1024] = {0};
//     FILE *f = popen("zenity --file-selection", "r");
//     fgets(cbuffer, 1024, f);
//     std::string sbuffer = cbuffer;
//     if (sbuffer.empty())
//     {
//         printf("Info: Schedule: operation terminated, no file selected\n");
//     }
//     else
//     {
//         sbuffer.pop_back(); // remove \n sign at the end
//         bd->href = sbuffer;
//         this->setButtonColor(bd);
//         printf("Info: Schedule: href '%s' added to %s\n",
//                bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
//     }
//     // this->window->setVisible(true);
// #elif _WIN32
//     printf("ERROR: Schedule: add file windows not configured!\n");
// #endif
// }

// void Schedule::deleteHrefsAction(ButtonData *bd)
// {
//     bd->href.clear();
//     this->setButtonColor(bd);
//     printf("Info: Schedule: href '%s' from  %s was deleted\n",
//            bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
// }

// void Schedule::useHrefsAction(ButtonData *bd)
// {
//     printf("Info: Schedule: href '%s' used\n", bd->href.c_str());
// #ifdef linux
//     system(("open \"" + bd->href + "\";").c_str());
// #elif _WIN32
//     system(("start \'" + bd->href + "\';").c_str());
// #endif
//     this->setButtonColor(bd);
// }