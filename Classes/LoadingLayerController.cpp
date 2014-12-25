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
#include "ResourcePreloadManager.h"
#include "SceneManager.h"

LoadingLayerController::LoadingLayerController()
{
    auto pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto pListener = pDispatcher->addCustomEventListener(custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadStart>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadStart>* pData = (decltype(pData)) event->getUserData();
    });
    pListener->retain();
    _listeners.push_back(pListener);
    
    pListener = pDispatcher->addCustomEventListener(custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadProgress>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadProgress>* pData = (decltype(pData)) event->getUserData();
    });
    pListener->retain();
    _listeners.push_back(pListener);
    
    pListener = pDispatcher->addCustomEventListener(custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadEnd>::NAME, [](cocos2d::EventCustom* event){
        custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadEnd>* pData = (decltype(pData)) event->getUserData();
        
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
    ResourcePreloadManager::getInstance().startLoadResource("GroupTitle");
}