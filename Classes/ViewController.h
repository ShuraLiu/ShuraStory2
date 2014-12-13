//
//  ViewController.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#ifndef __ShuraStory__ViewController__
#define __ShuraStory__ViewController__

#include "cocos2d.h"
#include "LifeCircle.h"
#include "ViewControllerType.h"

class BaseView;

class ViewController : public LifeCircle
{
public:
    typedef std::shared_ptr<ViewController> Ptr;
    
    ViewController():_pNode(nullptr){}
    virtual ~ViewController() = default;
    
    virtual const ViewControllerType getType() const = 0;
    virtual cocos2d::Node* getView() = 0;
    
protected:
    BaseView* _pNode;
};

#endif /* defined(__ShuraStory__ViewController__) */
