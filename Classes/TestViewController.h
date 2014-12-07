//
//  TestViewController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__TestViewController__
#define __ShuraStory__TestViewController__

#include "ViewController.h"

class TestViewController : public ViewController
{
public:
    typedef std::shared_ptr<TestViewController> Ptr;
    
    virtual cocos2d::Node* createView() override;
    virtual void onStart() override;
};

#endif /* defined(__ShuraStory__TestViewController__) */
