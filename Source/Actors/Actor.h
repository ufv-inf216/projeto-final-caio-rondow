#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../Utils/Math.h"
#include "../Components/Component.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"

enum class ActorState{
    ACTIVE,
    PAUSED,
    DESTROY
};

class Component;
class InterfaceGame;

class Actor{ /* This is the actor abstract class */
friend class Component;
public:
    Actor(InterfaceGame *game);
    virtual ~Actor();

    void Update(float DeltaTime);
    void ProcessInput(const Uint8* KeyState);
    
    const Vector2 &GetPosition() const;
    void SetPosition(const Vector2&position);
    
    float GetScale() const;
    void SetScale(const float scale);

    float GetRotation() const;
    void SetRotation(const float rotation);

    ActorState GetActorState() const;
    void SetActorState(ActorState state);

    bool GetFlip() const;
    void SetFlip(const bool flip);

    InterfaceGame *GetGame() const;

    virtual void OnCollision(const std::vector<Actor*>&responses);

    template <typename T>
    T* GetComponent() const{
        for (auto c : mComponents){
            T* t = dynamic_cast<T*>(c);
            if (t != nullptr){
                return t;
            }
        }
        return nullptr;
    }

protected:

    /* Specific actor update code */
    virtual void OnUpdate(float DeltaTime);
    virtual void OnProcessInput(const Uint8 *KeyState);

    /* PROTECTED ATTRIBUTES */
    InterfaceGame *mGame;
    std::vector<Component*> mComponents;
   
    Vector2 mPosition;
    ActorState mState;
    float mRotation;
    float mScale;
    bool mFlip;
    
private:
    /* PRIVATE METHODS */
    void AddComponent(Component *c);
};