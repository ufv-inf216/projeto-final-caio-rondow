#include "Component.h"
#include "../Actors/Actor.h"

/* CONSTRUCTOR AND DESTRUCTOR */
Component::Component(Actor *owner, int UpdateOrder):
    mOwner(owner),
    mUpdateOrder(UpdateOrder),
    mState(COMPONENT_STATE_ENABLED)
{
    mOwner->AddComponent(this);
}

Component::~Component(){

}

/* PUBLIC METHODS */
int Component::GetUpdateOrder() const{
    return mUpdateOrder;
}

Actor &Component::GetOwner() const{
    return *mOwner;
}

void Component::SetComponentState(bool state){
    mState = state;
}

bool Component::IsComponentEnabled() const{
    return mState;
}