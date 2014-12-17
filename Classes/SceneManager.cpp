//
//  SceneManager.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/4.
//
//

#include "SceneManager.h"
#include "cocos2d.h"

const char* KEY_PUSH_VIEW_CONTROLLER = "key_push_view_controller";

SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    auto pDirector = cocos2d::Director::getInstance();
    pDirector->getScheduler()->unschedule(KEY_PUSH_VIEW_CONTROLLER, this);
    while (!_controllerStack.empty())
    {
        _controllerStack.at(_controllerStack.size() - 1)->stop();
        _controllerStack.pop_back();
        pDirector->popScene();
    }
}

void SceneManager::pushViewController(const ViewController::Ptr& controller, bool withAnimation/* = false*/)
{
    _pNextController = controller;
    cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
        cocos2d::Scene* pScene = cocos2d::Scene::create();
        pScene->addChild(_pNextController->getView());
        auto pDirector = cocos2d::Director::getInstance();
        if(!pDirector->getRunningScene())
        {
            _controllerStack.push_back(_pNextController);
            pDirector->runWithScene(pScene);
        }
        else
        {
            auto pLast = _controllerStack.at(_controllerStack.size() - 1);
            pLast->pause();
            _controllerStack.push_back(_pNextController);
            pDirector->pushScene(pScene);
        }
        _pNextController->start();
        _pNextController = nullptr;
    }, this, 0, 0, 0, false, KEY_PUSH_VIEW_CONTROLLER);
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
    cocos2d::Scene* pScene = cocos2d::Scene::create();
    pScene->addChild(controller->getView());
    auto pLast = _controllerStack.at(_controllerStack.size() - 1);
    pLast->stop();
    _controllerStack.pop_back();
    _controllerStack.push_back(controller);
    cocos2d::Director::getInstance()->replaceScene(pScene);
    controller->start();
}
