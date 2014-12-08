//
//  HomeSceneController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/8.
//
//

#include "HomeSceneController.h"
#include "HomeScene.h"

cocos2d::Node* HomeSceneController::createView()
{
    return HomeScene::create();
}

void HomeSceneController::onStart()
{
    CCLOG("[HomeSceneController][onStart]");
}