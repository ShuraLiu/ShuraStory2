//
//  LoadingLayer.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#include "LoadingLayer.h"
#include"cocostudio/CocoStudio.h"

LoadingLayer::LoadingLayer()
{

}

LoadingLayer::~LoadingLayer()
{
    
}

bool LoadingLayer::init()
{
    if (!BaseView::init())
    {
        return false;
    }
    
    auto pNode = cocos2d::CSLoader::createNode("LoadingScene.csb");
    auto winSize = cocos2d::Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    
    pNode->setPosition(cocos2d::Vec2((winSize.width - pNode->getContentSize().width) / 2, (winSize.height - pNode->getContentSize().height) / 2));
    addChild(pNode);
    
    return true;
}