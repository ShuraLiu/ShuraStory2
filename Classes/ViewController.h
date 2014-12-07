//
//  ViewController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__ViewController__
#define __ShuraStory__ViewController__

#include "cocos2d.h"
#include "LifeCircle.h"

class ViewController : public LifeCircle
{
public:
    typedef std::shared_ptr<ViewController> Ptr;
    
    
    ViewController() = default;
    virtual ~ViewController() = default;
    
    virtual cocos2d::Node* createView() = 0;
};

#endif /* defined(__ShuraStory__ViewController__) */
