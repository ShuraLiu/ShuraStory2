//
//  HomeSceneController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/8.
//
//

#ifndef __ShuraStory__HomeSceneController__
#define __ShuraStory__HomeSceneController__

#include "ViewController.h"

class HomeSceneController : public ViewController
{
public:
    typedef std::shared_ptr<HomeSceneController> Ptr;
    
    virtual cocos2d::Node* createView() override;
    virtual void onStart() override;
};

#endif /* defined(__ShuraStory__HomeSceneController__) */
