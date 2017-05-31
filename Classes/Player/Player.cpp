#include "Player.h"
#include "Layer\GameLayer.h"

Player::Player(TankBase* pTank)
	:m_pTank(pTank)
{
	//设置内存池的初始参数
	m_memPoolState.setCallNum(1);
	m_memPoolState.setNewFunc(PlayerState());

	//实例一个初始状态
	m_pState = m_memPoolState.allocWithTag(PlayerDefaultState);
}

Player::~Player()
{
	if (m_pTank)
	{
		delete m_pTank;
	}

	m_memPoolState.clear();
}

void Player::hanleInput(const PlayerInputType& type, Layer* layer)
{
	//获取新状态
	PlayerState* pNewState = m_pState->handleInput(*this, layer, type);

	//如果获取到新状态
	if (pNewState)
	{
		//将老状态放入内存池中
		m_memPoolState.release(m_pState);

		//切换到新状态
		m_pState = pNewState;

		//调用onEnter() 函数
		m_pState->onEnter(*this, layer);
	}
}

void Player::update(Layer* layer, float dt)
{
	m_pState->update(*this);
}

SimpleMemPool<PlayerState>& Player::getStateMemPool()
{
	return m_memPoolState;
}

TankBase* Player::getTank()
{
	return m_pTank;
}