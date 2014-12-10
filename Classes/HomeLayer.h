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

class HomeLayer : public BaseView
{
public:
    HomeLayer();
    virtual ~HomeLayer();
    CREATE_FUNC(HomeLayer);
    
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
    virtual void addSubView(const ViewController::Ptr& controller);
    
private:
    cocos2d::Node* _pNodeCCS;
};

#endif /* defined(__ShuraStory__HomeLayer__) */
