#include "pch.h"
#include "LibraPatch.h"

namespace LibraPatch {
	LibraChrDataEntry* LibraCharacterCreateData = new LibraChrDataEntry[MAX_CLONES];

    /* 
        OverrideCharacterCreateData
        AOB: 80 f9 03 73 79 (it's so tiny)
		original code: 
                              **************************************************************
                              *                          FUNCTION                          *
                              **************************************************************
                              void __fastcall OverrideCharacterCreateData(byte slot, u
                                assume GS_OFFSET = 0xff00000000
              void              <VOID>         <RETURN>
              byte              CL:1           slot
              uint              EDX:4          entityId
              uint              R8D:4          entityId2
              uint              R9D:4          entityId3
              int               Stack[0x28]:4  npcParamId
              int               Stack[0x30]:4  npcThinkParamId
              int               Stack[0x38]:4  characterParamId
              undefined8        HASH:41f1a0f   slotOffset
                              OverrideCharacterCreateData                     XREF[1]:     FUN_14058b540:14058eb6d(c)
        1402000c0 80 f9 03        CMP        slot,0x3
        1402000c3 73 79           JNC        LAB_14020013e
        1402000c5 44 0f b6 d1     MOVZX      R10D,slot
        1402000c9 8b 4c 24 28     MOV        slot,dword ptr [RSP + 0x28]
        1402000cd 4b 8d 04 52     LEA        RAX,[R10 + R10*0x2]
        1402000d1 4c 8d 1c        LEA        R11,[RAX*0x8]
                  c5 00 00
                  00 00
        1402000d9 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  78 45 a0 03
        1402000e0 41 89 94        MOV        dword ptr [R11 + RAX*0x1 + 0x3f8],entityId
                  03 f8 03
                  00 00
        1402000e8 4b 8d 14 52     LEA        entityId,[R10 + R10*0x2]
        1402000ec 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  65 45 a0 03
        1402000f3 45 89 84        MOV        dword ptr [R11 + RAX*0x1 + 0x3fc],entityId2
                  03 fc 03
                  00 00
        1402000fb 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  56 45 a0 03
        140200102 45 89 8c        MOV        dword ptr [R11 + RAX*0x1 + 0x400],entityId3
                  03 00 04
                  00 00
        14020010a 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  47 45 a0 03
        140200111 41 89 8c        MOV        dword ptr [R11 + RAX*0x1 + 0x404],slot
                  03 04 04
                  00 00
        140200119 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  38 45 a0 03
        140200120 8b 4c 24 30     MOV        slot,dword ptr [RSP + 0x30]
        140200124 89 8c d0        MOV        dword ptr [RAX + entityId*0x8 + 0x408],slot
                  08 04 00 00
        14020012b 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  26 45 a0 03
        140200132 8b 4c 24 38     MOV        slot,dword ptr [RSP + 0x38]
        140200136 41 89 8c        MOV        dword ptr [R11 + RAX*0x1 + 0x40c],slot
                  03 0c 04
                  00 00
                              LAB_14020013e                                   XREF[1]:     1402000c3(j)
        14020013e c3              RET
    */
    void DetourOverrideCharacterCreateData(uint8_t slot, uint32_t entityId, uint32_t entityId2, uint32_t entityId3,
        int32_t npcParamId, int32_t npcThinkParamId, int32_t charaInitParamId)
    {
        if (slot < MAX_CLONES)
		{
			LibraCharacterCreateData[slot].entityId = entityId;
			LibraCharacterCreateData[slot].entityId2 = entityId2;
			LibraCharacterCreateData[slot].entityId3 = entityId3;
			LibraCharacterCreateData[slot].npcParamId = npcParamId;
			LibraCharacterCreateData[slot].npcThinkParamId = npcThinkParamId;
			LibraCharacterCreateData[slot].charaInitParamId = charaInitParamId;
		}
	}

