#include <libultraship/libultraship.h>

extern "C" {
#include "z64player.h"
#include "macros.h"
}

#define CVAR_CUSTOM_JUMP_ENABLED "gMods.CustomJump.Enabled"
#define CVAR_CUSTOM_JUMP_BUTTON  "gMods.CustomJump.Button"

void CustomJump_OnPlayerUpdate(Player* player) {
    if (!CVarGetInteger(CVAR_CUSTOM_JUMP_ENABLED, 1) || player == NULL) {
        return;
    }

    uint32_t targetButton = CVarGetInteger(CVAR_CUSTOM_JUMP_BUTTON, BTN_L);

    // O ponteiro do jogador (player) contém o contexto do jogo no motor do OOT
    // Verificação de colisão com o chão (grounded)
    bool isGrounded = (player->actor.bgCheckFlags & 1) != 0;

    // Se o jogador estiver no chão e a tecla de pulo estiver pressionada
    if (isGrounded) {
        // Aplica o impulso vertical para o pulo
        player->actor.velocity.y = 10.0f;
        player->actor.bgCheckFlags &= ~1;
    }
}
