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
    void SetScale(float scale);

    float GetRotation() const;
    void SetRotation(float rotation);

    ActorState GetActorState() const;
    void SetActorState(ActorState state);

    inline bool GetFlip() const{
        return mFlip;
    }
    inline void SetFlip(const bool flip){
        mFlip = flip;
    }

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

    /* Actor width/height */
    inline int GetWidth() const { return mWidth; }
    inline int GetHeight() const { return mHeight; }
    inline void SetWidth(const uint width) { mWidth = width; }
    inline void SetHeight(const uint height) { mHeight = height; }

protected:
    /* PROTECTED METHODS */

    /* Specific actor update code */
    virtual void OnUpdate(float DeltaTime);
    virtual void OnProcessInput(const Uint8 *KeyState);

    /* PROTECTED ATTRIBUTES */
    InterfaceGame *mGame;
    ActorState mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;
    bool mFlip;
    std::vector<Component*> mComponents;
    int mWidth, mHeight;

private:
    /* PRIVATE METHODS */
    void AddComponent(Component *c);
};