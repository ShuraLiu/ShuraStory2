//
//  ViewController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__ViewController__
#define __ShuraStory__ViewController__

#include <stdio.h>
#include <memory>
#include "cocos2d.h"

class ViewController
{
public:
    typedef std::shared_ptr<ViewController> Ptr;
    
    
    ViewController() = default;
    virtual ~ViewController() = default;
    
    virtual cocos2d::Node* createView() = 0;
};

#endif /* defined(__ShuraStory__ViewController__) */
