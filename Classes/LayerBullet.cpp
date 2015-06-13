#include "LayerBullet.h"
#include "LayerPlane.h"

LayerBullet::LayerBullet(void)
{
}

LayerBullet::~LayerBullet(void)
{
}

bool LayerBullet::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("ui/shoot.png");
		spriteBatchNodeBullet = SpriteBatchNode::createWithTexture(texture);//bulletBatchNode为CCSpriteBatchNode类型成员变量
		addChild(spriteBatchNodeBullet);

		isInit = true;
	} while (0);
	return isInit;
}

void LayerBullet::bulletAdd(float dt)
{
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	spriteBatchNodeBullet->addChild(bullet);//这里子弹要添加到bulletBatchNode中
	vecBullet.pushBack(bullet);

	auto plane = LayerPlane::getInstance()->getChildByTag(AIRPLANE);
	auto positionPlane = plane->getPosition();
	bullet->setPosition(Vec2(positionPlane.x,positionPlane.y + plane->getContentSize().height/2));

	Value distance(Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2 - positionPlane.y);
	Value velocity(420.0f);//飞行速度：420pixel/sec
	Value duration(distance.asFloat()/velocity.asFloat());
	auto actionMoveBy = MoveBy::create(duration.asFloat(),Size(0,distance.asFloat()));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(LayerBullet::bulletMoveOut,this));
	auto sequence = Sequence::create(actionMoveBy,actionDone,NULL);

	bullet->runAction(sequence);
}

void LayerBullet::bulletRemove(Sprite *bullet)
{
	if (bullet != NULL)
	{
		vecBullet.erase(vecBullet.find(bullet));
		spriteBatchNodeBullet->removeChild(bullet,true);
	}
}
void LayerBullet::bulletMoveOut(Node *node)
{
	bulletRemove((Sprite *)node);
}

void LayerBullet::shootStart(float delay)
{
	schedule(schedule_selector(LayerBullet::bulletAdd),0.2f,kRepeatForever,delay);
}

void LayerBullet::shootStop()
{
	unschedule(schedule_selector(LayerBullet::bulletAdd));
}