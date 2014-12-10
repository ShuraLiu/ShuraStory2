//
//  HomeLayerController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#ifndef __ShuraStory__HomeLayerController__
#define __ShuraStory__HomeLayerController__

#include "ViewController.h"

class HomeLayerController : public ViewController
{
public:
    typedef std::shared_ptr<HomeLayerController> Ptr;
    
    virtual cocos2d::Node* createView() override;
    virtual void onStart() override;
};

#endif /* defined(__ShuraStory__HomeLayerController__) */
