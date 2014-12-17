//
//  TitleLayer.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#include "TitleLayer.h"
#include"cocostudio/CocoStudio.h"

TitleLayer::TitleLayer()
{
    
}

TitleLayer::~TitleLayer()
{
    
}

bool TitleLayer::init()
{
    if (!BaseView::init())
    {
        return false;
    }
    
    auto pNode = cocos2d::CSLoader::createNode("TitleScene.csb");
    auto winSize = cocos2d::Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    
    pNode->setPosition(cocos2d::Vec2((winSize.width - pNode->getContentSize().width) / 2, (winSize.height - pNode->getContentSize().height) / 2));
    addChild(pNode);
    
    return true;
}