    /*
        ResetCharacterCreateData
        AOB: 40 55 48 8b ec 48 83 ec 20 48 8b 05 ?? ?? ?? ?? 33 c9
        Original code:
                              **************************************************************
                              *                          FUNCTION                          *
                              **************************************************************
                              void __fastcall ResetCharacterCreateData(void)
                                assume GS_OFFSET = 0xff00000000
              void              <VOID>         <RETURN>
              undefined8        HASH:3fb7110   GameDataMan
                              ResetCharacterCreateData                        XREF[2]:     FUN_140c24b40:140c24cf7(c),
                                                                                           14472d970(*)
        1401fc800 40 55           PUSH       RBP
        1401fc802 48 8b ec        MOV        RBP,RSP
        1401fc805 48 83 ec 20     SUB        RSP,0x20
        1401fc809 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  48 7e a0 03
        1401fc810 33 c9           XOR        ECX,ECX
        1401fc812 48 c7 45        MOV        qword ptr [RBP + -0x14],-0x1
                  ec ff ff
                  ff ff
        1401fc81a 48 89 4d e0     MOV        qword ptr [RBP + -0x20],RCX
        1401fc81e 89 4d e8        MOV        dword ptr [RBP + -0x18],ECX
        1401fc821 0f 10 45 e0     MOVUPS     XMM0,xmmword ptr [RBP + -0x20]
        1401fc825 c7 45 f4        MOV        dword ptr [RBP + -0xc],0xffffffff
                  ff ff ff ff
        1401fc82c f2 0f 10        MOVSD      XMM1,qword ptr [RBP + -0x10]
                  4d f0
        1401fc831 0f 11 80        MOVUPS     xmmword ptr [RAX + 0x3f8],XMM0
                  f8 03 00 00
        1401fc838 48 c7 45        MOV        qword ptr [RBP + -0x14],-0x1
                  ec ff ff
                  ff ff
        1401fc840 f2 0f 11        MOVSD      qword ptr [RAX + 0x408],XMM1
                  88 08 04
                  00 00
        1401fc848 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  09 7e a0 03
        1401fc84f 48 89 4d e0     MOV        qword ptr [RBP + -0x20],RCX
        1401fc853 89 4d e8        MOV        dword ptr [RBP + -0x18],ECX
        1401fc856 0f 10 45 e0     MOVUPS     XMM0,xmmword ptr [RBP + -0x20]
        1401fc85a c7 45 f4        MOV        dword ptr [RBP + -0xc],0xffffffff
                  ff ff ff ff
        1401fc861 f2 0f 10        MOVSD      XMM1,qword ptr [RBP + -0x10]
                  4d f0
        1401fc866 0f 11 80        MOVUPS     xmmword ptr [RAX + 0x410],XMM0
                  10 04 00 00
        1401fc86d 48 c7 45        MOV        qword ptr [RBP + -0x14],-0x1
                  ec ff ff
                  ff ff
        1401fc875 f2 0f 11        MOVSD      qword ptr [RAX + 0x420],XMM1
                  88 20 04
                  00 00
        1401fc87d 48 8b 05        MOV        RAX,qword ptr [Global_GameDataMan]
                  d4 7d a0 03
        1401fc884 48 89 4d e0     MOV        qword ptr [RBP + -0x20],RCX
        1401fc888 89 4d e8        MOV        dword ptr [RBP + -0x18],ECX
        1401fc88b 0f 10 45 e0     MOVUPS     XMM0,xmmword ptr [RBP + -0x20]
        1401fc88f c7 45 f4        MOV        dword ptr [RBP + -0xc],0xffffffff
                  ff ff ff ff
        1401fc896 f2 0f 10        MOVSD      XMM1,qword ptr [RBP + -0x10]
                  4d f0
        1401fc89b 0f 11 80        MOVUPS     xmmword ptr [RAX + 0x428],XMM0
                  28 04 00 00
        1401fc8a2 f2 0f 11        MOVSD      qword ptr [RAX + 0x438],XMM1
                  88 38 04
                  00 00
        1401fc8aa 48 83 c4 20     ADD        RSP,0x20
        1401fc8ae 5d              POP        RBP
        1401fc8af c3              RET
    */
    void DetourResetCharacterCreateData()
    {
		for (int slot = 0; slot < MAX_CLONES; slot++)
		{
			LibraCharacterCreateData[slot].entityId = 0;
			LibraCharacterCreateData[slot].entityId2 = 0;
			LibraCharacterCreateData[slot].entityId3 = 0;
			LibraCharacterCreateData[slot].npcParamId = -1;
			LibraCharacterCreateData[slot].npcThinkParamId = -1;
			LibraCharacterCreateData[slot].charaInitParamId = -1;
		}
	}
    /*
    GetCharacterCreateData
    AOB: 4c 8b 15 ?? ?? ?? ?? 45 33 c0
    Original code:
                             **************************************************************
                             *                          FUNCTION                          *
                             **************************************************************
                             bool __fastcall GetCharacterCreateData(int param_1, unde
                               assume GS_OFFSET = 0xff00000000
             bool              AL:1           <RETURN>
             int               ECX:4          param_1
             undefined8 *      RDX:8          param_2
                             GetCharacterCreateData                          XREF[1]:     FUN_1403e54d0:1403e55dc(c)
        140201870 4c 8b 15        MOV        R10,qword ptr [Global_GameDataMan]
                  e1 2d a0 03
        140201877 45 33 c0        XOR        R8D,R8D
        14020187a 4c 8b da        MOV        R11,param_2
        14020187d 45 8b c8        MOV        R9D,R8D
        140201880 49 8d 82        LEA        RAX,[R10 + 0x3fc]
                  fc 03 00 00
                              LAB_140201887                                   XREF[1]:     1402018a3(j)
        140201887 3b 48 fc        CMP        param_1,dword ptr [RAX + -0x4]
        14020188a 74 1c           JZ         LAB_1402018a8
        14020188c 3b 08           CMP        param_1,dword ptr [RAX]
        14020188e 74 18           JZ         LAB_1402018a8
        140201890 3b 48 04        CMP        param_1,dword ptr [RAX + 0x4]
        140201893 74 13           JZ         LAB_1402018a8
        140201895 41 ff c0        INC        R8D
        140201898 49 ff c1        INC        R9
        14020189b 48 83 c0 18     ADD        RAX,0x18
        14020189f 49 83 f9 03     CMP        R9,0x3
        1402018a3 7c e2           JL         LAB_140201887
                              LAB_1402018a5                                   XREF[1]:     1402018ab(j)
        1402018a5 32 c0           XOR        AL,AL
        1402018a7 c3              RET
                              LAB_1402018a8                                   XREF[3]:     14020188a(j), 14020188e(j),
                                                                                           140201893(j)
        1402018a8 45 85 c0        TEST       R8D,R8D
        1402018ab 78 f8           JS         LAB_1402018a5
        1402018ad 49 63 c8        MOVSXD     param_1,R8D
        1402018b0 b0 01           MOV        AL,0x1
        1402018b2 48 8d 14 49     LEA        param_2,[RCX + RCX*0x2]
        1402018b6 41 0f 10        MOVUPS     XMM0,xmmword ptr [R10 + param_2*0x8 + 0x3f8]
                  84 d2 f8
                  03 00 00
        1402018bf 41 0f 11 03     MOVUPS     xmmword ptr [R11],XMM0
        1402018c3 f2 41 0f        MOVSD      XMM1,qword ptr [R10 + param_2*0x8 + 0x408]
                  10 8c d2
                  08 04 00 00
        1402018cd f2 41 0f        MOVSD      qword ptr [R11 + 0x10],XMM1
                  11 4b 10
        1402018d3 c3              RET
                              LAB_1402018d4                                   XREF[2]:     FUN_14078eae7:14078eaee(*),
                                                                                           FUN_14078eae7:14078eaf5(*)
        1402018d4 48 8b ea        MOV        RBP,RDX
        1402018d7 4c 8b 45 30     MOV        R8,qword ptr [RBP + 0x30]
        1402018db e9 4a b3        JMP        LAB_140ddcc2a
                  bd 00
        
 */
	bool DetourGetCharacterCreateData(uint32_t targetEntityId, LibraChrDataEntry *entityData)
	{
		for (int slot = 0; slot < MAX_CLONES; slot++)
		{
			if (LibraCharacterCreateData[slot].entityId == targetEntityId ||
				LibraCharacterCreateData[slot].entityId2 == targetEntityId ||
				LibraCharacterCreateData[slot].entityId3 == targetEntityId)
			{
				*entityData = LibraCharacterCreateData[slot];
				return true;
			}
		}
		return false;
	}

