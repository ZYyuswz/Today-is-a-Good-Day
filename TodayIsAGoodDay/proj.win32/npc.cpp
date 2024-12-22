#include "NPC.h"

USING_NS_CC;

NPC::NPC() : affinity(0), affinityThreshold(100), currentDialogIndex(0) {
    // 初始化对话内容
    dialogs = {
        "Hello, KuanYe!",
        "How are you today?",
        "Today is a Good Day!",
        "Goodbye!"
    };
}

NPC::~NPC() {
    // 释放资源
}

bool NPC::init() {
    if (!Sprite::initWithFile("person/npc1.png")) { // 使用图片创建 NPC
        return false;
    }

    // 创建聊天框背景图
    chatBackground = Sprite::create("npc/chatBackground.png");
    chatBackground->setAnchorPoint(Vec2(0.5,0.5));
    chatBackground->setPosition(Vec2(1024, 200)); // 聊天框背景图显示在屏幕下方
    chatBackground->setScale(0.5f);
    chatBackground->setVisible(false); // 初始时隐藏
    Director::getInstance()->getRunningScene()->addChild(chatBackground);

    // 创建对话框
    dialogLabel = Label::createWithSystemFont("", "Arial", 40);
    dialogLabel->setAnchorPoint(Vec2(0.5, 0.5));
    dialogLabel->setPosition(Vec2(1024, 200)); // 对话框显示在屏幕下方
    dialogLabel->setVisible(false); // 初始时隐藏
    Director::getInstance()->getRunningScene()->addChild(dialogLabel);

    return true;
}

void NPC::showDialog() {
    // 显示对话框
    chatBackground->setVisible(true);
    dialogLabel->setVisible(true);
    dialogLabel->setString(dialogs[currentDialogIndex]);
}

void NPC::updateDialog() {
    // 切换到下一句对话
    currentDialogIndex++;
    if (currentDialogIndex >= dialogs.size()) {
        // 对话结束，隐藏对话框
        dialogLabel->setVisible(false);
        chatBackground->setVisible(false);
        return;
        currentDialogIndex = 0; // 重置对话索引
    }
    else {
        // 显示下一句对话
        dialogLabel->setString(dialogs[currentDialogIndex]);
    }

    // 增加好感度
    increaseAffinity(10); // 每次对话增加 10 点好感度
}

void NPC::increaseAffinity(int amount) {
    // 增加好感度
    affinity += amount;
    CCLOG("Affinity increased to: %d", affinity);

    // 检查好感度是否达到阈值
    if (isAffinityThresholdReached()) {
        CCLOG("Affinity threshold reached! Intimacy level increased.");
    }
}

bool NPC::isAffinityThresholdReached() {
    // 检查好感度是否达到阈值
    return affinity >= affinityThreshold;
}