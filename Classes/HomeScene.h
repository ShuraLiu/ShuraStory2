//
//  HomeScene.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/8.
//
//

#ifndef __ShuraStory__HomeScene__
#define __ShuraStory__HomeScene__

#include "cocos2d.h"

class HomeScene : public cocos2d::Scene
{
public:
    HomeScene();
    virtual ~HomeScene();
    CREATE_FUNC(HomeScene);
    
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
private:
    cocos2d::Node* _pNodeRoot;
};

#endif /* defined(__ShuraStory__HomeScene__) */
