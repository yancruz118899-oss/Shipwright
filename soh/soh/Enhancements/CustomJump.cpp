#include "soh/Enhancements/game-interceptor/CommandManager.h"
#include "soh/OTRGlobals.h"
#include "z64player.h"
#include <libultraship/bridge.h>

#define CVAR_CUSTOM_JUMP_ENABLED "gMods.CustomJump.Enabled"
#define CVAR_CUSTOM_JUMP_BUTTON  "gMods.CustomJump.Button" 

void CustomJump_OnPlayerUpdate(Player* player) {
    if (!CVarGetInteger(CVAR_CUSTOM_JUMP_ENABLED, 0) || player == NULL) {
        return;
    }

    Input* input = &gGameInfo->frameControl[0]; 
    uint32_t targetButton = CVarGetInteger(CVAR_CUSTOM_JUMP_BUTTON, BTN_L);

    bool isButtonPressed = (input->press.button & targetButton) != 0;
    bool isGrounded = (player->actor.bgCheckFlags & 1) != 0;
    bool isBusy = (player->stateFlags1 & (0x10000000 | 0x08000000 | 0x00000800 | 0x00002000)); 

    if (isButtonPressed && isGrounded && !isBusy) {
        player->actor.velocity.y = 10.0f;
        player->actor.bgCheckFlags &= ~1;

        Audio_PlaySoundGeneral(0x4809, &player->actor.projectedPos, 4, 
                               &gSfxDefaultFreq, &gSfxDefaultVol, &gSfxDefaultReverb);
    }
}

void InitCustomJumpMod() {
    Ship::RegisterHook<Ship::OnPlayerUpdate>(CustomJump_OnPlayerUpdate);
}

struct CustomJumpAutoInit {
    CustomJumpAutoInit() {
        InitCustomJumpMod();
    }
};
static CustomJumpAutoInit gCustomJumpAutoInit;

