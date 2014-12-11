//
//  BaseView.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#ifndef __ShuraStory__BaseView__
#define __ShuraStory__BaseView__

#include "cocos2d.h"
#include <cocos/ui/CocosGUI.h>
#include "ViewController.h"

class BaseViewProtocol
{
public:
    virtual ~BaseViewProtocol() = default;
    virtual void addSubView(const ViewController::Ptr& controller, ViewControllerType type) = 0;
    virtual void removeSubView(const ViewController::Ptr& controller, ViewControllerType type) = 0;
};

class BaseView
: public cocos2d::ui::Widget
, public BaseViewProtocol
{
public:
    BaseView();
    virtual ~BaseView() = default;
    virtual void addSubView(const ViewController::Ptr& controller, ViewControllerType type){};
    virtual void removeSubView(const ViewController::Ptr& controller, ViewControllerType type){};
};

#endif /* defined(__ShuraStory__BaseView__) */
