/*
    * LilyLib::Memory
    * Functions for scanning memory
    * Requires Pattern16

    * Copyright (c) 2025 Lily, aka "Umgak"

    * This program is free software; licensed under the MIT license.
    * You should have received a copy of the license along with this program.
    * If not, see <https://opensource.org/licenses/MIT>.
*/

#pragma once
#include <Psapi.h>
#include "Pattern16/include/Pattern16.h"

namespace LilyLib {
    namespace Memory {
        struct MemoryRegion {
            void *start = 0;
            size_t size = 0;

            MemoryRegion(const char* module, const char* pe_section)
            {
                HMODULE hModule = GetModuleHandleA(module);
                MODULEINFO modInfo{};
                if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo)))
                {
                    Util::ShowErrorMessage("Failed to create MemoryRegion: GetModuleInformation returned {}.", GetLastError());
                    return;
                }
                uintptr_t base = (uintptr_t)modInfo.lpBaseOfDll;

                IMAGE_DOS_HEADER *dosHeader = (IMAGE_DOS_HEADER*)base;
                IMAGE_NT_HEADERS *ntHeader = (IMAGE_NT_HEADERS*)((uintptr_t)base + dosHeader->e_lfanew);
                IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(ntHeader);

                for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++) {
                    if (memcmp(pe_section, (char*)section[i].Name, IMAGE_SIZEOF_SHORT_NAME) == 0) {
                        start = (void*)(base + section[i].VirtualAddress);
                        size = (size_t)section[i].Misc.VirtualSize;
                        return;
                    }
                }
            }
        };

        // Use Pattern16 to scan memory (by default .text section) for an AOB
        inline void* AOBScanModule(std::string aob, const char* module = nullptr, const char* section = ".text")
        {
            MemoryRegion mem(module, section);
            void* address = Pattern16::scan(mem.start, mem.size, aob);
            if (!address)
            {
                Util::ShowErrorMessage("AOBScanModule failed!\nAOB was: \"{}\".\nFailed to locate AOB in process.", aob);
            }
            return address;
        }
        
        // Extract a base pointer from a RIP-relative instruction
        // by default, 64 bit mov is the target, but this can be overriden with instructionOffset and opcodeOffset
        inline void* AOBScanBase(std::string aob, const int opcodeOffset = 3, const int instructionOffset = 7, const char* module = nullptr, const char* section = ".text")
        {
            char* address = (char*)AOBScanModule(aob, module, section);
            return reinterpret_cast<void*>(address + *reinterpret_cast<int32_t*>(address + opcodeOffset) + instructionOffset);
        }
    }
}