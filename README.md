# Files on Schedule

## About

Cross-platform app supporting Windows and Linux. Facilitates file and folder management, by enabling users to associate files/folders with specific lessons on a weekly schedule for efficient organization and access.

The 'res/exec' directory contains all the scripts required to add a new schedule to the application. These scripts are configured to import schedules exclusively from USOSweb (Uniwersytecki System Obsługi Studiów). It's important to note that the schedules must be named in the format 'YYYY-MM-DD-YYYY-MM-DD.png,' mirroring the format used in the USOSweb schedule descriptions.
By modifying the content of the 'res/exec' path, you can tailor the application to your class schedule, allowing the app to automatically detect individual lessons in new added schedules. Additionally, customization of the app is possible through the 'res/conf.json' file.
All schedules are sorted based on their names and displayed from the oldest to the newest. This arrangement allows for the seamless addition of both new and older plans.
The 'res/coords' directory contains all the information regarding which lesson has associated coordinates for buttons and which file/folder is associated with it. This information is organized based on weekly schedules.


## Required
- **C++17**
- **SFML-2.6.1**
- **CMake 3.10**
- **Python 3.11.5**


## Compile
### Linux
```bash
mkdir bin && cd bin;
cmake .. && make && ./main;
```

### Windows 
```bash
mkdir bin && cd bin;
cmake -G "MinGW Makefiles" .. && cmake --build . && .\main
```


## Screenshots

