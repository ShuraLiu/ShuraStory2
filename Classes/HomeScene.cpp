//
//  HomeScene.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/8.
//
//

#include "HomeScene.h"
#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

HomeScene::HomeScene()
{
    
}

HomeScene::~HomeScene()
{
    
}

bool HomeScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    _pNodeRoot = CSLoader::createNode("HomeScene.csb");
    auto winSize = Director::getInstance()->getWinSize();
    _pNodeRoot->setContentSize(winSize);
    addChild(_pNodeRoot);
    
    return true;
}

void HomeScene::onEnter()
{
    Scene::onEnter();
}

void HomeScene::onExit()
{
    Scene::onExit();
}