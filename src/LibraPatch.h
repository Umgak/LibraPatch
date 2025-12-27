#pragma once
#include <stdint.h>
#include "LilyLib/LilyLib.hpp"
#if defined _M_X64
#pragma comment(lib, "libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "libMinHook.x86.lib")
#endif

#define MAX_CLONES 10
namespace LibraPatch {
	struct LibraChrDataEntry {
		uint32_t entityId = 0;
		uint32_t entityId2 = 0;
		uint32_t entityId3 = 0;
		int32_t npcParamId = -1;
		int32_t npcThinkParamId = -1;
		int32_t charaInitParamId = -1;
	};

	void DetourOverrideCharacterCreateData(uint8_t slot, uint32_t entityId, uint32_t entityId2, uint32_t entityId3,
			int32_t npcParamId, int32_t npcThinkParamId, int32_t charaInitParamId);
	void DetourResetCharacterCreateData();
	bool DetourGetCharacterCreateData(uint32_t targetEntityId, LibraChrDataEntry* entityData);

	typedef void (*OverrideCharacterCreateData)(uint8_t, uint32_t, uint32_t, uint32_t, int32_t, int32_t, int32_t);
	typedef void (*ResetCharacterCreateData)();
	typedef bool (*GetCharacterCreateData)(uint32_t, LibraChrDataEntry*);

	bool installHooks();
	bool removeHooks();
}