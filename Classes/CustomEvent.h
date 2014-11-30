//
//  CustomEvent.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/11/30.
//
//

#ifndef __ShuraStory__CustomEvent__
#define __ShuraStory__CustomEvent__

#include "cocos2d.h"

namespace custom_event
{
    template<typename _Data>
    void dispatch(const char* eventName, const _Data& data)
    {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName, (void*)&data);
    }
    
    inline void dispatch(const char* eventName)
    {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName);
    }
    
    template<typename _Event>
    void dispatch(const _Event& event)
    {
        dispatch(_Event::NAME, event);
    }
    
    template<typename _Event>
    void dispatch()
    {
        dispatch(_Event::NAME);
    }
}

#endif /* defined(__ShuraStory__CustomEvent__) */
