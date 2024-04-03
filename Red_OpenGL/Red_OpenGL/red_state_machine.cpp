/*******************************************
    Written by Robert Parry [RJP] - 2024
    Refer to red_main.cpp for the license
*******************************************/

#include "red_state_machine.h"
#include "red_game.h"

void StateMachine::executeState(Game* game) 
{
    switch (currentState) 
    {
        case GameState::MENU:
            game->menuRun();
            break;
        case GameState::PLAY:
            game->gameRun();
            break;
        case GameState::PAUSE:
            game->pauseRun();
            break;
        case GameState::GAME_OVER:
            game->gameOverRun();
            break;
    }
}