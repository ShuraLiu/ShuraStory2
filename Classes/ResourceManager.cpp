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

void ResourceManager::load(const std::string &group)
{
    std::vector<std::string> groups;
    groups.push_back(group);
    load(groups);
}

void ResourceManager::cacheTexture(const std::string &groupID, const std::string &fileName, cocos2d::Texture2D *tex)
{
    auto pInfo = getCacheInfo(groupID);
    pInfo->textureCache[fileName] = tex;
    tex->retain();
}

void ResourceManager::cacheFontAtlas(const std::string &groupID, const std::string &fileName, cocos2d::FontAtlas *atlas)
{
    auto pInfo = getCacheInfo(groupID);
    pInfo->fontAtlasCache[fileName] = atlas;
    atlas->retain();
}

void ResourceManager::cacheSpriteFrame(const std::string &groupID, const std::string &name)
{
    auto pInfo = getCacheInfo(groupID);
    pInfo->spriteFrameCache.push_back(name);
    auto iter = _spriteFrameReferenceMap.find(name);
    if (iter == _spriteFrameReferenceMap.end())
    {
        _spriteFrameReferenceMap[name] = 1;
    }
    else
    {
        ++_spriteFrameReferenceMap[name];
    }
}

void ResourceManager::release(const std::string &groupID)
{
    auto iter = _cache.find(groupID);
    if (iter != _cache.end())
    {
        auto pInfo = (*iter).second;
        auto& textureCache = pInfo->textureCache;
        auto texIter = textureCache.begin();
        auto texEnd = textureCache.end();
        while (texIter != texEnd)
        {
            (*texIter).second->release();
            textureCache.erase(texIter);
        }
        auto& fontAtlasCache = pInfo->fontAtlasCache;
        auto fontIter = fontAtlasCache.begin();
        auto fontEnd = fontAtlasCache.end();
        while (fontIter != fontEnd)
        {
            (*fontIter).second->release();
            fontAtlasCache.erase(fontIter);
        }
        auto& spriteFrameCache = pInfo->spriteFrameCache;
        for (auto& spriteFrame : spriteFrameCache)
        {
            --_spriteFrameReferenceMap[spriteFrame];
            if (_spriteFrameReferenceMap[spriteFrame] == 0)
            {
                cocos2d::SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(spriteFrame);
            }
        }
        delete (*iter).second;
        _cache.erase(iter);
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

auto ResourceManager::getCacheInfo(const std::string &groupID) -> CacheInfo*
{
    auto iter = _cache.find(groupID);
    if (iter == _cache.end())
    {
        _cache[groupID] = new CacheInfo();
    }
    return _cache[groupID];
}