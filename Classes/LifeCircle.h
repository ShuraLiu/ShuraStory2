//
//  LifeCircle.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__LifeCircle__
#define __ShuraStory__LifeCircle__

#include <stdio.h>

class LifeCircle
{
private:
    enum class State : int
    {
        Active,
        Running,
        Paused,
    };
    
public:
    LifeCircle();
    
public:
    bool start();
    bool resume();
    bool pause();
    bool stop();
    
    virtual void onStart(){};
    virtual void onResume(){};
    virtual void onPause(){};
    virtual void onStop(){};
    
    bool isActive();
    bool isRunning();
    bool isPaused();
    
private:
    State _state;
};

#endif /* defined(__ShuraStory__LifeCircle__) */
