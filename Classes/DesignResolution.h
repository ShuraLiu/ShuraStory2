//
//  DesignResolution.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__DesignResolution__
#define __ShuraStory__DesignResolution__

class DesignResolution
{
public:
    static DesignResolution& getInstance()
    {
        static DesignResolution instance;
        return instance;
    }
    
    virtual ~DesignResolution() = default;
    
    void initResolution();
    const float getScale() const;
    
private:
    DesignResolution();
    DesignResolution(const DesignResolution&) = delete;
    DesignResolution& operator=(const DesignResolution&) = delete;
    
private:
    float _scale;
};

#endif /* defined(__ShuraStory__DesignResolution__) */