![1](https://github.com/Cezary-Androsiuk/Files_on_Schedule/blob/master/pictures/0.png?raw=true)
![1](https://github.com/Cezary-Androsiuk/Files_on_Schedule/blob/master/pictures/1.png?raw=true)
![1](https://github.com/Cezary-Androsiuk/Files_on_Schedule/blob/master/pictures/2.png?raw=true)

## Example Terminal Logs

```log
Info: Window: constructing objects
Info: ConfData: constructing objects
Info: ConfData: configuration loaded from 'resconf.json'
Info: ConfData: configuration moved to memory
Info: ConfData: configuration verifying ...
Info: ConfData: configuration verified
Info: ConfData: objects correctly constructed
Info: Objects: constructing objects
Info: Schedule: constructing objects
Info: Schedule: schedule state loaded
Info: Schedule: changing schedule from 110 to page 4 with name '2021-10-25-2021-10-31' ...
Info: Schedule: saving buttons data: last page: -1, current page: 110, next page: 4, existing buttons: 0
Info: Schedule: saved was skipped
Info: Schedule: reading button data from '2021-10-25-2021-10-31.buttondata.json' ...
Info: Schedule: button data was storred in json variable
Info: Schedule: Button_0 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_0 data was setted
Info: Schedule: Button_1 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_1 data was setted
Info: Schedule: Button_10 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_10 data was setted
Info: Schedule: Button_2 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_2 data was setted
Info: Schedule: Button_3 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_3 data was setted
Info: Schedule: Button_4 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_4 data was setted
Info: Schedule: Button_5 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_5 data was setted
Info: Schedule: Button_6 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_6 data was setted
Info: Schedule: Button_7 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_7 data was setted
Info: Schedule: Button_8 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_8 data was setted
Info: Schedule: Button_9 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_9 data was setted
Info: Schedule: all buttons was loaded
Info: Schedule: changed schedule to page 4 with name '2021-10-25-2021-10-31'
Info: Schedule: objects correctly constructed
Info: Objects: data initialized
Info: Objects: objects correctly constructed
Info: Window: data initialized
Info: Window: window initialized
Info: Window: objects correctly constructed
Info: Schedule: Button_0 pressed
Info: UpdateSchedule: operation terminated, no file selected
Info: Schedule: Button_0 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_5 pressed
Info: HrefActions: href 'G:\Studia\StudiaSem1\StudiaSem1\C Jezyk angielski 1\info.txt' added to Button_5
Info: Schedule: Button_5 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_10 pressed
Info: HrefActions: href 'G:\Studia\StudiaSem1\StudiaSem1\C # W Podstawy logiki i teorii mnogosci\Cwiczenia\Logika 2.pdf' added to Button_10
Info: Schedule: Button_10 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_8 pressed
Info: HrefActions: href 'G:\Studia\StudiaSem1\StudiaSem1\C # W Podstawy programowania strukturalnego\Cwiczenia\lista2pps.pdf' added to Button_8
Info: Schedule: Button_8 color setted to:   active: true   state: UseHrefState
Info: Schedule:   event: KeyPressed, key: Keyboard: Delete
Info: Schedule: changing schedule from 4 to page 4 with name '2021-10-25-2021-10-31' ...
Info: Schedule: saving buttons data: last page: 110, current page: 4, next page: 4, existing buttons: 11
Info: Schedule: Button_0 data was storred in json variable
Info: Schedule: Button_1 data was storred in json variable
Info: Schedule: Button_10 data was storred in json variable
Info: Schedule: Button_2 data was storred in json variable
Info: Schedule: Button_3 data was storred in json variable
Info: Schedule: Button_4 data was storred in json variable
Info: Schedule: Button_5 data was storred in json variable
Info: Schedule: Button_6 data was storred in json variable
Info: Schedule: Button_7 data was storred in json variable
Info: Schedule: Button_8 data was storred in json variable
Info: Schedule: Button_9 data was storred in json variable
Info: Schedule: all buttons was saved in 'res\coords\2021-10-25-2021-10-31.buttondata.json'
Info: Schedule: reading button data from '2021-10-25-2021-10-31.buttondata.json' ...
Info: Schedule: button data was storred in json variable
Info: Schedule: Button_0 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_0 data was setted
Info: Schedule: Button_1 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_1 data was setted
Info: Schedule: Button_10 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_10 data was setted
Info: Schedule: Button_2 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_2 data was setted
Info: Schedule: Button_3 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_3 data was setted
Info: Schedule: Button_4 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_4 data was setted
Info: Schedule: Button_5 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_5 data was setted
Info: Schedule: Button_6 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_6 data was setted
Info: Schedule: Button_7 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_7 data was setted
Info: Schedule: Button_8 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_8 data was setted
Info: Schedule: Button_9 color setted to:   active: true   state: DeleteHrefState
Info: Schedule: Button_9 data was setted
Info: Schedule: all buttons was loaded
Info: Schedule: changed schedule to page 4 with name '2021-10-25-2021-10-31'
Info: Schedule:   event: KeyPressed, key: Keyboard: Delete
Info: Schedule: changing schedule from 4 to page 4 with name '2021-10-25-2021-10-31' ...
Info: Schedule: saving buttons data: last page: 4, current page: 4, next page: 4, existing buttons: 11
Info: Schedule: Button_0 data was storred in json variable
Info: Schedule: Button_1 data was storred in json variable
Info: Schedule: Button_10 data was storred in json variable
Info: Schedule: Button_2 data was storred in json variable
Info: Schedule: Button_3 data was storred in json variable
Info: Schedule: Button_4 data was storred in json variable
Info: Schedule: Button_5 data was storred in json variable
Info: Schedule: Button_6 data was storred in json variable
Info: Schedule: Button_7 data was storred in json variable
Info: Schedule: Button_8 data was storred in json variable
Info: Schedule: Button_9 data was storred in json variable
Info: Schedule: all buttons was saved in 'res\coords\2021-10-25-2021-10-31.buttondata.json'
Info: Schedule: reading button data from '2021-10-25-2021-10-31.buttondata.json' ...
Info: Schedule: button data was storred in json variable
Info: Schedule: Button_0 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_0 data was setted
Info: Schedule: Button_1 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_1 data was setted
Info: Schedule: Button_10 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_10 data was setted
Info: Schedule: Button_2 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_2 data was setted
Info: Schedule: Button_3 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_3 data was setted
Info: Schedule: Button_4 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_4 data was setted
Info: Schedule: Button_5 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_5 data was setted
Info: Schedule: Button_6 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_6 data was setted
Info: Schedule: Button_7 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_7 data was setted
Info: Schedule: Button_8 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_8 data was setted
Info: Schedule: Button_9 color setted to:   active: true   state: UseHrefState
Info: Schedule: Button_9 data was setted
Info: Schedule: all buttons was loaded
Info: Schedule: changed schedule to page 4 with name '2021-10-25-2021-10-31'
Info: Window:   event: Closed
Info: Window: deconstructing objects...
Info: Objects: deconstructing objects...
Info: Schedule: deconstructing objects...
Info: Schedule: application state was saved to 'res\state.json'
Info: Schedule: saving buttons data: last page: 4, current page: 4, next page: 4, existing buttons: 11
Info: Schedule: Button_0 data was storred in json variable
Info: Schedule: Button_1 data was storred in json variable
Info: Schedule: Button_10 data was storred in json variable
Info: Schedule: Button_2 data was storred in json variable
Info: Schedule: Button_3 data was storred in json variable
Info: Schedule: Button_4 data was storred in json variable
Info: Schedule: Button_5 data was storred in json variable
Info: Schedule: Button_6 data was storred in json variable
Info: Schedule: Button_7 data was storred in json variable
Info: Schedule: Button_8 data was storred in json variable
Info: Schedule: Button_9 data was storred in json variable
Info: Schedule: all buttons was saved in 'res\coords\2021-10-25-2021-10-31.buttondata.json'
Info: Schedule: objects correctly deconstructed
Info: Objects: objects correctly deconstructed
Info: ConfData: deconstructing objects...
Info: ConfData: objects correctly deconstructed
Info: Window: objects deleted
Info: Window: objects correctly deconstructed
Info: LogData: disabling log file...
log file was not enabled
Application Correctly Closed!
```