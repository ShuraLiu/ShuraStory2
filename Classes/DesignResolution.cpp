//
//  DesignResolution.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#include "DesignResolution.h"
#include "cocos2d.h"

const cocos2d::Size designSize = {960, 640};

DesignResolution::DesignResolution()
: _scale(1)
{
    
}

void DesignResolution::initResolution()
{
    auto pGLView = cocos2d::Director::getInstance()->getOpenGLView();
    pGLView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);
    _scale = pGLView->getScaleX();
}

const float DesignResolution::getScale() const
{
    return _scale;
}