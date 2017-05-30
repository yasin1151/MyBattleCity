#include "PlayerState.h"
#include "Player.h"

PlayerState* PlayerState::handleInput(Player& player, cocos2d::Layer* layer, const PlayerInputType& type)
{
	//直接进行分配
	return player.getStateMemPool().allocWithTag(type);

}

void PlayerState::update(Player& player)
{

}

void PlayerState::onEnter(Player& player, cocos2d::Layer* layer)
{

}

PlayerState::~PlayerState()
{

}

PlayerState* PlayerState::operator()(size_t type) const
{
	//创建一个返回用的指针变量
	PlayerState* pRet = nullptr;

	switch (type)
	{
	case PlayerDefaultState:
		pRet = new PlayerState();
		break;
	case PlayerDown:
		pRet = new PlayerStateDown();
		break;
	case PlayerUp:
		pRet = new PlayerStateUp();
		break;
	case PlayerLeft:
		pRet = new PlayerStateLeft();
		break;
	case PlayerRight:
		pRet = new PlayerStateRight();
		break;
	case PlayerShot:
		pRet = new PlayerStateShot();
		break;
	}

	return pRet;
}

void PlayerStateDown::onEnter(Player& player, cocos2d::Layer* layer)
{
	log("down");
	player.getTank()->command(MoveDown);
}

void PlayerStateUp::onEnter(Player& player, cocos2d::Layer* layer)
{

	log("up");
	player.getTank()->command(MoveUp);
}

void PlayerStateRight::onEnter(Player& player, cocos2d::Layer* layer)
{

	log("right");
	player.getTank()->command(MoveRight);
}

void PlayerStateLeft::onEnter(Player& player, cocos2d::Layer* layer)
{
	log("left");
	player.getTank()->command(MoveLeft);
}

void PlayerStateShot::onEnter(Player& player, cocos2d::Layer* layer)
{
	log("shot");
	player.getTank()->command(Shot);
}
