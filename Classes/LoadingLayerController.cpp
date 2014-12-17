//
//  LoadingLayerController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#include "LoadingLayerController.h"
#include "TitleLayerController.h"
#include "LoadingLayer.h"
#include "ResourceManager.h"
#include "SceneManager.h"

LoadingLayerController::LoadingLayerController()
{
    auto pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto pListener = pDispatcher->addCustomEventListener(custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Start>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Start>* pData = (decltype(pData)) event->getUserData();
    });
    pListener->retain();
    _listeners.push_back(pListener);
    
    pListener = pDispatcher->addCustomEventListener(custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Progress>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Progress>* pData = (decltype(pData)) event->getUserData();
    });
    pListener->retain();
    _listeners.push_back(pListener);
    
    pListener = pDispatcher->addCustomEventListener(custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::End>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::End>* pData = (decltype(pData)) event->getUserData();
        TitleLayerController::Ptr pController(new TitleLayerController());
        SceneManager::getInstance().pushViewController(pController);
    });
    pListener->retain();
    _listeners.push_back(pListener);
}

LoadingLayerController::~LoadingLayerController()
{
    CC_SAFE_RELEASE_NULL(_pNode);
}

cocos2d::Node* LoadingLayerController::getView()
{
    if (!_pNode)
    {
        auto pLayer = LoadingLayer::create();
        _pNode = pLayer;
        _pNode->retain();
    }
    return _pNode;
}

void LoadingLayerController::onStart()
{
    CCLOG("[LoadingLayerController][onStart]");
    ResourceManager::getInstance().load("GroupTitle");
}