    bool installHooks()
    {
        if (MH_Initialize() != MH_OK)
        {
            LilyLib::Util::ShowErrorMessage("Failed to initialize MinHook.");
            return false;
        }
        OverrideCharacterCreateData fnOverrideCharacterCreateData = (OverrideCharacterCreateData)LilyLib::Memory::AOBScanModule("80 f9 03 73 79");
        ResetCharacterCreateData fnResetCharacterCreateData = (ResetCharacterCreateData)LilyLib::Memory::AOBScanModule("40 55 48 8b ec 48 83 ec 20 48 8b 05 ?? ?? ?? ?? 33 c9");
        GetCharacterCreateData fnGetCharacterCreateData = (GetCharacterCreateData)LilyLib::Memory::AOBScanModule("4c 8b 15 ?? ?? ?? ?? 45 33 c0");
        
        if (MH_CreateHook((void*)fnOverrideCharacterCreateData, (void*)DetourOverrideCharacterCreateData, nullptr) != MH_OK)
        {
            LilyLib::Util::ShowErrorMessage("Failed to hook OverrideCharacterCreateData.");
            return false;
        }
        if (MH_CreateHook((void*)fnResetCharacterCreateData, (void*)DetourResetCharacterCreateData, nullptr) != MH_OK)
        {
            LilyLib::Util::ShowErrorMessage("Failed to hook ResetCharacterCreateData.");
            return false;
        }
        if (MH_CreateHook((void*)fnGetCharacterCreateData, (void*)DetourGetCharacterCreateData, nullptr) != MH_OK)
        {
            LilyLib::Util::ShowErrorMessage("Failed to hook GetCharacterCreateData.");
            return false;
        }
        MH_QueueEnableHook(MH_ALL_HOOKS);
        MH_ApplyQueued();
        return true;
    }

    bool removeHooks()
    {
        MH_DisableHook(MH_ALL_HOOKS);
        if (MH_Uninitialize() != MH_OK)
        {
            LilyLib::Util::ShowErrorMessage("Failed to uninitialize MinHook.");
            return false;
        }
        return true;
    }
}