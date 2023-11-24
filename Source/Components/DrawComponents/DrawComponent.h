#pragma once

#include "../Component.h"

#define DRAWABLE_STATE_VISIBLE 1
#define DRAWABLE_STATE_INVISIBLE 0

class DrawComponent : public Component{
public:
    /* CONSTUCTOR AND DESTRUCTOR */
    explicit DrawComponent(Actor *owner, int DrawOrder=10);
    ~DrawComponent() override;
    
    /* PUBLIC METHODS */
    void Update(float DeltaTime) override;
    void ProcessInput(const Uint8 *KeyState) override;
    /* specific for the draw component (e.g.: Sprite, Animated Sprite...) */
    virtual void Draw(SDL_Renderer *renderer);
    /* drawable visibility */
    bool IsVisible() const;
    void SetDrawableState(bool state);

    int GetDrawOrder() const;

protected:
    /* PROTECTED ATTRIBUTES */
    bool mState;
    int mDrawOrder;
};