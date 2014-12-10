//
//  SubLayer.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#ifndef __ShuraStory__SubLayer__
#define __ShuraStory__SubLayer__

#include "BaseView.h"

class SubLayer : public BaseView
{
public:
    SubLayer();
    virtual ~SubLayer();
    CREATE_FUNC(SubLayer);
    
    bool init() override;
    void onEnter() override;
    void onExit() override;
    
private:
    cocos2d::Node* _pNodeCCS;
};

#endif /* defined(__ShuraStory__SubLayer__) */
