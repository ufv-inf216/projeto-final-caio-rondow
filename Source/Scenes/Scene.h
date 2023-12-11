#pragma once

#include "../Game/InterfaceGame.h"

class Scene{
public:
    Scene(InterfaceGame *game);

    virtual void Load();
    virtual void ProcessInput(const Uint8 *KeyState);

    InterfaceGame *GetGame() const;

protected:
    InterfaceGame *mGame;
};