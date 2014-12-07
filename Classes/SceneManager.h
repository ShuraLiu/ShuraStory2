//
//  SceneManager.h
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/4.
//
//

#ifndef __ShuraStory__SceneManager__
#define __ShuraStory__SceneManager__

#include <stdio.h>
#include <vector>
#include "ViewController.h"

class SceneManager
{
    typedef std::vector<ViewController::Ptr> ControllerArray;
    
private:
    SceneManager();
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    
public:
    ~SceneManager();
    
    static SceneManager& getInstance()
    {
        static SceneManager manager;
        return manager;
    }
    
    void pushViewController(const ViewController::Ptr& controller, bool withAnimation = false);
    void popViewController(bool withAnimation = false);
    void replaceViewController(const ViewController::Ptr& controller, bool withAnimation = false);
    
private:
    ControllerArray _controllerStack;
};

#endif /* defined(__ShuraStory__SceneManager__) */
