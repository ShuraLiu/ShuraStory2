//
//  ResourceLoader.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/30.
//
//

#include "ResourceLoader.h"
#include "ResourceConfig.h"
#include "ResourceManager.h"
#include "2d/CCFontAtlasCache.h"

const char* TYPE_TEXTURE = "Texture";
const char* TYPE_SPRITEFRAME = "SpriteFrame";
const char* TYPE_BITMAP_FONT = "BitmapFont";

const char* LOAD_RESOURCE = "load_resource";

ResourceLoader::ResourceLoader(const std::vector<std::string>& groups, const ResourceLoadProgressCallback& callback, const ResourceLoadStateCallback& startCallback, const ResourceLoadStateCallback endCallback)
: _textureLoadProgress(0)
, _spriteLoadProgress(0)
, _bitmapFontLoadProgress(0)
, _curResourceCount(0)
, _totalResourceCount(0)
, _callback(callback)
, _startCallback(startCallback)
, _endCallback(endCallback)
{
    auto& config = ResourceConfig::getInstance();
    for (auto& group : groups)
    {
        auto resource = config.getGroup(group);
        for (auto& kv : resource)
        {
            auto type = kv.first;
            if (std::strcmp(type.c_str(), TYPE_TEXTURE))
            {
                auto& textures = kv.second;
                for (auto& texture : textures)
                {
                    TextureInfo info;
                    info.fileName = texture["file_name"];
                    info.format = translateTextureFormat(texture["pixel_format"]);
                    info.groupID = group;
                    _arrayTextures.push_back(info);
                }
            }
            else if (std::strcmp(type.c_str(), TYPE_SPRITEFRAME))
            {
                auto& spriteFrames = kv.second;
                for (auto& spriteFrame : spriteFrames)
                {
                    SpriteFrameInfo info;
                    info.fileName = spriteFrame["file_name"];
                    info.groupID = group;
                    _arraySpriteFrames.push_back(info);
                }
            }
            else if (std::strcmp(type.c_str(), TYPE_BITMAP_FONT))
            {
                auto& bitmapFonts = kv.second;
                for (auto& bitmapFont : bitmapFonts)
                {
                    BitmapFontInfo info;
                    info.fileName = bitmapFont["file_name"];
                    info.groupID = group;
                    _arrayBitmapFonts.push_back(info);
                }
            }
        }
    }
    _totalResourceCount = _arrayTextures.size() + _arraySpriteFrames.size() + _arrayBitmapFonts.size();
}

void ResourceLoader::startLoad()
{
    notifyStart();
    if (!_arrayTextures.empty())
    {
        cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(_arrayTextures.at(0).fileName, CC_CALLBACK_1(ResourceLoader::onAsyncTextureLoadCallback, this));
    }
    else
    {
        loadResourceInCocosThread();
    }
}

cocos2d::Texture2D::PixelFormat ResourceLoader::translateTextureFormat(const std::string &format)
{
    if (std::strcmp(format.c_str(), "RGBA8888"))
    {
        return cocos2d::Texture2D::PixelFormat::RGBA8888;
    }
    else if (std::strcmp(format.c_str(), "RGBA4444"))
    {
        return cocos2d::Texture2D::PixelFormat::RGBA4444;
    }
    return cocos2d::Texture2D::PixelFormat::RGBA8888;
}

void ResourceLoader::onAsyncTextureLoadCallback(cocos2d::Texture2D* tex)
{
    auto& textureInfo = _arrayTextures.at(_textureLoadProgress);
    ResourceManager::getInstance().cacheTexture(textureInfo.groupID, textureInfo.fileName, tex);
    ++_textureLoadProgress;
    ++_curResourceCount;
    notifyProgress();
    if (_textureLoadProgress == _arrayTextures.size())
    {
        loadResourceInCocosThread();
    }
}

void ResourceLoader::loadResourceInCocosThread()
{
    cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ResourceLoader::loadResourcePerFrame, this), this, 0, kRepeatForever, 0, false, LOAD_RESOURCE);
}

void ResourceLoader::loadResourcePerFrame(float dt)
{
    if (!_arraySpriteFrames.empty() && _spriteLoadProgress != _arraySpriteFrames.size())
    {
        auto& spriteFrameInfo = _arraySpriteFrames.at(_spriteLoadProgress);
        const std::string& fullPathName = cocos2d::FileUtils::getInstance()->fullPathForFilename(spriteFrameInfo.fileName);
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fullPathName);
        ResourceManager::getInstance().cacheSpriteFrame(spriteFrameInfo.groupID, fullPathName);
        ++_spriteLoadProgress;
        ++_curResourceCount;
        notifyProgress();
    }
    else if (!_arrayBitmapFonts.empty() && _bitmapFontLoadProgress != _arrayBitmapFonts.size())
    {
        auto& bitmapFontInfo = _arrayBitmapFonts.at(_bitmapFontLoadProgress);
        auto fnt = cocos2d::FontAtlasCache::getFontAtlasFNT(bitmapFontInfo.fileName);
        ResourceManager::getInstance().cacheFontAtlas(bitmapFontInfo.groupID, bitmapFontInfo.fileName, fnt);
        ++_bitmapFontLoadProgress;
        ++_curResourceCount;
        notifyProgress();
    }
    else
    {
        notifyEnd();
    }
}

void ResourceLoader::notifyProgress()
{
    if (_callback)
    {
        _callback(_curResourceCount, _totalResourceCount);
    }
}

void ResourceLoader::notifyStart()
{
    if (_startCallback)
    {
        _startCallback();
    }
}

void ResourceLoader::notifyEnd()
{
    if (_endCallback)
    {
        _endCallback();
    }
}