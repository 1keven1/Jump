#pragma once
#include "GtActor.h"
class Rock :
    public GtActor
{
public:
    Rock();
    ~Rock();
    bool BeenHit(GtActor* p);
    bool OutOfScreen();
    virtual void Restart();
    bool CanScore(GtActor* p);
private:
    virtual void OnInit();
    virtual void OnUpdate(float fElapsedTime);
    virtual void OnDestroy();
    virtual void OnKey(const SInputEvent& event);

private:
    GtBitmap* rock;
    float speed;
    bool bScore;
    int random;
};

