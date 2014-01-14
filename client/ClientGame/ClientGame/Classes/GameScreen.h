//
//  GameScreen.h
//  WarFare
//
//  Created by macbook_006 on 12/18/13.
//
//

#ifndef __WarFare__GameScreen__
#define __WarFare__GameScreen__

#include <iostream>
#include "cocos2d.h"
#include "ClientSocket.h"
#include <iostream>
#include <string.h>
#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class GameScreen : public cocos2d::CCLayer
{
public:
    ~GameScreen();
    virtual bool init();
    static cocos2d::CCScene* scene();
    static GameScreen* create();
    void update(float delta);
    virtual void ccTouchesBegan(CCSet* touch, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* touch, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touch, CCEvent* event);
    void recvMessage();
//    void *ThreadFunction(void* arg);
//    void CreateThread(Socket* sock);
private:
    bool isplay = false;
    int count = 0;
    float timeSS = 0;
    ClientSocket* socket;
    char *re = new char;
    char* name_orther =  new char;
    CCSprite * spr1, *spr2;
    CCSprite* sprPlayer;
};
#endif /* defined(__WarFare__GameScreen__) */
