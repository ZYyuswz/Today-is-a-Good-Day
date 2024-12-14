/* ----- 实现背包及其功能 包括合成操作 ----- */
#include "cocos2d.h"
#include <vector>
#include <string>
#include "person.h"
#include <iostream>

struct item
{
    std::string name;
    int num;
    item(const std::string itemName, const int itemNum = 1) :name(itemName), num(itemNum){} 
};


class Bag : public Person
{
public:
    // 构造函数
    Bag(const std::string& name, const int& sex, const std::string& farmName,
        int level, int HP, int energy, int money);

    //监听器，按E打开背包
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 添加工具或材料
    void addItem(const item& MyItem);

    // 移除工具或材料
    void removeItem(const item& MyItem);

    // 显示背包内容
    void displayBag();

    //关闭背包
    void closeBag();

    // 更新物品信息
    void updateItemInfo(cocos2d::Vec2 position);

private:
    //物品列表
    std::vector<item> _items;

    //物品精灵列表
    std::vector<cocos2d::Sprite*> _itemSprites;

    //物品标签，只有一个，根据鼠标移动显示
    cocos2d::Label* _itemInfoLabel;
    int _selectedItemIndex;

    bool isOpen;
};


Bag::Bag(const std::string& name, const int& sex, const std::string& farmName,
    int level, int HP, int energy, int money)
    : Person(name, sex, farmName), _selectedItemIndex(-1)
{
    // 创建一个标签用于显示物品信息
    _itemInfoLabel = cocos2d::Label::createWithSystemFont("", "Arial", 24);
    _itemInfoLabel->setPosition(cocos2d::Vec2(400, 50));
    this->addChild(_itemInfoLabel);

    //初始化键盘监听器
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Bag::onKeyPressed, this);

    // 创建鼠标监听器
    auto mouseListener = cocos2d::EventListenerMouse::create();

    //监听鼠标移动
    mouseListener->onMouseMove = [this](cocos2d::Event* event) {
        cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
        cocos2d::Vec2 mousePosition = mouseEvent->getLocation();
        updateItemInfo(mousePosition);
        };

    mouseListener->onMouseDown = [this](cocos2d::Event* event) {
        cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
        cocos2d::Vec2 mousePosition = mouseEvent->getLocation();
        updateItemInfo(mousePosition);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}



//按键函数
void Bag::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E)
    {
        isOpen = !isOpen;
        if (isOpen)
        {
            displayBag();
        }
        else
        {
            closeBag();
        }
    }       
}


void Bag::addItem(const item& MyItem)
{
    // 检查背包中是否已有该物品
    for (auto& item : _items)
    {
        if (item.name == MyItem.name)
        {
            // 合并同类物品
            item.num += MyItem.num;
            return;
        }
    }

    // 如果没有该物品，则添加新物品
    _items.emplace_back(MyItem);
}

void Bag::removeItem(const item& MyItem)
{
    for (auto it = _items.begin(); it != _items.end(); ++it)
    {
        if (it->name == MyItem.name)
        {
            // 减少物品数量
            it->num -= MyItem.num;

            // 如果物品数量为0或更少，则移除该物品
            if (it->num <= 0)
            {
                _items.erase(it);
            }
            return;
        }
    }
}

void Bag::displayBag()
{
    // 清除之前的物品精灵
    for (auto sprite : _itemSprites)
    {
        sprite->removeFromParent();
    }
    _itemSprites.clear();

    // 显示背包格的图片和物品图案
    int x = 100;
    int y = 400;
    for (const auto& item : _items)
    {
        auto itemSprite = cocos2d::Sprite::create(item.name + ".png"); // 假设每个物品都有一个对应的图片
        itemSprite->setPosition(cocos2d::Vec2(x, y));
        this->addChild(itemSprite);
        _itemSprites.push_back(itemSprite);

        x += 100;
        if (x > 700)
        {
            x = 100;
            y -= 100;
        }
    }
}

void Bag::updateItemInfo(cocos2d::Vec2 position)
{
    // 检查鼠标位置是否在某个物品上
    for (int i = 0; i < _itemSprites.size(); ++i)
    {
        auto sprite = _itemSprites[i];
        if (sprite->getBoundingBox().containsPoint(position))
        {
            _itemInfoLabel->setString(_items[i].name);
            _selectedItemIndex = i;
            return;
        }
    }

    // 如果鼠标不在任何物品上，清除物品信息
    _itemInfoLabel->setString("");
    _selectedItemIndex = -1;
}