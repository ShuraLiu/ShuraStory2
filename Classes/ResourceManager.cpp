//
//  ResourceManager.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/27.
//
//

#include "ResourceManager.h"
#include "CustomEvent.h"
#include "ResourceLoader.h"

ResourceManager::ResourceManager()
:_pLoader(nullptr)
{
    
}

ResourceManager::~ResourceManager()
{
    
}

void ResourceManager::load(const std::vector<std::string> &groups)
{
    _pLoader = new ResourceLoader(groups, CC_CALLBACK_2(ResourceManager::onLoadProgressCallback, this), CC_CALLBACK_0(ResourceManager::onLoadStartCallback, this), CC_CALLBACK_0(ResourceManager::onLoadEndCallback, this));
    _pLoader->startLoad();
}

void ResourceManager::cacheRef(const std::string &fileName, cocos2d::Ref* ref)
{
    if (_mapRefCache.find(fileName) == _mapRefCache.end())
    {
        _mapRefCache[fileName] = ref;
    }
    ref->retain();
}

void ResourceManager::releaseRef(const std::string &fileName)
{
    auto iter = _mapRefCache.find(fileName);
    if (iter != _mapRefCache.end())
    {
        (*iter).second->release();
    }
}

void ResourceManager::cacheSpriteFrameRef(const std::string &fileName)
{
    if (_spriteFrameRefCache.find(fileName) == _spriteFrameRefCache.end())
    {
        _spriteFrameRefCache[fileName] = 1;
    }
    else
    {
        ++_spriteFrameRefCache[fileName];
    }
}

void ResourceManager::onLoadStartCallback()
{
    custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Start> event;
    custom_event::dispatch(event);
}

void ResourceManager::onLoadEndCallback()
{
    custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::End> event;
    custom_event::dispatch(event);
    
    CC_SAFE_DELETE(_pLoader);
}

void ResourceManager::onLoadProgressCallback(int cur, int total)
{
    custom_event::ResourceLoadProgressEvent<custom_event::IDResourceLoadProgressEvent::Progress> event(cur, total);
    custom_event::dispatch(event);
}