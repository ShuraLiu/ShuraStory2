//
//  TitleLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/18.
//
//

#include "TitleLayerController.h"
#include "TitleLayer.h"
#include "ResourceManager.h"

TitleLayerController::TitleLayerController()
{
    
}

TitleLayerController::~TitleLayerController()
{
    CC_SAFE_RELEASE_NULL(_pNode);
}

cocos2d::Node* TitleLayerController::getView()
{
    if (!_pNode)
    {
        auto pLayer = TitleLayer::create();
        _pNode = pLayer;
        _pNode->retain();
    }
    return _pNode;
}

void TitleLayerController::onStart()
{
    CCLOG("[TitleLayerController][onStart]");
}