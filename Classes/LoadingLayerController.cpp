//
//  LoadingLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#include "LoadingLayerController.h"
#include "LoadingLayer.h"

LoadingLayerController::LoadingLayerController()
{
    CC_SAFE_RELEASE_NULL(_pNode);
}

cocos2d::Node* LoadingLayerController::getView()
{
    if (!_pNode)
    {
        auto pLayer = LoadingLayer::create();
        _pNode = pLayer;
        _pNode->retain();
    }
    return _pNode;
}

void LoadingLayerController::onStart()
{
    CCLOG("[LoadingLayerController][onStart]");
}