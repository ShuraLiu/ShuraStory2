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
#include "SubLayerController.h"

class HomeLayerController
: public ViewController
, public HomeLayerUIEventDelegate
{
public:
    constexpr static const ViewControllerType TYPE = ViewControllerType::HomeViewController;
    HomeLayerController();
    typedef std::shared_ptr<HomeLayerController> Ptr;
    
    virtual const ViewControllerType getType() const override {return ViewControllerType::HomeViewController;};
    virtual cocos2d::Node* getView() override;
    
    virtual void onStart() override;
    
    virtual void onButtonTestPressed() override;
    virtual void onButtonTest2Pressed() override;
    
private:
    SubLayerController::Ptr _pSubLayerController;
};

#endif /* defined(__ShuraStory__HomeLayerController__) */
