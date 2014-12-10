//
//  SubLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "SubLayerController.h"
#include "SubLayer.h"

cocos2d::Node* SubLayerController::createView()
{
    return SubLayer::create();
}