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
	
	void bulletAdd(float dt);
	void bulletRemove(Sprite *bullet);
	void bulletMoveOut(Node *node);

	void shootStart(float delay = 0.0f);
	void shootStop();
	
private:
	Vector<Sprite *> _vecBullet;
};

