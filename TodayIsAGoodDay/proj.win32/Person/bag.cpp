/* ----- ʵ�ֱ������书�� �����ϳɲ��� ----- */
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
    // ���캯��
    Bag(const std::string& name, const int& sex, const std::string& farmName,
        int level, int HP, int energy, int money);

    //����������E�򿪱���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ��ӹ��߻����
    void addItem(const item& MyItem);

    // �Ƴ����߻����
    void removeItem(const item& MyItem);

    // ��ʾ��������
    void displayBag();

    //�رձ���
    void closeBag();

    // ������Ʒ��Ϣ
    void updateItemInfo(cocos2d::Vec2 position);

private:
    //��Ʒ�б�
    std::vector<item> _items;

    //��Ʒ�����б�
    std::vector<cocos2d::Sprite*> _itemSprites;

    //��Ʒ��ǩ��ֻ��һ������������ƶ���ʾ
    cocos2d::Label* _itemInfoLabel;
    int _selectedItemIndex;

    bool isOpen;
};


Bag::Bag(const std::string& name, const int& sex, const std::string& farmName,
    int level, int HP, int energy, int money)
    : Person(name, sex, farmName), _selectedItemIndex(-1)
{
    // ����һ����ǩ������ʾ��Ʒ��Ϣ
    _itemInfoLabel = cocos2d::Label::createWithSystemFont("", "Arial", 24);
    _itemInfoLabel->setPosition(cocos2d::Vec2(400, 50));
    this->addChild(_itemInfoLabel);

    //��ʼ�����̼�����
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Bag::onKeyPressed, this);

    // ������������
    auto mouseListener = cocos2d::EventListenerMouse::create();

    //��������ƶ�
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



//��������
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

    // ��ʾ�������ͼƬ����Ʒͼ��
    int x = 100;
    int y = 400;
    for (const auto& item : _items)
    {
        auto itemSprite = cocos2d::Sprite::create(item.name + ".png"); // ����ÿ����Ʒ����һ����Ӧ��ͼƬ
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
    // ������λ���Ƿ���ĳ����Ʒ��
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

    // �����겻���κ���Ʒ�ϣ������Ʒ��Ϣ
    _itemInfoLabel->setString("");
    _selectedItemIndex = -1;
}