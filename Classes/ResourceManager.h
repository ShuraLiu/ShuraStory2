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

class ResourceManager
{
public:
    CC_DISALLOW_COPY_AND_ASSIGN(ResourceManager)
    virtual ~ResourceManager();
    
    static ResourceManager& getInstance()
    {
        static ResourceManager manager;
        return manager;
    }
    
private:
    ResourceManager();
};

#endif /* defined(__ShuraStory__ResourceManager__) */
