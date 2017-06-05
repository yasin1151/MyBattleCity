#ifndef _GameLayer_H_
#define _GameLayer_H_

#include <cocos2d.h>
#include "Map/TankTiledMap.h"
#include "HudLayer.h"
#include "yUtils/Helper/yUtils.h"
#include "Player\UserPlayer.h"
#include "Tank\MineTank.h"
#include "Bullet\BulletBase.h"
#include "Player\AIPlayer.h"
#include "Tank\TankFactory.h"
#include "Player\AIPlayerManager.h"
#include "yUtils\cocos\Rocker4AWithTrans.h"
#include "Stage\StageManager.h"
USING_NS_CC;

class GameLayer : public Layer
{
private:
	//当前关卡编号
	int m_iCurRoundNum;

	//地图对象
	TankTiledMap* m_pMap;

	//ui层
	HudLayer* m_pHudLayer;

	//坦克工厂对象
	TankFactory* m_pTankFactory;

	//玩家对象
	Player* m_pPlayer;

	//ai玩家管理对象
	AIPlayerManager* m_pAIMgr;

	//敌军出现的位置数组
	std::vector<Vec2> m_arrAIPos;

	//键盘映射
	std::list<EventKeyboard::KeyCode> m_listKeyCode;

	//摇杆对象
	Rocker4AWithTrans* m_pRocker;

	//道具管理类
	StageManager* m_pStageMgr;

	//当前层的配置文件
	ValueMap m_vConfig;
public:
	//roundNum : 关卡数目，1~n
	static GameLayer* create(int roundNum);

	bool init(int roundNum);

	virtual ~GameLayer() override;

	virtual void update(float dt) override;

	//道具出现更新函数
	void stageCreateUpdate(float dt);

	//摇杆更新
	void rockerUpdate(float dt);

	//添加ai对象
	void aiCreator(float dt);

	//初始化地图对象
	bool initMap(const char* fileName);
	
	//初始化菜单
	bool initMenu();

	//初始化ai玩家
	bool initAIPlayer();

	//初始化用户
	bool initPlayer();

	//初始化道具
	bool initStage();

	//初始化键盘事件
	bool initKeyboardEvent();

	//创建玩家,1代表玩家，2代表ai玩家
	Player* createPlayer(const TankType& tankType, int playerType, const Vec2& vInitPos);

	//获取hud层
	HudLayer* getHudLayer();

	//按钮回掉函数
	void LeftCallBack(Ref* ref);

	void RightCallBack(Ref* ref);

	void UpCallBack(Ref* ref);

	void DownCallBack(Ref* ref);

	void ShotCallBack(Ref* ref);

	void KeyboardCallBack(EventKeyboard::KeyCode keyCode);
};

#endif