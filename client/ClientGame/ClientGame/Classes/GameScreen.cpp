
#include "GameScreen.h"
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct SimpleStructure
{
    CCSprite* spr;
    Socket* sock;
};

void* ThreadFunction(void* arg)
{
//    pthread_mutex_lock(&mutex);
    SimpleStructure *structSimple = (SimpleStructure*)arg;
    Socket* sock = (Socket*)structSimple->sock;
    CCSprite* spr = (CCSprite*)structSimple->spr;
    // do something with args->data and args->otherData
    //    delete args;
    char* result = new char;
//    sock->recv(result);
    do{
        sock->recv(result);
        spr->cocos2d::CCNode::setVisible(true);
        
        string str(result);
        CCLOG("result*** %s", result);
        char *p;
        int *location = new int;
        int index = 0;
        p = strtok(result, ",. "); //cat chuoi bang cac ky tu ,. va space
        while(p != NULL)
        {
            CCLOG(".....%s", p);
            string str(p);
            if(strcmp(str.c_str(), "yes") == 0){
//                spr1->setPosition(ccp(200, 100));
//                this->spr1->setVisible(true);
                spr->setPosition(ccp(600, 100));
//                this->spr2->setVisible(true);
                spr->setTag(2);
                break;
            }
            else if(strcmp(str.c_str(), "no") == 0){
                spr->setPosition(ccp(200, 100));
//                this->spr2->setVisible(true);
//                spr1->setTag(2);
                spr->setTag(1);
                break;
            }
            int a = atoi(p);
            *(location + index) = a;
            index++;
            p = strtok(NULL, ",. "); //cat chuoi tu vi tri dung lai truoc do
        }
        if(*(location+1) != 0 && *(location +2) != 0){
            spr->runAction(CCMoveTo::create(2, ccp(*(location + 1), *(location + 2))));
        }
        delete location;
        str.clear();
    }
    while (!(strcmp(result, "quit") == 0));
//    pthread_mutex_unlock(&mutex);
    return NULL;
}

void CreateThread(SimpleStructure* structSimple)
{
    pthread_t thread;
    pthread_create(&thread, NULL, &ThreadFunction, structSimple);
}
GameScreen::~GameScreen(){
}

CCScene* GameScreen::scene(){
    CCScene *scene = CCScene::create();
    GameScreen* layer = GameScreen::create();
    scene->addChild(layer);
    return scene;
}

GameScreen* GameScreen::create(){
    GameScreen* pRet = new GameScreen();
    if(pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool GameScreen::init(){
    this->setTouchEnabled(true);
    
    //add sprite
    this->spr1 = CCSprite::create("Icon.png");
    this->spr1->setPosition(ccp(300, 200));
    this->addChild(spr1);
    this->spr1->setVisible(true);
    
    this->spr2 = CCSprite::create("CloseNormal.png");
    this->addChild(spr2);
    this->spr2->setVisible(false);
//    socket
    char addr[20]="192.168.1.134";
    int port= 8080;
    socket = new ClientSocket(addr, port);
    socket->connect();
    SimpleStructure* simleStruct = new SimpleStructure();
    simleStruct->sock = socket;
    simleStruct->spr = spr2;
    CreateThread(simleStruct);
    char buf[10];
    snprintf (buf, sizeof(buf), "11...");
    CCLOG("buf ::: %s", buf);
    socket->send(buf);
//    this->scheduleUpdate();
    return true;
}

void GameScreen::update(float delta){
}

void GameScreen::ccTouchesBegan(CCSet* touches, CCEvent* event){
	CCTouch* touch = (CCTouch*)touches->anyObject();
    CCPoint touchPoint = this->getParent()->convertTouchToNodeSpace(touch);
    this->spr1->runAction(CCMoveTo::create(2, touchPoint));
    //send to server message TouchLocation
    char buf[12];
    snprintf (buf, sizeof(buf), "2.%d.%d.",(int)touchPoint.x, (int)touchPoint.y);
    CCLOG("buf ::: %s", buf);
    socket->send(buf);
}

void GameScreen::ccTouchesMoved(CCSet* touches, CCEvent* event){
}

void GameScreen::ccTouchesEnded(CCSet* touches, CCEvent* event){
}

void GameScreen::recvMessage(){
////    char* re = new char;
//    socket->recv(re);
//    string str(re);
//    CCLOG("result*** %s", re);
//    char *p;
//    int *location = new int;
//    int index = 0;
//    p = strtok(re, ",. "); //cat chuoi bang cac ky tu ,. va space
//    while(p != NULL)
//    {
//        CCLOG(".....%s", p);
//        string str(p);
//        if(strcmp(str.c_str(), "yes") == 0){
//            spr1->setPosition(ccp(200, 100));
//            this->spr1->setVisible(true);
//            spr2->setPosition(ccp(600, 100));
//            this->spr2->setVisible(true);
//            spr1->setTag(1);
//            spr2->setTag(2);
//            return;
//        }
//        else if(strcmp(str.c_str(), "no") == 0){
//            spr1->setPosition(ccp(600, 100));
//            this->spr1->setVisible(true);
//            spr2->setPosition(ccp(200, 100));
//            this->spr2->setVisible(true);
//            spr1->setTag(2);
//            spr2->setTag(1);
//            return;
//        }
//        int a = atoi(p);
//        *(location + index) = a;
//        index++;
//        p = strtok(NULL, ",. "); //cat chuoi tu vi tri dung lai truoc do
//    }
//    if(*(location+1) != 0 && *(location +2) != 0)
////    spr2->runAction(CCMoveTo::create(0.5, ccp(*(location + 1), *(location + 2))));
//        spr2->setPosition(ccp(*(location + 1), *(location + 2)));
//    delete location;
//    str.clear();
//    delete re;
//    re = NULL;
//    return;
}


