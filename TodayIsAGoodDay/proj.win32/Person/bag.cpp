#include "cocos2d.h"
#include <vector>
#include <string>
#include "person.h"
#include <iostream>
#include "definition.h"
#include "global.h"
#include "totaltools.h"


const float BAG_LEFT_LOCATION = 500.0;
const float BAG_UP_LOCATION = 675.0;
const float BAG_RIGHT_LOCATION = 1600;
const float BAG_CELL = 95.0;

Bag::Bag(): _selectedItemIndex(-1),_items(36,item()), _itemSprites(36),_itemLabels(36)
{

    isOpen = false;
    
    _items[0]=(item("axe"));
    _items[1]=(item("hammer"));
    _items[2]=(item("draft"));
    _items[3]=(item("kettle"));
    _items[4]=(item("fishing_pole"));


    _items[5]=(item(SEED_CARROT,20));
    _items[6] = (item(SEED_CORN));
    _items[7] = (item(SEED_CABBAGE));


}


//按键函数
void Bag::changeBag()
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


void Bag::addItem(const item& MyItem)
{
    int index = 0;
    // 检查背包中是否已有该物品
    for (index = 0;_items[index].name!="nothing"; index++)
    {
        if (_items[index].name == MyItem.name)
        {
            // 合并同类物品
            _items[index].num += MyItem.num;
            return;
        }
    }

    // 如果没有该物品，则添加新物品
    _items[index] = MyItem;
}

int Bag::removeItem(const item& MyItem)
{
    int index = 0;
    for (auto it = _items.begin(); it != _items.end(); ++it)
    {
        if (it->name == MyItem.name)
        {
            // 减少物品数量
            it->num -= MyItem.num;

            // 如果物品数量为0或更少，则移除该物品
            if (it->num <= 0)
            {
                _items[index] = item(); //改为nothing
                return 0;
            }
            return it->num;
        }
        index++;
    }
}

void Bag::displayBag()
{
    // 显示背包网格背景图片
    auto bagBackground = cocos2d::Sprite::create("bag/BagBackground.png"); //创建精灵
    bagBackground->setAnchorPoint(Vec2(0.5f,0.5f));//设置锚点位于中心
    bagBackground->setPosition(1024.0f,576.0f);
    bagBackground->setScale(1.5f);
    bagBackground->setName("bagBackground");
    Director::getInstance()->getRunningScene()->addChild(bagBackground,101);

    
    // 显示背包格的图片和物品图案
    float x = BAG_LEFT_LOCATION;
    float y = BAG_UP_LOCATION;
    int index = 0;
    for (const auto& item : _items)
    {
        Sprite* itemSprite;
        //为精灵找到图片并创建
        if (isFiveTool(item.name)) {
            itemSprite = cocos2d::Sprite::create("tool/" + item.name +
                std::to_string(leading_charactor.toolLevel()) + ".png");
            itemSprite->setScale(3.0f);
        }       
        else if (item.name.find("drop") != std::string::npos) {
            itemSprite = cocos2d::Sprite::create("bag/"+item.name + ".png");
            itemSprite->setScale(4.0f);
        }
        else {
            itemSprite = cocos2d::Sprite::create("bag/"+item.name + ".png");
        }
        itemSprite->setPosition(cocos2d::Vec2(x, y));
        
        Director::getInstance()->getRunningScene()->addChild(itemSprite,102);
        _itemSprites[index] = itemSprite;

        //创建标签
        auto itemLabel = Label::createWithSystemFont(std::to_string(item.num), "Arial", 20);
        Director::getInstance()->getRunningScene()->addChild(itemLabel, 102);
        itemLabel->setPosition(x + 25, y - 25);
        _itemLabels[index] = itemLabel;

        //挪到下一格
        x += BAG_CELL;
        if (x > BAG_RIGHT_LOCATION)
        {
            x = BAG_LEFT_LOCATION;
            y -= BAG_CELL;
        }
        index++;
    }
    
}

void Bag::closeBag()
{
    // 清除物品精灵
    for (auto sprite : _itemSprites)
    {
        sprite->removeFromParent();
    }
    // 清除物品信息标签
    for (auto label : _itemLabels)
    {
        label->removeFromParent();
    }

    // 重置选中物品的索引
    _selectedItemIndex = -1;

    auto currentScene = Director::getInstance()->getRunningScene();
    // 移除背包网格背景图片
    auto bagBackground = currentScene->getChildByName("bagBackground");
    if (bagBackground)
    {
        bagBackground->removeFromParent();
    }

   
}


