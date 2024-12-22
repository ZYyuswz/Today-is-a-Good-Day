#pragma once
#include "cocos2d.h"
USING_NS_CC;

class NPC : public Sprite {
public:
    NPC();
    ~NPC();

    // ��ʼ�� NPC
    bool init() override;

    // ��ʾ�Ի���
    void showDialog();

    // ���¶Ի�����
    void updateDialog();

    // ���Ӻøж�
    void increaseAffinity(int amount);

    // ���øж��Ƿ�ﵽ��ֵ
    bool isAffinityThresholdReached();

    // ���� NPC
    CREATE_FUNC(NPC);

private:
    // �Ի�����
    std::vector<std::string> dialogs;

    // ��ǰ�Ի�����
    int currentDialogIndex;

    // �øж�
    int affinity;

    // �øж���ֵ
    int affinityThreshold;

    // �Ի���
    cocos2d::Label* dialogLabel;

    // NPC ����Ƭ��ͼ�ϵ�λ��
    cocos2d::Vec2 tilePosition;

    cocos2d::Sprite* chatBackground;
};
