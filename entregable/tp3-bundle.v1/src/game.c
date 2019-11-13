/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

uint32_t points_y = 41;

uint32_t message_x[2] = {
    3,
    43,
};

uint32_t message_y[3] = {
    46,
    47,
    48,
};

uint16_t message_color[2] = {
    C_BG_RED + C_FG_WHITE,
    C_BG_BLUE + C_FG_WHITE,
};

uint16_t bg_color = C_BG_LIGHT_GREY + C_FG_LIGHT_GREY;

uint16_t ball_color[2] = {
    C_BG_LIGHT_GREY + C_FG_RED,
    C_BG_LIGHT_GREY + C_FG_BLUE,
};

uint16_t player_color[2] = {
    C_BG_RED + C_FG_BLACK,
    C_BG_BLUE + C_FG_CYAN,
};

uint32_t player_points[2] = {
    0,
    0
};

uint32_t player_x[2] = {
    0,
    79
};
uint32_t prev_player_y[2] = {
    0,
    0
};
uint32_t player_y[2] = {
    0,
    0
};

uint32_t prev_ball_x[6];
uint32_t prev_ball_y[6];
uint32_t ball_x[6];
uint32_t ball_y[6];

e_action_t ball_current_actions[6];
short ball_current_directions_x[6];
short ball_current_directions_y[6];

char *ballChar = "o";
char *missingBallChar = "X";
char *playerBgChar = "@";

uint32_t keys[10] = {
    SCAN_CODE_W,
    SCAN_CODE_S,
    SCAN_CODE_Z,
    SCAN_CODE_X,
    SCAN_CODE_C,
    SCAN_CODE_I,
    SCAN_CODE_K,
    SCAN_CODE_B,
    SCAN_CODE_N,
    SCAN_CODE_M,
};

uint32_t keyPresses[10];

/* ---------------------------- UI UTILS ---------------------------- */
void printIfValid(char* msg, uint32_t x, uint32_t y, uint16_t color) {
    if (x < BOARD_W && y < BOARD_H) {
        print(msg, x, y, color);
    }
}

void printPlayer(uint32_t x, uint32_t y, uint16_t color) {
    for (int i = 0; i < PLAYER_SIZE; i++) {
        printIfValid(playerBgChar, x, y + i, color);
    }
}
/* ---------------------------- UI UTILS ---------------------------- */

uint8_t hitPlayerAGoal(uint32_t x, uint32_t y) {
    // Devuelve true si está en la posición del goal de A y el jugador
    // A no está en la posición de impacto de la pelota!
    return x == PLAYER_A_GOAL && y < player_y[0] && y > player_y[0] + 6;
}

uint8_t hitPlayerBGoal(uint32_t x, uint32_t y) {
    // Devuelve true si está en la posición del goal de A y el jugador
    // A no está en la posición de impacto de la pelota!
    return x == PLAYER_B_GOAL && y < player_y[1] && y > player_y[1] + 6;
}

void game_movePlayerUp(uint8_t player) {
    // Mueve el jugador para arriba, de ser posible
    if (player_y[player] > 0) {
        player_y[player]--;
    }
}

void game_movePlayerDown(uint8_t player) {
    // Mueve el jugador para abajo, de ser posible
    if (player_y[player] < BOARD_H - PLAYER_SIZE) {
        player_y[player]++;
    }
}

void game_setDefaultBallDirections(PLAYER ballIndex) {
    e_action_t ball_current_actions[ballIndex] = Center;
    // El jugador A tiene direccion positiva por defecto, el B al reves
    short ball_current_directions_x[ballIndex] = ballIndex / 2 == 0 ? 1 : -1;
    short ball_current_directions_y[ballIndex] = 1;
}

void game_launchBall(PLAYER ballType) {
    sched_newBall(ballType);

    // Configuramos las direcciones de la pelota y su posicion
    game_setDefaultBallDirections(ballType);

    prev_ball_x[i] = player_x[ballType] + ball_current_directions_x[ballType];
    prev_ball_y[i] = player_y[ballType] + PLAYER_SIZE / 2;
}

void game_init() {
    for (uint32_t i = 0; i < 6; i++) {
        prev_ball_x[i] = 1000;
        prev_ball_y[i] = 1000;
        ball_x[i] = 1000;
        ball_y[i] = 1000;

        game_setDefaultBallDirections(i);
    }
}

void game_executeBallCalculations() {
    for (int i = 0; i < 6; i++) {
        uint32_t x = prev_ball_x[i];
        uint32_t y = prev_ball_y[i];

        e_action_t direction = ball_current_actions[i];
        switch (direction) {
            case Up:
                y -= 1 * ball_current_directions_y[i];
                break;

            case Center:
                // NO-OP, la pelota sigue moviéndose derecho
                break;

            case Down:
                y += 1 * ball_current_directions_y[i];
                break;
        }

        x += 1 * ball_current_directions_x[i];

        if (hitPlayerAGoal(x, y)) {
            // Matar la tarea de la pelota!
            sched_makeItLookLikeAnAccident();
            player_points[PLAYER_B]++;

            ball_x[i] = 1000;
            ball_y[i] = 1000; // Posiciones invalidas
        } else if (hitPlayerBGoal(x, y)) {
            // Matar la tarea de la pelota!
            sched_makeItLookLikeAnAccident();
            player_points[PLAYER_A]++;

            ball_x[i] = 1000;
            ball_y[i] = 1000; // Posiciones invalidas
        } else {
            ball_x[i] = x;
            ball_y[i] = y;
        }
    }
}

