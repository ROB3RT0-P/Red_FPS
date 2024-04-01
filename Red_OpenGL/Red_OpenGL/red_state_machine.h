/*******************************************
    Written by Robert Parry [RJP] - 2024
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

class Game; // RJP - Forward declaration

enum class GameState {
    MENU,
    PLAY,
    PAUSE,
    GAME_OVER
};

class StateMachine {
private:
    GameState currentState;

public:
    StateMachine() : currentState(GameState::MENU) {}

    void setState(GameState newState) {
        currentState = newState;
    }

    GameState getState() const {
        return currentState;
    }

    void executeState(Game* game);
};
