//
//  LifeCircle.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#include "LifeCircle.h"

LifeCircle::LifeCircle()
: _state(State::Active)
{
    
}

bool LifeCircle::start()
{
    if (isActive())
    {
        _state = State::Running;
        onStart();
        return true;
    }
    return false;
}

bool LifeCircle::resume()
{
    if (isPaused())
    {
        _state = State::Running;
        onResume();
        return true;
    }
    return false;
}

bool LifeCircle::pause()
{
    if (isRunning())
    {
        _state = State::Paused;
        onPause();
        return true;
    }
    return false;
}

bool LifeCircle::stop()
{
    if (isRunning())
    {
        _state = State::Active;
        onStop();
        return true;
    }
    return false;
}

bool LifeCircle::isActive()
{
    return _state == State::Active;
}

bool LifeCircle::isRunning()
{
    return _state == State::Running;
}

bool LifeCircle::isPaused()
{
    return _state == State::Paused;
}
