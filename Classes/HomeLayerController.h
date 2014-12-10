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
#include "HomeLayer.h"

class HomeLayerController
: public ViewController
, public HomeLayerUIEventDelegate
{
public:
    constexpr static const ViewControllerType TYPE = ViewControllerType::HomeViewController;
    HomeLayerController();
    typedef std::shared_ptr<HomeLayerController> Ptr;
    
    virtual cocos2d::Node* createView() override;
    virtual void onStart() override;
    
    virtual void onButtonTestPressed() override;
    
private:
    HomeLayer* _pLayer;
};

#endif /* defined(__ShuraStory__HomeLayerController__) */
