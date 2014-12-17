//
//  TitleLayerController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/18.
//
//

#ifndef __ShuraStory__TitleLayerController__
#define __ShuraStory__TitleLayerController__

#include "ViewController.h"

class TitleLayerController
: public ViewController
{
public:
    constexpr static const ViewControllerType TYPE = ViewControllerType::TitleViewController;
    TitleLayerController();
    virtual ~TitleLayerController();
    typedef std::shared_ptr<TitleLayerController> Ptr;
    
    virtual const ViewControllerType getType() const override {return ViewControllerType::TitleViewController;};
    virtual cocos2d::Node* getView() override;
    
    virtual void onStart() override;
    
private:
    std::vector<cocos2d::EventListener*> _listeners;
};

#endif /* defined(__ShuraStory__TitleLayerController__) */
