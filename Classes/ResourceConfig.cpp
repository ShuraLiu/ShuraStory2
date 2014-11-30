//
//  ResourceConfig.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/27.
//
//

#include "ResourceConfig.h"
#include <tinyxml2/tinyxml2.h>
#include "cocos2d.h"

using namespace tinyxml2;
USING_NS_CC;

ResourceConfig::ResourceConfig()
{
    
}

ResourceConfig::~ResourceConfig()
{
    
}

void ResourceConfig::loadConfig(const std::string &config)
{
    auto fullPath = FileUtils::getInstance()->fullPathForFilename(config);
    XMLDocument doc;
    auto error = doc.LoadFile(fullPath.c_str());
    if (error != XMLError::XML_NO_ERROR)
    {
        assert(false);
    }
    
    auto element = doc.FirstChildElement(GROUP_TYPE);
    while (element)
    {
        std::string id = element->Attribute(GROUP_ID);
        if (!element->NoChildren())
        {
            auto info = element->FirstChildElement();
            while (info)
            {
                auto infoName = info->Name();
                auto attribute = info->FirstAttribute();
                if (attribute)
                {
                    Attributes attr;
                    while (attribute)
                    {
                        attr[attribute->Name()] = attribute->Value();
                        attribute = attribute->Next();
                    }
                    _resource[id][infoName].push_back(attr);
                }
                info = info->NextSiblingElement();
            }
        }
        element = element->NextSiblingElement();
    }
}

void ResourceConfig::dump()
{
    if (_resource.empty())
    {
        CCLOG("resource empty");
    }
    else
    {
        CCLOG("----dump resource info----");
        for (auto& kv : _resource)
        {
            CCLOG("[%s]", kv.first.c_str());
            for (auto& subkv : kv.second)
            {
                CCLOG("[%s]", subkv.first.c_str());
                for (auto& info : subkv.second)
                {
                    for (auto& value : info)
                    {
                        CCLOG("[%s][%s]", value.first.c_str(), value.second.c_str());
                    }
                }
            }
        }
    }
}