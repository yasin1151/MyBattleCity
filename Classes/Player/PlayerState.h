#ifndef _PlayerState_H_
#define _PlayerState_H_

#include <cocos2d.h>

class Player;
class GameLayer;

//player输入类型
typedef enum
{
	PlayerDefaultState,
	PlayerDown,
	PlayerUp,
	PlayerLeft,
	PlayerRight,
	PlayerShot
}PlayerInputType;

class PlayerStateDown;
class PlayerStateUp;
class PlayerStateLeft;
class PlayerStateRight;
class PlayerStateShot;

/**
*	@class : PlayerState
*	@brief : 玩家状态基类
*	@warnning : 使用引用是为了保证绝对非空
*/
class PlayerState
{
public:
	//处理输入, 返回新状态
	virtual PlayerState* handleInput(Player& player, cocos2d::Layer* layer, const PlayerInputType& type);

	//每一帧或者固定时间调用
	virtual void update(Player& player);

	//每次切换状态时调用
	virtual void onEnter(Player& player, cocos2d::Layer* layer);

	//虚析构函数
	virtual ~PlayerState();

	//状态类的简单工厂,用于内存池的新建内存
	PlayerState* operator()(size_t type) const;
};

/**
*	@class : PlayerStateDown
*	@brief : 处理玩家向下的状态
*/
class PlayerStateDown : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateUp
*	@brief : 处理玩家向上的状态
*/
class PlayerStateUp : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateLeft
*	@brief : 处理玩家向左的状态
*/
class PlayerStateLeft : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateRight
*	@brief : 处理玩家向右的状态
*/
class PlayerStateRight : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};

/**
*	@class : PlayerStateShot
*	@brief : 处理玩家向发射的状态
*/
class PlayerStateShot : public PlayerState
{
public:
	virtual void onEnter(Player& player, cocos2d::Layer* layer) override;
};



#endif