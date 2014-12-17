//
//  LoadingLayerController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#ifndef __ShuraStory__LoadingLayerController__
#define __ShuraStory__LoadingLayerController__

#include "ViewController.h"

class LoadingLayerController
: public ViewController
{
public:
    constexpr static const ViewControllerType TYPE = ViewControllerType::LoadingViewController;
    LoadingLayerController();
    typedef std::shared_ptr<LoadingLayerController> Ptr;
    
    virtual const ViewControllerType getType() const override {return ViewControllerType::LoadingViewController;};
    virtual cocos2d::Node* getView() override;

    virtual void onStart() override;
};


#endif /* defined(__ShuraStory__LoadingLayerController__) */
