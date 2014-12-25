//
//  ResourcePreloadManager.h
//  XXLegend
//
//  Created by 刘 潇逸 on 14-12-19.
//
//

#ifndef __XXLegend__ResourcePreloadManager__
#define __XXLegend__ResourcePreloadManager__

#include "cocos2d.h"

class ResourcePreloadWorker;

class ResourcePreloadManager
{
    struct GroupCache
    {
        std::vector<cocos2d::Ref*> textureCache;
        std::vector<std::string> spriteFrameCache;
        std::vector<std::string> armatureCache;
    };
    
public:
    cocos2d::Texture2D::PixelFormat getTextureFormat(const char* format);
    
    bool releaseResource(const std::string& groupID);
    bool releaseResource(const std::vector<std::string>& groupIDs);
    
    int startLoadResource(const std::string& groupID);
    int startLoadResource(const std::vector<std::string>& groupIDs);
    
public:
    static ResourcePreloadManager& getInstance()
    {
        static ResourcePreloadManager instance;
        return instance;
    }
    
    ~ResourcePreloadManager();
    
private:
    void onResourceLoadCallback(int taskID, std::string groupID, std::string typeID, std::string fileName, int curCount, int totalCount);
    void onResourceLoadStarted(int taskID);
    void onResourceLoadFinished(int taskID);
    
    ResourcePreloadManager();
    
private:
    ResourcePreloadWorker* _pResourcePreloadWorker;
    std::map<std::string, int> _spriteFrameRefMap;
    std::map<std::string, int> _armatureRefMap;
    std::map<std::string, GroupCache*> _caches;
};

namespace custom_event
{
    enum class IDResourcePreloadEvent : int
    {
        PreloadStart,
        PreloadProgress,
        PreloadEnd,
    };
    
    template<IDResourcePreloadEvent _ID>
    struct ResourcePreloadEvent
    {
        IDResourcePreloadEvent ID = _ID;
        static constexpr const char* const NAME = "e_resource_pre_load";
    };
    
    template<>
    struct ResourcePreloadEvent<IDResourcePreloadEvent::PreloadStart>
    {
        static constexpr const char* const NAME = "e_resource_pre_load_start";
        
        int taskID;
        explicit ResourcePreloadEvent(int id) : taskID(id){}
    };
    
    template<>
    struct ResourcePreloadEvent<IDResourcePreloadEvent::PreloadProgress>
    {
        static constexpr const char* const NAME = "e_resource_pre_load_progress";
        
        int taskID;
        int totalCount;
        int curCount;
        explicit ResourcePreloadEvent(int id, int cur, int total) : taskID(id), curCount(cur), totalCount(total){}
    };
    
    template<>
    struct ResourcePreloadEvent<IDResourcePreloadEvent::PreloadEnd>
    {
        static constexpr const char* const NAME = "e_resource_pre_load_end";
        
        int taskID;
        explicit ResourcePreloadEvent(int id) : taskID(id){}
    };
}

#endif /* defined(__XXLegend__ResourcePreloadManager__) */
