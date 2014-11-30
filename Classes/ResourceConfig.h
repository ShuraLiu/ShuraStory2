//
//  ResourceConfig.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/27.
//
//

#ifndef __ShuraStory__ResourceConfig__
#define __ShuraStory__ResourceConfig__

#include <string>
#include <map>
#include <vector>

class ResourceConfig
{
    constexpr static const char* GROUP_TYPE = "Group";
    constexpr static const char* GROUP_ID = "id";
    
    typedef std::map<std::string, std::string> Attributes;
    typedef std::vector<Attributes> ResourceArray;
    typedef std::map<std::string, ResourceArray> ResourceTypeArrayMap;
    typedef std::map<std::string, ResourceTypeArrayMap> ResourceGroupMap;
    
public:
    void loadConfig(const std::string& config);
    void dump();
    
public:
    virtual ~ResourceConfig();
    
private:
    ResourceConfig();
    ResourceConfig(const ResourceConfig&) = delete;
    ResourceConfig& operator=(const ResourceConfig&) = delete;
    
public:
    static ResourceConfig& getInstance()
    {
        static ResourceConfig config;
        return config;
    }
    
private:
    ResourceGroupMap _resource;
};

#endif /* defined(__ShuraStory__ResourceConfig__) */
