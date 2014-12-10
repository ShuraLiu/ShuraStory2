//
//  ViewController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#include "ViewController.h"

void ViewController::addChildViewController(const ViewController::Ptr &controller)
{
    _children.push_back(controller);
    
}