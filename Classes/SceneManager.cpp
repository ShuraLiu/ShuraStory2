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
        _controllerStack.at(_controllerStack.size() - 1)->stop();
        _controllerStack.pop_back();
        pDirector->popScene();
    }
}

void SceneManager::pushViewController(const ViewController::Ptr& controller, bool withAnimation/* = false*/)
{
    cocos2d::Scene* pScene = dynamic_cast<cocos2d::Scene*>(controller->createView());
    assert(pScene);
    auto pDirector = cocos2d::Director::getInstance();
    if(!pDirector->getRunningScene())
    {
        _controllerStack.push_back(controller);
        pDirector->runWithScene(pScene);
    }
    else
    {
        auto pLast = _controllerStack.at(_controllerStack.size() - 1);
        pLast->pause();
        _controllerStack.push_back(controller);
        pDirector->pushScene(pScene);
    }
    controller->start();
}

void SceneManager::popViewController(bool withAnimation/* = false*/)
{
    auto pController = _controllerStack.at(_controllerStack.size() - 1);
    pController->stop();
    _controllerStack.pop_back();
    cocos2d::Director::getInstance()->popScene();
    if (!_controllerStack.empty())
    {
        _controllerStack.at(_controllerStack.size() - 1)->resume();
    }
}

void SceneManager::replaceViewController(const ViewController::Ptr &controller, bool withAnimation/* = false*/)
{
    cocos2d::Scene* pScene = dynamic_cast<cocos2d::Scene*>(controller->createView());
    assert(pScene);
    auto pLast = _controllerStack.at(_controllerStack.size() - 1);
    pLast->stop();
    _controllerStack.pop_back();
    _controllerStack.push_back(controller);
    cocos2d::Director::getInstance()->replaceScene(pScene);
    controller->start();
}
