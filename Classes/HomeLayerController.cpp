//
//  HomeLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "HomeLayerController.h"

HomeLayerController::HomeLayerController()
: _pSubLayerController(nullptr)
{
    
}
cocos2d::Node* HomeLayerController::getView()
{
    if (!_pNode)
    {
        auto pLayer = HomeLayer::create();
        pLayer->setHomeLayerUIEventDelegate(this);
        _pNode = pLayer;
        _pNode->retain();
    }
    return _pNode;
}

void HomeLayerController::onStart()
{
    CCLOG("[HomeLayerController][onStart]");
}

void HomeLayerController::onButtonTestPressed()
{
    if (!_pSubLayerController)
    {
        _pSubLayerController = std::make_shared<SubLayerController>();
    }
    _pNode->addSubView(_pSubLayerController);
}

void HomeLayerController::onButtonTest2Pressed()
{
    _pNode->removeSubView(_pSubLayerController);
}