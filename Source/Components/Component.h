#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../Utils/Math.h"

#define COMPONENT_STATE_ENABLED 1
#define COMPONENT_STATE_DISABLED 0

class Actor;

class Component{ /* This is the Component abstract class */ 
public:
    /* CONSTRUCTOR AND DESTRUCTOR */
    explicit Component(Actor *owner, int UpdateOrder=10);
    virtual ~Component();    

    /* PUBLIC METHODS */
    
    /* Component specific */
    virtual void Update(float DeltaTime) = 0;
    virtual void ProcessInput(const Uint8 *KeyState) = 0;
    /* Actor related */
    int GetUpdateOrder() const;
    Actor &GetOwner() const;
    /* Component state */
    void SetComponentState(bool state);
    bool IsComponentEnabled() const;

protected:
    /* PROTECTED ATTRIBUTES */
    Actor *mOwner;
    int mUpdateOrder;
    bool mState;
};