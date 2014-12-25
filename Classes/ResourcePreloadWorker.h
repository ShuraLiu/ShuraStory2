//
//  ResourcePreloadWorker.h
//  XXLegend
//
//  Created by 刘 潇逸 on 14-12-19.
//
//

#ifndef __XXLegend__ResourcePreloadWorker__
#define __XXLegend__ResourcePreloadWorker__

#include <string>
#include <map>
#include <vector>
#include <functional>
#include "cocos2d.h"

class ResourcePreloadWorker : public cocos2d::Ref
{
    static int s_resoucre_preload_id;
    struct ResourceInfo
    {
        std::string groupID;
        std::string typeID;
        std::string fileName;
        
        virtual ~ResourceInfo() = default;
    };
    
    struct TextureInfo : public ResourceInfo
    {
        std::string pixelFormat;
    };
    
public:
    typedef std::function<void(int)> LoadStateCallback;
    typedef std::function<void(int, std::string groupID, std::string typeID, std::string fileName, int, int)> LoadProgressCallback;
    
public:
    explicit ResourcePreloadWorker(const LoadStateCallback& loadStartCallback, const LoadStateCallback& loadEndCallback, const LoadProgressCallback& loadProgressCallback);
    ~ResourcePreloadWorker();
    
    int startLoad(const std::vector<std::string>& groupIDs);
    int startLoad(const std::string& groupID);
    
private:
    void prepareResourceInfos(const std::vector<std::string>& groupIDs);
    void loadTextures();
    void asyncTextureLoadCallback(cocos2d::Texture2D* tex);
    void loadOthers();
    void asyncArmatureAnimationLoadCallback(float dt);
    void notifyStart();
    void notifyEnd();
    void notifyProgress(const std::string& groupID, const std::string& typeID, const std::string& fileName);
    
private:
    int _taskID;
    std::map<std::string, std::vector<ResourceInfo*>> _resourceInfoCache;
    LoadStateCallback _loadStartCallback;
    LoadStateCallback _loadEndCallback;
    LoadProgressCallback _loadPorgressCallback;
    std::vector<ResourceInfo*> _unloadedArmatures;
    size_t _totalResourceCount;
    size_t _loadedResoureCount;
    size_t _textureProgress;
    size_t _spriteFrameProgress;
    size_t _armatureProgress;
};

#endif /* defined(__XXLegend__ResourcePreloadWorker__) */
