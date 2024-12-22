#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
// 定义合作界面类
class scene_coop : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene()
    {
        return scene_coop::create();
    }

    // 初始化场景
    virtual bool init();

    // 创建按钮回调函数
    void onCreate(Ref* sender);
    void onJoin(Ref* sender);

    // 使用 CREATE_FUNC 宏来自动生成 create 函数
    CREATE_FUNC(scene_coop);
};

// 定义创建界面类
class scene_create : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene()
    {
        return scene_create::create();
    }

    // 初始化场景
    virtual bool init();

    // 使用 CREATE_FUNC 宏来自动生成 create 函数
    CREATE_FUNC(scene_create);
};

// 定义加入界面类
class scene_join : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene()
    {
        return scene_join::create();
    }

    // 初始化场景
    virtual bool init();

    // 使用 CREATE_FUNC 宏来自动生成 create 函数
    CREATE_FUNC(scene_join);
};

// 定义 ConnectingScene 类
class ConnectingScene : public cocos2d::Scene
{
public:
    // 创建场景
    static Scene* createScene()
    {
        return ConnectingScene::create();
    }

    // 初始化场景
    virtual bool init();
    // 使用 CREATE_FUNC 宏来自动生成 create 函数
    CREATE_FUNC(ConnectingScene);
};

//监听线程函数
void listenThread();
//启动监听线程
void startListeningThread();
//发送消息到服务器
void sendMessageToServer(const std::string& message);
//连接到服务器
bool connectToServer();
//匹配成功函数
void handleMatchedMessage(std::string receivedMessage);
//处理连接错误信息
void handleFailedMessage(std::string receivedMessage);
//处理玩家移动消息
void handlePlayerReleaseMessage(std::string receivedMessage);
//处理砍树动作消息
void handleTreeActionMessage(std::string receivedMessage);
//处理采矿动作消息
void handleMineActionMessage(std::string receivedMessage);
//处理种植动作消息
void handlePlantActionMessage(std::string receivedMessage);
//处理耕地动作信息
void handlePloughActionMessage(std::string receivedMessage);

void handlePlayerMoveMessage(std::string receivedMessage);
