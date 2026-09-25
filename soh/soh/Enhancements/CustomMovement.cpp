#include "global.h"
#include "game-interactor/GameInteractor.h"
#include "game-interactor/GameInteractor_Hooks.h"

#define CVAR_CUSTOM_MOVEMENT_ENABLED "gMods.CustomMovement.Enabled"
#define CVAR_CUSTOM_MOVEMENT_JUMP_FORCE "gMods.CustomMovement.JumpForce"

static void CustomMovement_OnPlayerUpdate() {
    if (!CVarGetInteger(CVAR_CUSTOM_MOVEMENT_ENABLED, 1)) {
        return;
    }

    if (gPlayState == nullptr) {
        return;
    }

    Player* player = GET_PLAYER(gPlayState);

    if (player == nullptr) {
        return;
    }

    /*
     * CUSTOM JUMP
     *
     * Primeiro teste:
     * L = pulo
     *
     * Vamos tornar o botão configurável em uma etapa posterior,
     * depois que confirmarmos que o hook compila corretamente.
     */

    bool grounded = (player->actor.bgCheckFlags & 1) != 0;

    if (!grounded) {
        return;
    }

    if (!CHECK_BTN_ALL(gPlayState->state.input[0].press.button, BTN_L)) {
        return;
    }

    float jumpForce =
        CVarGetFloat(CVAR_CUSTOM_MOVEMENT_JUMP_FORCE, 10.0f);

    player->actor.velocity.y = jumpForce;

    player->actor.bgCheckFlags &= ~1;
}

void CustomMovement_Init() {
    COND_HOOK(OnPlayerUpdate, true, []() {
        CustomMovement_OnPlayerUpdate();
    });
}
