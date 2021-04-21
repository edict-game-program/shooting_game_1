#pragma once
#ifndef __GAMEOBJECT_HEADER__
#define __GAMEOBJECT_HEADER__

#include <vector>
#include "ShootingGameDef.h"
#include "ShootingGame.h"

class ShootingGame;

namespace core2d
{
	namespace Collision
	{
		class CollisionBase;
	}
}

// ゲームでの更新単位を表す抽象クラス
class GameObject
{
	friend class ShootingGame::GameObjects; //GameObjects::update()内でonFirstUpdateをコールさせるためのフレンドクラス

public:
	GameObject(void) = delete;	// デフォルトコンストラクタを削除
	GameObject(ShootingGame* manager);
	virtual ~GameObject(void);

	// 更新処理の純粋仮想関数 ※継承先でオーバーライドが必須
	virtual void update(void) = 0;

	// 識別子設定・取得
	void setId(unsigned int id);
	unsigned int getId(void);

	// 任意の識別タグ設定・取得
	void setTag(unsigned int tag);
	unsigned int getTag(void);

	// 更新フラグの設定・取得
	virtual void setActive(bool active = true);
	bool isActive(void);

	// 破棄状態の設定・取得
	virtual void setDestroy(void);
	bool isDestroy(void);

	// 座標の設定・取得
	void setPosition(float x, float y);
	float getPositionX(void);
	float getPositionY(void);

	// 拡縮の設定・取得
	void setScale(float x, float y);
	float getScaleX(void);
	float getScaleY(void);

	// 回転の設定・取得
	void setRotation(float degree);
	float getRotation(void);


	//コリジョン数
	unsigned int getCollisionNum();

	//コリジョンの登録
	void addCollision(core2d::Collision::CollisionBase* collision);

	//コリジョンの登録解除
	void removeCollision();

	//コリジョンの取得
	core2d::Collision::CollisionBase* getCollision(unsigned int index);

	//接触した場合に呼ばれる。
	//接触した自分のコリジョン、相手のコリジョン、相手のGameObjectが引数として渡される
	virtual void onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target){};

protected:
	ShootingGame* manager(void) { return m_manager; }

	//updateの前に一度だけ呼ばれる
	virtual void onFirstUpdate() {};

private:
	ShootingGame* m_manager;		// 管理者へのアクセサ
	unsigned int m_id;				// オブジェクトの識別番号
	unsigned int m_tag;				// 任意の識別子
	bool m_active;					// 更新フラグ
	bool m_destroy;					// 破棄フラグ

protected:
	float m_positionX, m_positionY;	// 座標
	float m_scaleX, m_scaleY;		// 拡縮
	float m_rotation;				// 回転

	std::vector<core2d::Collision::CollisionBase*> m_collisions; //コリジョン。１つのオブジェクトで複数の当たりを持つこともある

#if COLLISION_VISIBLE
public:
	void setCollisionVisible(bool flag) { m_collisionVisible = flag; }
	bool getCollisionVisible(void) { return m_collisionVisible; }
private:
	bool m_collisionVisible;
#endif
};

#endif