void game_executeInputCalculations() {
    if (keyPresses[PLAYER_A_UP]) game_movePlayerUp(PLAYER_A);
    if (keyPresses[PLAYER_A_DOWN]) game_movePlayerDown(PLAYER_A);
    if (keyPresses[PLAYER_A_BALL_1]) game_launchBall(PLAYER_A_TIPO_1);
    if (keyPresses[PLAYER_A_BALL_2]) game_launchBall(PLAYER_A_TIPO_2);
    if (keyPresses[PLAYER_A_BALL_3]) game_launchBall(PLAYER_A_TIPO_3);
    if (keyPresses[PLAYER_B_UP]) game_movePlayerUp(PLAYER_B);
    if (keyPresses[PLAYER_B_DOWN]) game_movePlayerDown(PLAYER_B);
    if (keyPresses[PLAYER_B_BALL_1]) game_launchBall(PLAYER_B_TIPO_1);
    if (keyPresses[PLAYER_B_BALL_2]) game_launchBall(PLAYER_B_TIPO_2);
    if (keyPresses[PLAYER_B_BALL_3]) game_launchBall(PLAYER_B_TIPO_3);
}

void game_executeFrameCalculations() {
    game_executeBallCalculations();
    game_executeInputCalculations();
}

void game_executeFrame() {
    game_executeFrameCalculations();

    // Pintar pelotas
    for (int i = 0; i < 6; i++) {
        // Limpiar anteriores
        uint32_t x = prev_ball_x[i];
        uint32_t y = prev_ball_y[i];
        uint16_t color = bg_color;
        printIfValid(ballChar, x, y, color);

        // Imprimir nuevas
        x = ball_x[i];
        y = ball_y[i];
        color = ball_color[i];
        printIfValid(ballChar, x, y, color);
        
        // Actualizar pelotas previas
        prev_ball_x[i] = x;
        prev_ball_y[i] = y;
    }

    // Pintar paletas
    for (int i = 0; i < 2; i++) {
        // Limpiar anteriores
        uint32_t x = player_x[i];
        uint32_t y = prev_player_y[i];
        uint16_t color = bg_color;
        printPlayer(x, y, color);

        // Imprimir nuevas
        y = player_y[i];
        color = player_color[i];
        printPlayer(x, y, color);
        
        // Actualizar posición previa
        prev_player_y[i] = y;
    }

    // Pintar puntos
    for (int i = 0; i < 2; i++) {
        // Limpiar anteriores
        uint32_t x = message_x[i];
        uint32_t y = points_y;
        uint16_t color = message_color[i];

        print_dec(player_points[i], 2, x, y, color);
    }

    // Pintar pelotas disponibles
    for (int i = 0; i < 6; i++) {
        uint32_t x = message_x[i] + 10 + i;
        uint32_t y = points_y;
        uint16_t color = message_color[i];

        if (ball_x[i] >= BOARD_W) {
            print(ballChar, x, y, color);
        } else {
            print(missingBallChar, x, y, color);
        }
    }
}

void game_talk(const char *msg) {
    uint32_t currentBall = sched_getTareaActual();

    // Truncamos texto, rellenamos con espacios para limpiar
    char displayMsg[20];
    for (uint8_t i = 0; i < 20; i++) {
        char toWrite = ' ';
        if (*msg != 0) {
            toWrite = *msg;
            msg++;
        }
        displayMsg[i] = toWrite;
    }
    
    // Las 1ras 3 tareas son del Player A, las otras 3 del Player B
    uint32_t x = message_x[currentBall / 3];
    uint32_t y = message_y[currentBall % 3];
    uint16_t color = message_color[currentBall / 3];
    print(displayMsg, x, y, color);
}

uint32_t game_getCurrentX() {
    uint32_t currentBall = sched_getTareaActual();
    return ball_x[currentBall];
}

uint32_t game_getCurrentY() {
    uint32_t currentBall = sched_getTareaActual();
    return ball_y[currentBall];
}

void game_informAction(e_action_t action) {
    uint32_t currentBall = sched_getTareaActual();
    ball_current_actions[currentBall] = action;
}


void game_kbInput(uint32_t input) {
    // Vemos que tecla se està presionando
    for(int i = 0; i < 10; i++) {
        if(keys[i] == input) {
            keyPresses[i] = 1;
        } else if (BREAK_CODE(keys[i]) == input) {
            keyPresses[i] = 0;
        }
    }
}