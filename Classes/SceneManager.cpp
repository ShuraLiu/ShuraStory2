//
//  SceneManager.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/4.
//
//

#include "SceneManager.h"
#include "cocos2d.h"

SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    auto pDirector = cocos2d::Director::getInstance();
    while (!_controllerStack.empty())
    {
        _controllerStack.pop_back();
        pDirector->popScene();
    }
}

void SceneManager::pushViewController(const ViewController::Ptr& controller, bool withAnimation/* = false*/)
{
    _controllerStack.push_back(controller);
    cocos2d::Scene* pScene = dynamic_cast<cocos2d::Scene*>(controller->createView());
    assert(pScene);
    auto pDirector = cocos2d::Director::getInstance();
    if(!pDirector->getRunningScene())
    {
        pDirector->runWithScene(pScene);
    }
    else
    {
        pDirector->pushScene(pScene);
    }
}

void SceneManager::popViewController(bool withAnimation/* = false*/)
{
    _controllerStack.pop_back();
    cocos2d::Director::getInstance()->popScene();
}

void SceneManager::replaceViewController(const ViewController::Ptr &controller, bool withAnimation/* = false*/)
{
    _controllerStack.pop_back();
    _controllerStack.push_back(controller);
    cocos2d::Scene* pScene = dynamic_cast<cocos2d::Scene*>(controller->createView());
    assert(pScene);
    cocos2d::Director::getInstance()->replaceScene(pScene);
}
