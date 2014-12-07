//
//  TestViewController.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/7.
//
//

#include "TestViewController.h"
#include "HelloWorldScene.h"

cocos2d::Node* TestViewController::createView()
{
    return HelloWorld::createScene();
}

void TestViewController::onStart()
{
    CCLOG("TestViewController[onStart]");
}