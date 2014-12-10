//
//  HomeLayer.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#ifndef __ShuraStory__HomeLayer__
#define __ShuraStory__HomeLayer__

#include "BaseView.h"

class HomeLayerUIEventDelegate
{
public:
    virtual ~HomeLayerUIEventDelegate() = default;
    virtual void onButtonTestPressed() = 0;
};

class HomeLayer : public BaseView
{
public:
    HomeLayer();
    virtual ~HomeLayer();
    CREATE_FUNC(HomeLayer);
    
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
    virtual void addSubView(const ViewController::Ptr& controller, ViewControllerType type);
    void setHomeLayerUIEventDelegate(HomeLayerUIEventDelegate* pDelegate);
    
private:
    cocos2d::Node* _pNodeCCS;
    HomeLayerUIEventDelegate* _pHomeLayerUIEventDelegate;
    
    cocos2d::ui::Button* _pButtonTest;
};

#endif /* defined(__ShuraStory__HomeLayer__) */
