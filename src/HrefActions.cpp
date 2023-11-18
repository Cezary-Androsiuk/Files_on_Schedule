#include "HrefActions.hpp"

void HrefActions::addFileHrefActionLinux(ButtonData *bd)
{
    printf("Info: HrefActions: select file start\n");
    char cbuffer[1024] = {0};
    FILE *f = popen("zenity --file-selection", "r");
    fgets(cbuffer, 1024, f);
    std::string sbuffer = cbuffer;
    if (sbuffer.empty())
    {
        printf("Info: HrefActions: operation terminated, no file selected\n");
    }
    else
    {
        sbuffer.pop_back(); // remove \n sign at the end
        bd->href = sbuffer;
        printf("Info: HrefActions: href '%s' added to %s\n",
               bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
    }
}
void HrefActions::addFileHrefActionWindows(ButtonData *bd)
{
    char buffer[MAX_PATH] = {0};

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.lpstrFile = buffer;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a File";

    if (GetOpenFileNameA(&ofn))
    {
        std::string filePath(buffer, MAX_PATH);
        if (filePath.empty())
        {
            printf("Warning: Schedule: operation terminated, empty path\n");
            return;
        }
        bd->href = filePath;
        printf("Info: HrefActions: href '%s' added to %s\n",
               bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
    }
    else
    {
        printf("Info: UpdateSchedule: operation terminated, no file selected\n");
    }
}
void HrefActions::addDirHrefActionLinux(ButtonData *bd)
{
    printf("Info: HrefActions: select file start\n");
    char cbuffer[1024] = {0};
    FILE *f = popen("zenity --file-selection", "r");
    fgets(cbuffer, 1024, f);
    std::string sbuffer = cbuffer;
    if (sbuffer.empty())
    {
        printf("Info: HrefActions: operation terminated, no file selected\n");
    }
    else
    {
        sbuffer.pop_back(); // remove \n sign at the end
        bd->href = sbuffer;
        printf("Info: HrefActions: href '%s' added to %s\n",
               bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
    }
}
void HrefActions::addDirHrefActionWindows(ButtonData *bd)
{
    // * GPT CODE IDK HOW IT WORDK
    IFileDialog *pFileDialog;

    // Inicjalizacja COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    // Utwórz obiekt IFileDialog.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileDialog, reinterpret_cast<void **>(&pFileDialog));

    if (SUCCEEDED(hr))
    {
        // Ustaw opcję, aby umożliwić wybieranie zarówno plików, jak i folderów.
        DWORD dwOptions;
        pFileDialog->GetOptions(&dwOptions);
        pFileDialog->SetOptions(dwOptions | FOS_PICKFOLDERS);

        // Wywołaj okno dialogowe
        hr = pFileDialog->Show(NULL);

        if (SUCCEEDED(hr))
        {
            IShellItem *pItem;
            hr = pFileDialog->GetResult(&pItem);

            if (SUCCEEDED(hr))
            {
                PWSTR pszFilePath;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                if (SUCCEEDED(hr))
                {
                    std::wstring filePath(pszFilePath);
                    CoTaskMemFree(pszFilePath);

                    // Tutaj możesz użyć filePath jako ścieżki do pliku lub folderu

                    bd->href = sf::String(filePath).toAnsiString();
                    printf("Info: HrefActions: href '%s' added to %s\n",
                           bd->href.c_str(), bd->button->getName().toAnsiString().c_str());
                }

                pItem->Release();
            }
        }

        pFileDialog->Release();
    }

    // Zakończ COM
    CoUninitialize();
}

void HrefActions::useHrefsAction(void *bd)
{
    HrefActions::ButtonData *n_bd = static_cast<HrefActions::ButtonData *>(bd);
    printf("Info: HrefActions: href '%s' used\n", n_bd->href.c_str());
#ifdef linux
    system(("open \"" + bd->href + "\";").c_str());
#elif _WIN32
    LPCSTR filePath = n_bd->href.c_str();
    LPCSTR action = "open";
    //! it is ok but intellisense freak out
    HINSTANCE result = ShellExecute(nullptr, action, filePath, nullptr, nullptr, SW_SHOWNORMAL);

#endif
}

void HrefActions::addFileHrefAction(void *bd)
{
    // this->window->setVisible(false);
    const auto start_path = std::filesystem::current_path();
#ifdef linux
    HrefActions::addFileHrefActionLinux(bd);
#elif _WIN32
    HrefActions::addFileHrefActionWindows(static_cast<HrefActions::ButtonData *>(bd));
#endif
    std::filesystem::current_path(start_path);
    // this->window->setVisible(true);
}

void HrefActions::addDirHrefAction(void *bd)
{
    // this->window->setVisible(false);
    const auto start_path = std::filesystem::current_path();
#ifdef linux
    HrefActions::addDirHrefActionLinux(bd);
#elif _WIN32
    HrefActions::addDirHrefActionWindows(static_cast<HrefActions::ButtonData *>(bd));
#endif
    std::filesystem::current_path(start_path);
    // this->window->setVisible(true);
}

void HrefActions::deleteHrefsAction(void *bd)
{
    HrefActions::ButtonData *n_bd = static_cast<HrefActions::ButtonData *>(bd);
    n_bd->href.clear();
    printf("Info: HrefActions: href '%s' from  %s was deleted\n",
           n_bd->href.c_str(), n_bd->button->getName().toAnsiString().c_str());
}
