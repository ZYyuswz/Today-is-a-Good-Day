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