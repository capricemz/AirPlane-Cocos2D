#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LayerBullet : public Layer
{
public:
	LayerBullet(void);
	~LayerBullet(void);

	CREATE_FUNC(LayerBullet);

	virtual bool init();

	Vector<Sprite *> vecBulletGet();
	
	void bulletAdd(float delta);
	void bulletRemove(Node *bullet);

	void shootStart();
	void shootStop();
	void useBulletDouble();

private:
	void createBulletSingle();
	void createBulletDouble();

private:
	float _timeNow;
	float _timeOverDoubleBullet;
	Vector<Sprite *> _vecBullet;
};

