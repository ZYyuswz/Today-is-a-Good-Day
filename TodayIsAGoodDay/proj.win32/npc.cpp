#include "NPC.h"

USING_NS_CC;

NPC::NPC() : affinity(0), affinityThreshold(100), currentDialogIndex(0) {
    // ��ʼ���Ի�����
    dialogs = {
        "Hello, KuanYe!",
        "How are you today?",
        "Today is a Good Day!",
        "Goodbye!"
    };
}

NPC::~NPC() {
    // �ͷ���Դ
}

bool NPC::init() {
    if (!Sprite::initWithFile("person/npc1.png")) { // ʹ��ͼƬ���� NPC
        return false;
    }

    // ��������򱳾�ͼ
    chatBackground = Sprite::create("npc/chatBackground.png");
    chatBackground->setAnchorPoint(Vec2(0.5,0.5));
    chatBackground->setPosition(Vec2(1024, 200)); // ����򱳾�ͼ��ʾ����Ļ�·�
    chatBackground->setScale(0.5f);
    chatBackground->setVisible(false); // ��ʼʱ����
    Director::getInstance()->getRunningScene()->addChild(chatBackground);

    // �����Ի���
    dialogLabel = Label::createWithSystemFont("", "Arial", 40);
    dialogLabel->setAnchorPoint(Vec2(0.5, 0.5));
    dialogLabel->setPosition(Vec2(1024, 200)); // �Ի�����ʾ����Ļ�·�
    dialogLabel->setVisible(false); // ��ʼʱ����
    Director::getInstance()->getRunningScene()->addChild(dialogLabel);

    return true;
}

void NPC::showDialog() {
    // ��ʾ�Ի���
    chatBackground->setVisible(true);
    dialogLabel->setVisible(true);
    dialogLabel->setString(dialogs[currentDialogIndex]);
}

void NPC::updateDialog() {
    // �л�����һ��Ի�
    currentDialogIndex++;
    if (currentDialogIndex >= dialogs.size()) {
        // �Ի����������ضԻ���
        dialogLabel->setVisible(false);
        chatBackground->setVisible(false);
        return;
        currentDialogIndex = 0; // ���öԻ�����
    }
    else {
        // ��ʾ��һ��Ի�
        dialogLabel->setString(dialogs[currentDialogIndex]);
    }

    // ���Ӻøж�
    increaseAffinity(10); // ÿ�ζԻ����� 10 ��øж�
}

void NPC::increaseAffinity(int amount) {
    // ���Ӻøж�
    affinity += amount;
    CCLOG("Affinity increased to: %d", affinity);

    // ���øж��Ƿ�ﵽ��ֵ
    if (isAffinityThresholdReached()) {
        CCLOG("Affinity threshold reached! Intimacy level increased.");
    }
}

bool NPC::isAffinityThresholdReached() {
    // ���øж��Ƿ�ﵽ��ֵ
    return affinity >= affinityThreshold;
}