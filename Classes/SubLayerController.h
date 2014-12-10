//
//  SubLayerController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#ifndef __ShuraStory__SubLayerController__
#define __ShuraStory__SubLayerController__

#include "ViewController.h"

class SubLayerController : public ViewController
{
public:
    constexpr static const ViewControllerType TYPE = ViewControllerType::SubViewController;
    typedef std::shared_ptr<SubLayerController> Ptr;
    
    virtual cocos2d::Node* createView() override;
};


#endif /* defined(__ShuraStory__SubLayerController__) */
