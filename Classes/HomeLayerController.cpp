//
//  HomeLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "HomeLayerController.h"
#include "SubLayerController.h"

HomeLayerController::HomeLayerController()
: _pLayer(nullptr)
{
    
}
cocos2d::Node* HomeLayerController::createView()
{
    _pLayer = HomeLayer::create();
    _pLayer->setHomeLayerUIEventDelegate(this);
    return _pLayer;
}

void HomeLayerController::onStart()
{
    CCLOG("[HomeLayerController][onStart]");
}

void HomeLayerController::onButtonTestPressed()
{
    SubLayerController::Ptr pSubLayerController(new SubLayerController());
    _children.push_back(pSubLayerController);
    _pLayer->addSubView(pSubLayerController, pSubLayerController->TYPE);
}