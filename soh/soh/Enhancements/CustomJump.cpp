#include <libultraship/libultraship.h>

extern "C" {
#include "z64.h"
#include "variables.h"
#include "macros.h"
}

#define CVAR_CUSTOM_JUMP_ENABLED "gMods.CustomJump.Enabled"
#define CVAR_CUSTOM_JUMP_BUTTON  "gMods.CustomJump.Button"

void CustomJump_OnPlayerUpdate(Player* player) {
    if (!CVarGetInteger(CVAR_CUSTOM_JUMP_ENABLED, 1) || player == NULL || gPlayState == NULL) {
        return;
    }

    // Acesso correto aos inputs na versão recente do Shipwright
    Input* input = &gPlayState->state.input[0];
    uint32_t targetButton = CVarGetInteger(CVAR_CUSTOM_JUMP_BUTTON, BTN_L);

    bool isButtonPressed = CHECK_BTN_ALL(input->press.button, targetButton);
    bool isGrounded = (player->actor.bgCheckFlags & 1) != 0;

    if (isButtonPressed && isGrounded) {
        player->actor.velocity.y = 10.0f;
        player->actor.bgCheckFlags &= ~1;
    }
}
