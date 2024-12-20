/* ----- 实现每一个动作的特效 ----- */
#include "person.h"

void Person::useTools()
{
	currentTool->_toolsprite = Sprite::create("/tool/" + currentTool->getName() + "1.png");
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->addChild(currentTool->_toolsprite);
	currentTool->_toolsprite->setPosition(getWorldPosition() + Vec2(64, 48));

	//模拟动画效果
	auto rotateCounterClockwise = RotateBy::create(0.5f, -45.0f); // 逆时针旋转 45 度，耗时 0.5 秒
	auto pause = DelayTime::create(0.1f); // 暂停 0.1 秒
	auto rotateClockwise = RotateBy::create(0.5f, 90.0f); // 顺时针旋转 90 度，耗时 0.5 秒
	auto useSequence = Sequence::create(rotateCounterClockwise, pause, rotateClockwise, nullptr);
	currentTool->_toolsprite->runAction(useSequence);
	currentTool->_toolsprite->release();
}