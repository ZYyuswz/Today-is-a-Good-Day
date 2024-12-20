#include "cocos2d.h"
#include <vector>
#include <string>
#include "person.h"
#include <iostream>
#include "definition.h"
#include "global.h"



const int BAG_LEFT_LOCATION = 500;
const int BAG_UP_LOCATION = 1000;
const int BAG_RIGHT_LOCATION = 1500;
const int BAG_CELL = 100;

Bag::Bag(): _selectedItemIndex(-1)
{
    // ����һ����ǩ������ʾ��Ʒ��Ϣ
    _itemInfoLabel = cocos2d::Label::createWithSystemFont("", "Arial", 24);
    isOpen = false;
    _items.push_back(item("axe"));
    _items.push_back(item("hammer"));
    _items.push_back(item("draft"));
    _items.push_back(item("kettle"));
    _items.push_back(item("fishing_pole"));
    _items.push_back(item("Carrot_Seeds"));
}

//��������
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
    // ��鱳�����Ƿ����и���Ʒ
    for (auto& item : _items)
    {
        if (item.name == MyItem.name)
        {
            // �ϲ�ͬ����Ʒ
            item.num += MyItem.num;
            return;
        }
    }

    // ���û�и���Ʒ�����������Ʒ
    _items.emplace_back(MyItem);
}

void Bag::removeItem(const item& MyItem)
{
    for (auto it = _items.begin(); it != _items.end(); ++it)
    {
        if (it->name == MyItem.name)
        {
            // ������Ʒ����
            it->num -= MyItem.num;

            // �����Ʒ����Ϊ0����٣����Ƴ�����Ʒ
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
    
    // ���֮ǰ����Ʒ����
    for (auto sprite : _itemSprites)
    {
        sprite->removeFromParent();
    }
    _itemSprites.clear();
    

    // ��ʾ�������񱳾�ͼƬ
    auto bagBackground = cocos2d::Sprite::create("bag/BagBackground.png"); //��������
    bagBackground->setAnchorPoint(Vec2(0.5f,0.5f));//����ê��λ������
    bagBackground->setPosition(1024.0f,576.0f);
    bagBackground->setScale(1.2f);
    bagBackground->setName("bagBackground");
    Director::getInstance()->getRunningScene()->addChild(bagBackground);

    // ��ʾ�������ͼƬ����Ʒͼ��
    int x = BAG_LEFT_LOCATION;
    int y = BAG_UP_LOCATION;
    for (const auto& item : _items)
    {
        auto itemSprite = cocos2d::Sprite::create("bag/"+ item.name + ".png"); // ����ÿ����Ʒ����һ����Ӧ��ͼƬ
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
    // �����Ʒ����
    for (auto sprite : _itemSprites)
    {
        sprite->removeFromParent();
    }
    _itemSprites.clear();

    // �����Ʒ��Ϣ��ǩ
//    _itemInfoLabel->setString("");

    // ����ѡ����Ʒ������
    _selectedItemIndex = -1;

    auto currentScene = Director::getInstance()->getRunningScene();
    // �Ƴ��������񱳾�ͼƬ
    auto bagBackground = currentScene->getChildByName("bagBackground");
    if (bagBackground)
    {
        bagBackground->removeFromParent();
    }

    // �رձ�������
    isOpen = false;
}


void Bag::updateItemInfo(cocos2d::Vec2 position)
{
    // ������λ���Ƿ���ĳ����Ʒ��
    for (int i = 0; i < _itemSprites.size(); ++i)
    {
        auto nowScene = Director::getInstance()->getRunningScene();
        nowScene->addChild(_itemInfoLabel);
        _itemInfoLabel->setPosition(position);
        auto sprite = _itemSprites[i];
        if (sprite->getBoundingBox().containsPoint(position))
        {
            _itemInfoLabel->setString(_items[i].name + std::to_string(_items[i].num));
            _selectedItemIndex = i;
            return;
        }
    }

    // �����겻���κ���Ʒ�ϣ������Ʒ��Ϣ
    _itemInfoLabel->setString("");
    _selectedItemIndex = -1;
}