//
//  LoadingLayer.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#ifndef __ShuraStory__LoadingLayer__
#define __ShuraStory__LoadingLayer__

#include "BaseView.h"

class LoadingLayer : public BaseView
{
public:
    LoadingLayer();
    virtual ~LoadingLayer();
    CREATE_FUNC(LoadingLayer);
    
    bool init() override;
    
private:
    cocos2d::Node* _pNodeCCS;
};

#endif /* defined(__ShuraStory__LoadingLayer__) */
