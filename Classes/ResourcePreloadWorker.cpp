//
//  ResourcePreloadWorker.cpp
//  XXLegend
//
//  Created by 刘 潇逸 on 14-12-19.
//
//

#include "ResourcePreloadWorker.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "ResourcePreloadManager.h"
#include "ResourceConfig.h"

const char* KEY_LOAD_OTHERS = "key_load_others";
const char* KEY_DELAY_NOTIFY_END = "key_delay_notify_end";
const char* KEY_START_LOAD = "key_start_load";

int ResourcePreloadWorker::s_resoucre_preload_id = 0;

ResourcePreloadWorker::ResourcePreloadWorker(const LoadStateCallback& loadStartCallback, const LoadStateCallback& loadEndCallback, const LoadProgressCallback& loadProgressCallback)
: _loadStartCallback(loadStartCallback)
, _loadEndCallback(loadEndCallback)
, _loadPorgressCallback(loadProgressCallback)
, _totalResourceCount(0)
, _loadedResoureCount(0)
, _textureProgress(0)
, _spriteFrameProgress(0)
, _armatureProgress(0)
, _taskID(-1)
{
    
}

ResourcePreloadWorker::~ResourcePreloadWorker()
{
    cocos2d::Director::getInstance()->getScheduler()->unschedule(KEY_DELAY_NOTIFY_END, this);
    cocos2d::Director::getInstance()->getScheduler()->unschedule(KEY_LOAD_OTHERS, this);
    cocos2d::Director::getInstance()->getScheduler()->unschedule(KEY_START_LOAD, this);
    
    if (!_resourceInfoCache.empty())
    {
        for (auto& cache : _resourceInfoCache)
        {
            auto& array = cache.second;
            for (auto& pInfo : array)
            {
                delete pInfo;
            }
        }
    }
}

int ResourcePreloadWorker::startLoad(const std::string &groupID)
{
    std::vector<std::string> groups;
    groups.push_back(groupID);
    return startLoad(groups);
}

int ResourcePreloadWorker::startLoad(const std::vector<std::string> &groupIDs)
{
    s_resoucre_preload_id++;
    _taskID = s_resoucre_preload_id;
    
    prepareResourceInfos(groupIDs);
    
    cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
        this->notifyStart();
        if (_resourceInfoCache.find("Texture") != _resourceInfoCache.end())
        {
            loadTextures();
        }
        else
        {
            loadOthers();
        }
    }, this, 0, 0, 0, 0, KEY_START_LOAD);
    return _taskID;
}

void ResourcePreloadWorker::prepareResourceInfos(const std::vector<std::string> &groupIDs)
{
    auto& config = ResourceConfig::getInstance();
    
    const char* const TYPES[] = {
        "Texture",
        "SpriteFrame",
        "Armature",
    };
    
    int count = sizeof(TYPES)/sizeof(TYPES[0]);
    
    
    for (auto& groupID : groupIDs)
    {
        auto resourceTypeArrayMap = config.getGroup(groupID);
        auto pInfo = resourceTypeArrayMap.find(TYPES[0]);
        if (pInfo != resourceTypeArrayMap.end() && !pInfo->second.empty())
        {
            auto begin = pInfo->second.begin();
            auto end = pInfo->second.end();
            auto iter = begin;
            while(iter != end)
            {
                TextureInfo* pTextureInfo = new TextureInfo();
                pTextureInfo->groupID = groupID;
                pTextureInfo->typeID = "Texture";
                pTextureInfo->fileName = (*iter)["file_name"];
                pTextureInfo->pixelFormat = (*iter)["pixel_format"];
                _resourceInfoCache["Texture"].push_back(pTextureInfo);
                ++_totalResourceCount;
                ++iter;
            }
        }
        for (int i = 1; i < count; ++i)
        {
            auto pInfo = resourceTypeArrayMap.find(TYPES[i]);
            if (pInfo != resourceTypeArrayMap.end() && !pInfo->second.empty())
            {
                auto begin = pInfo->second.begin();
                auto end = pInfo->second.end();
                auto iter = begin;
                while(iter != end)
                {
                    ResourceInfo* pResourceInfo = new ResourceInfo();
                    pResourceInfo->groupID = groupID;
                    pResourceInfo->typeID = TYPES[i];
                    pResourceInfo->fileName = (*iter)["file_name"];
                    _resourceInfoCache[TYPES[i]].push_back(pResourceInfo);
                    ++_totalResourceCount;
                    ++iter;
                }
            }
        }
    }
}

