//
//  GameScene.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/4.
//
//

#ifndef __ShuraStory__GameScene__
#define __ShuraStory__GameScene__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    virtual ~GameScene();
    CREATE_FUNC(GameScene);
    
    bool init() override;
    void onEnter() override;
    void onExit() override;
};

#endif /* defined(__ShuraStory__GameScene__) */
