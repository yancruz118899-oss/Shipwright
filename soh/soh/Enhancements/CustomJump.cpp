#include <libultraship/libultraship.h>

extern "C" {
#include "z64player.h"
}

#define CVAR_CUSTOM_JUMP_ENABLED "gMods.CustomJump.Enabled"
#define CVAR_CUSTOM_JUMP_BUTTON  "gMods.CustomJump.Button"

static void CustomJump_OnPlayerUpdate(Player* player) {
    if (!CVarGetInteger(CVAR_CUSTOM_JUMP_ENABLED, 1) || player == NULL) {
        return;
    }

    Input* input = &gGameInfo->frameControl[0];
    uint32_t targetButton = CVarGetInteger(CVAR_CUSTOM_JUMP_BUTTON, BTN_L);

    bool isButtonPressed = (input->press.button & targetButton) != 0;
    bool isGrounded = (player->actor.bgCheckFlags & 1) != 0;

    if (isButtonPressed && isGrounded) {
        player->actor.velocity.y = 10.0f;
        player->actor.bgCheckFlags &= ~1;
    }
}

struct CustomJumpInit {
    CustomJumpInit() {
        Ship::RegisterHook<Ship::OnPlayerUpdate>(CustomJump_OnPlayerUpdate);
    }
};

static CustomJumpInit gCustomJumpInit;
