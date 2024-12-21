/* ----- 实现每一个动作的特效 ----- */
#include "person.h"

void Person::useTools()
{
	if (currentTool == nullptr)
		return;
	auto currentScene = Director::getInstance()->getRunningScene();
	currentScene->removeChildByName("tool");
	currentTool->_toolsprite = Sprite::create("/tool/" + currentTool->getName() + 
		                       std::to_string(currentTool->getLevel())+".png");	
	currentScene->addChild(currentTool->_toolsprite, PERSON_LAYER);
	currentTool->_toolsprite->setPosition(getWorldPosition() + Vec2(48, 0));
	currentTool->_toolsprite->setScale(3.0f);
	currentTool->_toolsprite->setName("tool");

	//模拟动画效果
	auto rotateCounterClockwise = RotateBy::create(0.2f, -90.0f); // 逆时针旋转 45 度，耗时 0.5 秒
	auto pause = DelayTime::create(0.2f); // 暂停 1 秒
	auto rotateClockwise = RotateBy::create(0.2f, 90.0f); // 顺时针旋转 45 度，耗时 0.5 秒
	auto fade = FadeOut::create(0.1f);
	auto useSequence = Sequence::create(rotateClockwise,rotateCounterClockwise, 
		               rotateClockwise->clone(), pause, fade,nullptr);
	currentTool->_toolsprite->runAction(useSequence);

} 