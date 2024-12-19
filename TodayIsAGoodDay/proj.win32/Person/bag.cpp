#include "cocos2d.h"
#include <vector>
#include <string>
#include "person.h"
#include <iostream>
#include "definition.h"
#include "global.h"


Bag::Bag(): _selectedItemIndex(-1)
{
    // 创建一个标签用于显示物品信息
    _itemInfoLabel = cocos2d::Label::createWithSystemFont("", "Arial", 24);
    _itemInfoLabel->setPosition(cocos2d::Vec2(400, 50));
    this->addChild(_itemInfoLabel);
  
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
    

    // 显示背包网格背景图片
    auto bagBackground = cocos2d::Sprite::create("bag/BagBackground.png"); //创建精灵
    bagBackground->setAnchorPoint(Vec2(0.5f,0.5f));//设置锚点位于中心
    bagBackground->setPosition(1024.0f,576.0f);
    bagBackground->setScale(0.4f);
    MapManager::getInstance()->getCurrentMap()->addChild(bagBackground);

    // 显示背包格的图片和物品图案
    int x = BAG_LEFT_LOCATION;
    int y = BAG_UP_LOCATION;
    for (const auto& item : _items)
    {
        auto itemSprite = cocos2d::Sprite::create(item.name + ".png"); // 假设每个物品都有一个对应的图片
        itemSprite->setPosition(cocos2d::Vec2(x, y));
        this->addChild(itemSprite);
        _itemSprites.push_back(itemSprite);

        x += BAG_CELL;
        if (x > BAG_RIGHT_LOCATION)
        {
            x = BAG_LEFT_LOCATION;
            y -= BAG_CELL;
        }
    }
}

void Bag::closeBag()
{
    // 清除物品精灵
    for (auto sprite : _itemSprites)
    {
        sprite->removeFromParent();
    }
    _itemSprites.clear();

    // 清除物品信息标签
    _itemInfoLabel->setString("");

    // 重置选中物品的索引
    _selectedItemIndex = -1;

    // 移除背包网格背景图片
    auto bagBackground = this->getChildByName("bagBackground");
    if (bagBackground)
    {
        bagBackground->removeFromParent();
    }

    // 关闭背包界面
    isOpen = false;
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