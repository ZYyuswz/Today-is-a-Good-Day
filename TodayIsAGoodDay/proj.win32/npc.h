#pragma once
#include "cocos2d.h"
USING_NS_CC;

class NPC : public Sprite {
public:
    NPC();
    ~NPC();

    // 初始化 NPC
    bool init() override;

    // 显示对话框
    void showDialog();

    // 更新对话内容
    void updateDialog();

    // 增加好感度
    void increaseAffinity(int amount);

    // 检查好感度是否达到阈值
    bool isAffinityThresholdReached();

    // 创建 NPC
    CREATE_FUNC(NPC);

private:
    // 对话内容
    std::vector<std::string> dialogs;

    // 当前对话索引
    int currentDialogIndex;

    // 好感度
    int affinity;

    // 好感度阈值
    int affinityThreshold;

    // 对话框
    cocos2d::Label* dialogLabel;

    // NPC 在瓦片地图上的位置
    cocos2d::Vec2 tilePosition;

    cocos2d::Sprite* chatBackground;
};
