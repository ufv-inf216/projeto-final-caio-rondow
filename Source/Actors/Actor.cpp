#include "Actor.h"
#include "../Game/InterfaceGame.h"

/* CONSTRUCTORS AND DESTRUCTOR */
Actor::Actor(InterfaceGame *game):
    mGame(game),
    mScale(1.0f),
    mRotation(0.0f),
    mPosition(Vector2::Zero),
    mState(ActorState::ACTIVE),
    mFlip(false)
{
    mGame->AddActor(this);
}

Actor::~Actor(){
    mGame->RemoveActor(this);
    for(auto component : mComponents){
        delete component;
    }
}

/* PUBLIC METHODS */
    
/* Generic actor update code */
void Actor::Update(float DeltaTime){

    if(mState == ActorState::ACTIVE){
        for(auto component : mComponents){
            if( component->IsComponentEnabled() ){
                component->Update(DeltaTime);
            }
        }
        OnUpdate(DeltaTime); // update specific task
    }
}

void Actor::ProcessInput(const Uint8 *KeyState){
    if(mState == ActorState::ACTIVE){
        for(auto component : mComponents){
            if( component->IsComponentEnabled() ){
                component->ProcessInput(KeyState);
            }
        }
        OnProcessInput(KeyState); // process specific task
    }
}

/* Getters and Setters */
/* Position */
const Vector2 &Actor::GetPosition() const{
    return mPosition;
}

void Actor::SetPosition(const Vector2&position){
    mPosition = position;
}

/* Scale */
float Actor::GetScale() const{
    return mScale;
}

void Actor::SetScale(const float scale){
    mScale = scale;
}

/* Rotation */
float Actor::GetRotation() const{
    return mRotation;
}

void Actor::SetRotation(const float rotation){
    mRotation = rotation;
}

/* Actor State */
ActorState Actor::GetActorState() const{
    return mState;
}

void Actor::SetActorState(ActorState state){
    mState = state;
}

bool Actor::GetFlip() const{
    return mFlip;
}
void Actor::SetFlip(const bool flip){
    mFlip = flip;
}

/* Game */
InterfaceGame *Actor::GetGame() const{
    return mGame;
}

/* Specific actor update code */
void Actor::OnUpdate(float DeltaTime){

}

void Actor::OnProcessInput(const Uint8 *KeyState){

}

void Actor::OnCollision(Actor *response){

}

bool Actor::DetectCollision(){
    return false; // standard is to ignore collisions
}

/* PRIVATE METHODS */
void Actor::AddComponent(Component *component){
    mComponents.emplace_back(component);
    std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
        return a->GetUpdateOrder() < b->GetUpdateOrder();
    });
}