void ResourcePreloadWorker::loadTextures()
{
    if (_textureProgress < _resourceInfoCache["Texture"].size())
    {
        auto pTextureInfo = dynamic_cast<TextureInfo*>(_resourceInfoCache["Texture"].at(_textureProgress));
        cocos2d::Texture2D::PixelFormat pixelFormat = ResourcePreloadManager::getInstance().getTextureFormat(pTextureInfo->pixelFormat.c_str());
        cocos2d::Texture2D::setDefaultAlphaPixelFormat(pixelFormat);
        cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(pTextureInfo->fileName, CC_CALLBACK_1(ResourcePreloadWorker::asyncTextureLoadCallback, this));
    }
    else
    {
        loadOthers();
    }
}

void ResourcePreloadWorker::asyncTextureLoadCallback(cocos2d::Texture2D *tex)
{
    ++_textureProgress;
    ++_loadedResoureCount;
    auto& textures = _resourceInfoCache["Texture"];
    for (auto& pInfo : textures)
    {
        if (tex == cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(pInfo->fileName))
        {
            this->notifyProgress(pInfo->groupID, "Texture", pInfo->fileName);
        }
    }
    
    loadTextures();
}

void ResourcePreloadWorker::loadOthers()
{
    cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
        auto end = _resourceInfoCache.end();
        auto iterSpriteFrame = _resourceInfoCache.find("SpriteFrame");
        auto iterArmature = _resourceInfoCache.find("Armature");
        
        if (iterSpriteFrame != end && (*iterSpriteFrame).second.size() > _spriteFrameProgress)
        {
            auto pInfos = (*iterSpriteFrame).second;
            auto pInfo = pInfos.at(_spriteFrameProgress);
            const std::string& fullPathName = cocos2d::FileUtils::getInstance()->fullPathForFilename(pInfo->fileName);
            cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fullPathName);
            ++_spriteFrameProgress;
            ++_loadedResoureCount;
            this->notifyProgress(pInfo->groupID, "SpriteFrame", fullPathName);
        }
        else
        {
            cocos2d::Director::getInstance()->getScheduler()->unschedule(KEY_LOAD_OTHERS, this);
            if (iterArmature != end && !(*iterArmature).second.empty())
            {
                auto& array = (*iterArmature).second;
                for (int i = 0; i < array.size(); ++i)
                {
                    _unloadedArmatures.push_back(array.at(i));
                }
                for (auto& pInfo : array)
                {
                    cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(pInfo->fileName, this, schedule_selector(ResourcePreloadWorker::asyncArmatureAnimationLoadCallback));
                }
            }
            else
            {
                this->notifyEnd();
            }
        }
    }, this, 0, kRepeatForever, 0, 0, KEY_LOAD_OTHERS);
}

void ResourcePreloadWorker::asyncArmatureAnimationLoadCallback(float dt)
{
    auto begin = _unloadedArmatures.begin();
    auto end = _unloadedArmatures.end();
    auto iter = begin;
    while (iter != end)
    {
        auto pArmatureInfo = (*iter);
        auto first = pArmatureInfo->fileName.find_first_of(".");
        std::string fileName;
        if(first != std::string::npos)
        {
            fileName = pArmatureInfo->fileName.substr(0, first);
        }
        auto pRef = cocostudio::ArmatureDataManager::getInstance()->getArmatureData(fileName);
        if (pRef)
        {
            ++_armatureProgress;
            ++_loadedResoureCount;
            this->notifyProgress(pArmatureInfo->groupID, "Armature", pArmatureInfo->fileName);
            _unloadedArmatures.erase(iter);
            break;
        }
        else
        {
            ++iter;
        }
    }
    if (_unloadedArmatures.empty())
    {
        cocos2d::Director::getInstance()->getScheduler()->schedule([this](float dt){
            this->notifyEnd();
        }, this, 0, 0, 0, 0, KEY_DELAY_NOTIFY_END);
    }
}

void ResourcePreloadWorker::notifyStart()
{
    if (_loadStartCallback)
    {
        _loadStartCallback(_taskID);
    }
}

void ResourcePreloadWorker::notifyEnd()
{
    if (_loadEndCallback)
    {
        _loadEndCallback(_taskID);
    }
}

void ResourcePreloadWorker::notifyProgress(const std::string& groupID, const std::string& typeID, const std::string& fileName)
{
    if (_loadPorgressCallback)
    {
        _loadPorgressCallback(_taskID, groupID, typeID, fileName, _loadedResoureCount, _totalResourceCount);
    }
}