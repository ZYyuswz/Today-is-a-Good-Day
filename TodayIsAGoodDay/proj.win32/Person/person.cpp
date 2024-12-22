/* ----- 该文件夹主cpp ----- */
/* 详细内容参阅开发者手册 */

#include "person.h"
#include "global.h"
#include "totaltools.h"
#include <vector>
#include "Map/drop.h"

Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, const Vec2& Tiledposition);


/*关于图片，这里只给出了一张，如果要有选择角色功能的话，那么图片要不一样*/
Person::Person()

{

}
void Person::person_construction(const std::string& name, const int& sex, const std::string& farmName,
    Scene* currentScene, int level, int HP, int energy, int money)
{

    //初始化赋值
    _name = name;
    _sex = sex;
    _farmName = farmName;
    _level = level;
    _HP = HP;
    _money = money;
    _energy = energy;
     
    auto newCharacterLayer = Layer::create();
    currentScene->addChild(newCharacterLayer); // 将人物层添加到当前场景中
    // 创建一个精灵并添加到Person节点中
    _sprite = cocos2d::Sprite::create("/person/person_front_1.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 screenCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    _sprite->setPosition(screenCenter);

    if (_sprite)
    {
        newCharacterLayer->addChild(_sprite);
    }
    init();
    
    createAnimate();
    
}
bool Person::init()
{
    /*
    if (!Node::init())
    {
        return false;
    }
    */
    return true;
    
}

void Person::decreaseHP(const int attack)
{
    _HP -= attack;//扣血
    if (isDead()) {
        dead();
    }
}

void Person::dead()
{
    _HP /= 10;
    _money /= 10;
    _energy /= 10;
    //   setPosition(HOSPITAL_X, HOSPITAL_Y);
     //  Director::getInstance()->replaceScene(town); //切换场景为小镇
}

void Person::moneyUP(int deltaMoney)
{
    _money += deltaMoney;
    //预留函数接口
}

Vec2 Person::getTiledPosition()
{
    Vec2 PersonWP = _sprite->getPosition();
    Vec2 MapTP = MapManager::getInstance()->getCurrentMap()->getPosition();
    return convertWorldToTileCoord(PersonWP, MapTP);
}

Vec2 Person::getWorldPosition()
{
    return _sprite->getPosition();
}

void Person::levelUP()
{
    if (experience_all > 1000) {
        experience_all -= 1000;
        _level++;
    }
}

void Person::collectItems()
{
    Vec2 currentPosition = _sprite->getPosition();
    auto currentTiledMap = MapManager::getInstance()->getCurrentMap();
    Vec2 currentTiledPosition = convertWorldToTileCoord(currentPosition, currentTiledMap->getPosition());
    std::vector <Dropper*>* dropVector = getDrops(currentTiledPosition);
    if (dropVector->empty()) {
        CCLOG("EMPTY");
        delete dropVector;
        return;
    }
    for (auto i = 0; i < dropVector->size(); i++) {
        //MyBag.addItem(item((*dropVector)[i]->type));
    }
    delete dropVector;
}


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
    chatBackground->setAnchorPoint(Vec2(0.5, 0.5));
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
 //       return;
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

Pig::Pig() : moveSpeed(30.0f), isMoving(false), currentDirection(0) {
    // 初始化 Pig
}

Pig::~Pig() {
    // 释放资源
}

bool Pig::init() {
    if (!Sprite::initWithFile("npc/pig_front.png")) { // 初始方向为向下
        return false;
    }

    // 加载方向图片
    upFrame = SpriteFrame::create("npc/pig_back.png", Rect(0, 0, 32, 32));
    downFrame = SpriteFrame::create("npc/pig_front.png", Rect(0, 0, 32, 32));
    leftFrame = SpriteFrame::create("npc/pig_left.png", Rect(0, 0, 32, 32));
    rightFrame = SpriteFrame::create("npc/pig_right.png", Rect(0, 0, 32, 32));

    // 每帧更新
    this->scheduleUpdate();

    return true;
}


Vec2 convertTiledToWorld(const Vec2& TiledWorldPosition, const Vec2& TiledAnchorposition) {

    // 将差值转换为瓦片坐标
    Vec2 TiledGap = TiledWorldPosition * (BEACH_SMALL_SCALE * TILESIZE);

    // 计算屏幕坐标与瓦片地图位置的差值
    Vec2 WorldPosition = (TiledGap + TiledAnchorposition);


    return WorldPosition;
}
void Pig::setTilePosition(const Vec2& tilePosition, TMXTiledMap* tileMap) {
    // 保存 Pig 在瓦片地图上的位置
    this->targetTilePosition = tilePosition;

    Vec2 worldPosition = convertTiledToWorld(targetTilePosition, tileMap->getPosition());

    // 设置 Pig 的世界坐标
    this->setPosition(worldPosition);
}

void Pig::moveToTile(const Vec2& targetTilePosition, TMXTiledMap* tileMap) {
    // 保存目标瓦片位置
    this->targetTilePosition = targetTilePosition;

    // 将目标瓦片坐标转换为世界坐标

    Vec2 targetWorldPosition = convertTiledToWorld(targetTilePosition, tileMap->getPosition());

    // 设置目标世界坐标
    this->targetTilePosition = targetWorldPosition;

    // 标记为正在移动
    isMoving = true;
}

void Pig::update(float dt) {
    if (isMoving) {
        // 获取当前位置
        Vec2 currentPosition = this->getPosition();

        // 计算移动方向
        Vec2 direction = targetTilePosition - currentPosition;
        direction.normalize();

        // 根据方向切换图片
        if (direction.y > 0) {
            this->setSpriteFrame(upFrame);
            currentDirection = 0; // 向上
        }
        else if (direction.y < 0) {
            this->setSpriteFrame(downFrame);
            currentDirection = 1; // 向下
        }
        else if (direction.x < 0) {
            this->setSpriteFrame(leftFrame);
            currentDirection = 2; // 向左
        }
        else if (direction.x > 0) {
            this->setSpriteFrame(rightFrame);
            currentDirection = 3; // 向右
        }

        // 计算移动距离
        Vec2 moveDelta = direction * moveSpeed * dt;

        // 更新位置
        this->setPosition(currentPosition + moveDelta);

        // 检查是否到达目标位置
        if ((this->getPosition() - targetTilePosition).length() < 10.0f) {
            // 到达目标位置
            this->setPosition(targetTilePosition);
            isMoving = false;
        }
    }
}
