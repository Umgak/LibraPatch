/*
    * LilyLib::Util
    * Contains some logging/helper functions.

    * Copyright (c) 2025 Lily, aka "Umgak"
     
    * This program is free software; licensed under the MIT license.
    * You should have received a copy of the license along with this program.
    * If not, see <https://opensource.org/licenses/MIT>.
*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>
#include <fstream>

namespace LilyLib {
    namespace Util {
        static HWND uWindow = nullptr;
        static LPCWSTR uExpectedWindowTitle = L"ELDEN RING NIGHTREIGN";
        static std::ofstream uLogFile;

        static void dummy() {
            // blank, workaround
        }
        static std::filesystem::path _GetModulePath(bool mainProcessModule)
        {
            HMODULE module = nullptr;
            wchar_t lpFilepath[MAX_PATH] = {};
            std::wstring modulePathWide;
            std::filesystem::path modulePath;

            if (!mainProcessModule)
            {
                GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&dummy, &module);
            }
            GetModuleFileNameW(module, lpFilepath, sizeof(lpFilepath));
            modulePathWide = lpFilepath;
            modulePath = modulePathWide;
            return modulePath;
        }

        static std::string _GetModuleName(bool mainProcessModule)
        {
            std::filesystem::path modulePath = _GetModulePath(mainProcessModule);
            std::size_t pos = modulePath.string().find_last_of('\\');
            return modulePath.string().substr(pos + 1);
        }

        static std::string GetCurrentProcessName()
        {
            return _GetModuleName(true);
        }

        static std::filesystem::path GetCurrentModPath()
        {
            return _GetModulePath(false);
        }

        static std::string GetCurrentModName()
        {
            std::string moduleName = _GetModuleName(false);
            std::size_t pos = moduleName.find_last_of(".");
            std::string modName = moduleName.substr(0, pos);
            return modName;
        }

        static void OpenModLogFile()
        {
            if (!uLogFile.is_open())
            {
                uLogFile.open(GetCurrentModPath().replace_extension(".log"));
            }
        }

        static void CloseLog()
        {
            if (uLogFile.is_open())
            {
                uLogFile.close();
            }
        }

        inline void Log(std::string_view message)
        {
            OpenModLogFile();
            const auto now = std::chrono::system_clock::now();
            std::string logLine = std::format("{:%T}: {}: {}\n", now, GetCurrentModName(), message);

            if (uLogFile.is_open())
            {
                uLogFile << logLine;
                uLogFile.flush();
            }
        }

        template<typename... Args>
        inline void Log(std::format_string<Args...> format_str, Args&&... args)
        {
            Log(std::format(format_str, std::forward<Args>(args)...));
        }

        inline void ShowErrorMessage(std::string err)
        {
            Log("ERROR: {}", err);
            MessageBoxA(NULL, err.c_str(), GetCurrentModName().c_str(), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
        }

        template<typename... Args>
        inline void ShowErrorMessage(std::format_string<Args...> format_str, Args&&... args)
        {
            ShowErrorMessage(std::format(format_str, std::forward<Args>(args)...));
        }

        inline void WaitForProcess()
        {
            WaitForInputIdle(GetCurrentProcess(), INFINITE);
        }
    }
}