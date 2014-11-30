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
    typedef std::map<std::string, cocos2d::Ref*> RefCacheMap;
    typedef std::map<std::string, int> ResourceRefMap;
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
    void cacheRef(const std::string& fileName, cocos2d::Ref* ref);
    void cacheSpriteFrameRef(const std::string& fileName);
    
private:
    void releaseRef(const std::string& fileName);
    void onLoadStartCallback();
    void onLoadEndCallback();
    void onLoadProgressCallback(int cur, int total);
    
private:
    ResourceManager();
    
private:
    ResourceLoader* _pLoader;
    RefCacheMap _mapRefCache;
    ResourceRefMap _spriteFrameRefCache;
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
