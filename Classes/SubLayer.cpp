//
//  SubLayer.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "SubLayer.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

SubLayer::SubLayer()
: _pNodeCCS(nullptr)
{
    
}

SubLayer::~SubLayer()
{
    
}

bool SubLayer::init()
{
    if (!BaseView::init())
    {
        return false;
    }
    
    _pNodeCCS = CSLoader::createNode("SubLayer.csb");
    auto winSize = Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _pNodeCCS->setContentSize(winSize);
    addChild(_pNodeCCS);
    
    return true;
}

void SubLayer::onEnter()
{
    BaseView::onEnter();
}

void SubLayer::onExit()
{
    BaseView::onExit();
}