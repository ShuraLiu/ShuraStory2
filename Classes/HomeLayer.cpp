//
//  HomeLayer.cpp
//  ShuraStory
//
//  Created by 刘潇逸 on 14/12/10.
//
//

#include "HomeLayer.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

HomeLayer::HomeLayer()
: _pNodeCCS(nullptr)
, _pHomeLayerUIEventDelegate(nullptr)
, _pButtonTest(nullptr)
{
    
}

HomeLayer::~HomeLayer()
{
    
}

bool HomeLayer::init()
{
    if (!BaseView::init())
    {
        return false;
    }
    
    _pNodeCCS = CSLoader::createNode("HomeScene.csb");
    auto winSize = Director::getInstance()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _pNodeCCS->setContentSize(winSize);
    addChild(_pNodeCCS);
    
    _pButtonTest = (Button*) Helper::seekNodeByName(_pNodeCCS, "ButtonTest");
    
    _pButtonTest->addTouchEventListener([this](Ref* ref,Widget::TouchEventType type){
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                if (_pHomeLayerUIEventDelegate)
                {
                    _pHomeLayerUIEventDelegate->onButtonTestPressed();
                }
            }
                break;
                
            default:
                break;
        }
    });
    
    _pButtonTest2 = (Button*) Helper::seekNodeByName(_pNodeCCS, "ButtonTest2");
    _pButtonTest2->addTouchEventListener([this](Ref* ref,Widget::TouchEventType type){
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                if (_pHomeLayerUIEventDelegate)
                {
                    _pHomeLayerUIEventDelegate->onButtonTest2Pressed();
                }
            }
                break;
                
            default:
                break;
        }
    });
    
    return true;
}

void HomeLayer::onEnter()
{
    BaseView::onEnter();
}

void HomeLayer::onExit()
{
    BaseView::onExit();
}

void HomeLayer::addSubView(const ViewController::Ptr &controller, ViewControllerType type)
{
    switch (type)
    {
        case ViewControllerType::SubViewController:
        {
            auto pNode = controller->getView();
            pNode->setPosition(Vec2(200, 200));
            pNode->setAnchorPoint(Vec2::ZERO);
            this->addChild(pNode, 1);
        }
            break;
            
        default:
            break;
    }
}

void HomeLayer::removeSubView(const ViewController::Ptr &controller, ViewControllerType type)
{
    switch (type) {
        case ViewControllerType::SubViewController:
        {
            this->removeChild(controller->getView());
        }
            break;
            
        default:
            break;
    }
}

void HomeLayer::setHomeLayerUIEventDelegate(HomeLayerUIEventDelegate *pDelegate)
{
    _pHomeLayerUIEventDelegate = pDelegate;
}