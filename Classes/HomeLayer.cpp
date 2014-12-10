//
//  HomeLayer.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "HomeLayer.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

HomeLayer::HomeLayer()
: _pNodeCCS(nullptr)
{
    
}

HomeLayer::~HomeLayer()
{
    
}

bool HomeLayer::init()
{
    if (!BaseView::init())
    {
        return false;
    }
    
    _pNodeCCS = CSLoader::createNode("HomeScene.csb");
    auto winSize = Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _pNodeCCS->setContentSize(winSize);
    addChild(_pNodeCCS);
    
    return true;
}

void HomeLayer::onEnter()
{
    BaseView::onEnter();
}

void HomeLayer::onExit()
{
    BaseView::onExit();
}

void HomeLayer::addSubView(const ViewController::Ptr &controller)
{
    
}