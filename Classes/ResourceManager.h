//
//  ResourceManager.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/27.
//
//

#ifndef __ShuraStory__ResourceManager__
#define __ShuraStory__ResourceManager__

#include "cocos2d.h"

class ResourceLoader;

class ResourceManager
{
    typedef std::map<std::string, int> SpriteFrameReferenceMap;
    struct CacheInfo
    {
        std::map<std::string, cocos2d::Texture2D*> textureCache;
        std::vector<std::string> spriteFrameCache;
        std::map<std::string, cocos2d::FontAtlas*> fontAtlasCache;
    };
    
public:
    CC_DISALLOW_COPY_AND_ASSIGN(ResourceManager)
    virtual ~ResourceManager();
    
    static ResourceManager& getInstance()
    {
        static ResourceManager manager;
        return manager;
    }
    
    void load(const std::vector<std::string>& groups);
    void load(const std::string& group);
    void release(const std::string& groupID);
    void cacheTexture(const std::string& groupID, const std::string& fileName, cocos2d::Texture2D* tex);
    void cacheFontAtlas(const std::string& groupID, const std::string& fileName, cocos2d::FontAtlas* atlas);
    void cacheSpriteFrame(const std::string& groupID, const std::string& name);
    
private:
    void onLoadStartCallback();
    void onLoadEndCallback();
    void onLoadProgressCallback(int cur, int total);
    CacheInfo* getCacheInfo(const std::string& groupID);
    
private:
    ResourceManager();
    
private:
    ResourceLoader* _pLoader;
    std::map<std::string, CacheInfo*> _cache;
    SpriteFrameReferenceMap _spriteFrameReferenceMap;
};

namespace custom_event
{
    enum class IDResourceLoadProgressEvent : int
    {
        Start,
        Progress,
        End,
    };
    
    template<IDResourceLoadProgressEvent _ID>
    struct ResourceLoadProgressEvent
    {
        constexpr static IDResourceLoadProgressEvent ID = _ID;
        constexpr static const char* NAME = "e_resource_load_progress";
    };
    
    template<>
    struct ResourceLoadProgressEvent<IDResourceLoadProgressEvent::Start>
    {
        constexpr static const char* NAME = "e_resource_load_progress_start";
    };
    
    template<>
    struct ResourceLoadProgressEvent<IDResourceLoadProgressEvent::End>
    {
        constexpr static const char* NAME = "e_resource_load_progress_end";
    };
    
    template<>
    struct ResourceLoadProgressEvent<IDResourceLoadProgressEvent::Progress>
    {
        constexpr static const char* NAME = "e_resource_load_progress_progress";
        int loadedResourceCount;
        int totalResourceCount;
        
        explicit ResourceLoadProgressEvent(int loaded, int total): loadedResourceCount(loaded), totalResourceCount(total){}
    };
}

#endif /* defined(__ShuraStory__ResourceManager__) */
