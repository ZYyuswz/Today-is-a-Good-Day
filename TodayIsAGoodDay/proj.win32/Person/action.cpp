/* ----- 实现每一个动作的特效 ----- */
#include "person.h"

void Person::useTools()
{
	if (currentTool == nullptr)
		return;
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->removeChildByName("tool");
	currentTool->_toolsprite = Sprite::create("/tool/" + currentTool->getName() +
		std::to_string(currentTool->getLevel()) + ".png");
	currentScene->addChild(currentTool->_toolsprite, PERSON_LAYER);
	currentTool->_toolsprite->setPosition(getWorldPosition() + Vec2(48, 0));
	currentTool->_toolsprite->setScale(3.0f);
	currentTool->_toolsprite->setName("tool");

	//模拟动画效果
	auto rotateCounterClockwise = RotateBy::create(0.2f, -90.0f); // 逆时针旋转 45 度，耗时 0.5 秒
	auto pause = DelayTime::create(0.2f); // 暂停 1 秒
	auto rotateClockwise = RotateBy::create(0.2f, 90.0f); // 顺时针旋转 45 度，耗时 0.5 秒
	auto fade = FadeOut::create(0.1f);
	auto useSequence = Sequence::create(rotateClockwise, rotateCounterClockwise,
		rotateClockwise->clone(), pause, fade, nullptr);
	currentTool->_toolsprite->runAction(useSequence);

}

void Person::startFishing()
{
	if (currentTool == nullptr || currentTool->getName() != "fishing_pole")
		return;
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->removeChildByName("tool");
	currentTool->_toolsprite = Sprite::create("/tool/fishing.png");
	currentScene->addChild(currentTool->_toolsprite, PERSON_LAYER);
	currentTool->_toolsprite->setPosition(getWorldPosition() + Vec2(36, 0));
	currentTool->_toolsprite->setScale(3.0f);
	currentTool->_toolsprite->setName("tool");

	//模拟动画效果
	auto rotateCounterClockwise = RotateBy::create(0.5f, -45.0f); // 逆时针旋转 90 度，耗时 0.5 秒
	auto pause = DelayTime::create(5.0f); // 暂停 1 秒
	auto rotateClockwise = RotateBy::create(0.5f, 75.0f); // 顺时针旋转 90 度，耗时 0.5 秒

	auto useSequence = Sequence::create(rotateClockwise, rotateCounterClockwise,
		rotateClockwise->clone(), pause, nullptr);
	currentTool->_toolsprite->runAction(useSequence);
}

void Person::endFishing()
{
	auto rotateCounterClockwise = RotateBy::create(0.f, -90.0f);
	auto pause = DelayTime::create(1.0f); // 暂停 1 秒
	auto fade = FadeOut::create(0.1f);
	auto useSequence = Sequence::create(rotateCounterClockwise, pause, fade, nullptr);
	currentTool->_toolsprite->runAction(useSequence);
}