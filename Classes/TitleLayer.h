//
//  TitleLayer.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/17.
//
//

#ifndef __ShuraStory__TitleLayer__
#define __ShuraStory__TitleLayer__

#include "BaseView.h"

class TitleLayer : public BaseView
{
public:
    TitleLayer();
    virtual ~TitleLayer();
    CREATE_FUNC(TitleLayer);
    
    bool init() override;
    
private:
    cocos2d::Node* _pNodeCCS;
};

#endif /* defined(__ShuraStory__TitleLayer__) */
