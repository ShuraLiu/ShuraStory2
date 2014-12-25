//
//  ResourcePreloadManager.cpp
//  XXLegend
//
//  Created by 刘 潇逸 on 14-12-19.
//
//

#include "ResourcePreloadManager.h"
#include "ResourcePreloadWorker.h"
#include "CustomEvent.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "ResourceConfig.h"

USING_NS_CC;

ResourcePreloadManager::ResourcePreloadManager()
: _pResourcePreloadWorker(nullptr)
{
    ResourceConfig::getInstance().loadConfig("ResourceConfig.xml");
}

ResourcePreloadManager::~ResourcePreloadManager()
{
    CC_SAFE_DELETE(_pResourcePreloadWorker);
}

Texture2D::PixelFormat ResourcePreloadManager::getTextureFormat(const char *format)
{
    if (0 == std::strcmp(format, "RGBA4444"))
    {
        return Texture2D::PixelFormat::RGBA4444;
    }
    else if (0 == std::strcmp(format, "RGBA8888"))
    {
        return Texture2D::PixelFormat::RGBA8888;
    }
    return Texture2D::PixelFormat::DEFAULT;
}

int ResourcePreloadManager::startLoadResource(const std::string& groupID)
{
    std::vector<std::string> groupIDs;
    groupIDs.push_back(groupID);
    return startLoadResource(groupIDs);
}

int ResourcePreloadManager::startLoadResource(const std::vector<std::string>& groupIDs)
{
    _pResourcePreloadWorker = new ResourcePreloadWorker(CC_CALLBACK_1(ResourcePreloadManager::onResourceLoadStarted, this), CC_CALLBACK_1(ResourcePreloadManager::onResourceLoadFinished, this), std::bind(&ResourcePreloadManager::onResourceLoadCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6));
    return _pResourcePreloadWorker->startLoad(groupIDs);
}

bool ResourcePreloadManager::releaseResource(const std::string& groupID)
{
    std::vector<std::string> groupIDs;
    groupIDs.push_back(groupID);
    return releaseResource(groupIDs);
}

bool ResourcePreloadManager::releaseResource(const std::vector<std::string>& groupIDs)
{
    for (auto& groupID : groupIDs)
    {
        if (_caches.find(groupID) == _caches.end())
        {
            return false;
        }
    }
    
    for (auto& groupID : groupIDs)
    {
        auto iter = _caches.find(groupID);
        auto pInfo = iter->second;
        if (!pInfo->spriteFrameCache.empty())
        {
            for (auto& spriteFrame : pInfo->spriteFrameCache)
            {
                --_spriteFrameRefMap[spriteFrame];
                if (_spriteFrameRefMap[spriteFrame] == 0)
                {
                    auto it = _spriteFrameRefMap.find(spriteFrame);
                    _spriteFrameRefMap.erase(it);
                    cocos2d::SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(spriteFrame);
                }
            }
        }
        if (!pInfo->armatureCache.empty())
        {
            for (auto& armature : pInfo->armatureCache)
            {
                --_armatureRefMap[armature];
                if (_armatureRefMap[armature] == 0)
                {
                    auto it = _armatureRefMap.find(armature);
                    _armatureRefMap.erase(it);
                    cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo(armature);
                }
            }
        }
        if (!pInfo->textureCache.empty())
        {
            for (auto pTexture : pInfo->textureCache)
            {
                pTexture->release();
            }
        }
        delete pInfo;
        _caches.erase(iter);
    }
    
    cocos2d::Director::getInstance()->getTextureCache()->removeUnusedTextures();
    
    return true;
}

void ResourcePreloadManager::onResourceLoadStarted(int taskID)
{
    custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadStart> event(taskID);
    custom_event::dispatch(event);
}

void ResourcePreloadManager::onResourceLoadFinished(int taskID)
{
    custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadEnd> event(taskID);
    custom_event::dispatch(event);
    CC_SAFE_DELETE(_pResourcePreloadWorker);
}

void ResourcePreloadManager::onResourceLoadCallback(int taskID, std::string groupID, std::string typeID, std::string fileName, int curCount, int totalCount)
{
    GroupCache* pCache = nullptr;
    auto iter = _caches.find(groupID);
    if (iter == _caches.end())
    {
        pCache = new GroupCache();
        _caches[groupID] = pCache;
    }
    else
    {
        pCache = iter->second;
    }
    if (0 == std::strcmp("Texture", typeID.c_str()))
    {
        auto pTex = cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(fileName);
        pTex->retain();
        pCache->textureCache.push_back(pTex);
    }
    else if (0 == std::strcmp("SpriteFrame", typeID.c_str()))
    {
        pCache->spriteFrameCache.push_back(fileName);
        auto iter = _spriteFrameRefMap.find(fileName);
        if (iter == _spriteFrameRefMap.end())
        {
            _spriteFrameRefMap[fileName] = 1;
        }
        else
        {
            ++_spriteFrameRefMap[fileName];
        }
    }
    else if (0 == std::strcmp("Armature", typeID.c_str()))
    {
        pCache->armatureCache.push_back(fileName);
        auto iter = _armatureRefMap.find(fileName);
        if (iter == _armatureRefMap.end())
        {
            _armatureRefMap[fileName] = 1;
        }
        else
        {
            ++_armatureRefMap[fileName];
        }
    }
    custom_event::ResourcePreloadEvent<custom_event::IDResourcePreloadEvent::PreloadProgress> event(taskID, curCount, totalCount);
    custom_event::dispatch(event);
}
