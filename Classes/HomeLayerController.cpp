//
//  HomeLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "HomeLayerController.h"
#include "HomeLayer.h"

cocos2d::Node* HomeLayerController::createView()
{
    return HomeLayer::create();
}

void HomeLayerController::onStart()
{
    CCLOG("[HomeLayerController][onStart]");
}