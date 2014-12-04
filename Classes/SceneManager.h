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

class ViewController;

class SceneManager
{
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
    
    void pushViewController(ViewController* controller, bool withAnimation = false);
    void popViewController(bool withAnimation = false);
    void replaceViewController(ViewController* controller, bool withAnimation = false);
};

#endif /* defined(__ShuraStory__SceneManager__) */
