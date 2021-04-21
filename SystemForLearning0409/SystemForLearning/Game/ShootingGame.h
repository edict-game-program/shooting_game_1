#pragma once
#ifndef __SHOOTINGGAME_HEADER__
#define __SHOOTINGGAME_HEADER__

#include <GameFramework.h>
#include <unordered_map>
#include <random>

#include "ShootingGameDef.h"
#include "StageData.h"

class GameObject;
class Player;
class Enemy;
class SpecialEnemy;
class PlayerBullet;
class EnemyBullet;
class UpgradeItem;
class ExplosionEffect;

namespace core2d
{
	class Sprite;
	class Text;
}

// シューティングゲームクラス
class ShootingGame : public core2d::GameFramework
{
public:
	ShootingGame(void) = delete;
	ShootingGame(unsigned int fps);
	virtual ~ShootingGame(void);

private:
	// 仮想関数をオーバーライド
	bool initializeGame(void) final;
	void finalizeGame(void) final;
	void updateGame(void) final;

	// ==============================================================
	// ゲームの制御
	// ==============================================================
private:
	// 状態を表す列挙体
	enum class GameState
	{
		Title,
		MainStage,
		BossStage,
		DefeatBoss,
		GameOver,
		GameClear,
	};
	// ゲーム状態を設定・取得
	void setGameState(GameState state);
	GameState getGameState(void);

	// ステージデータからオブジェクトを生成
	FrameKey createObjectFromStageData(int frameCount);

public:
	// プレイヤーが死んだことを通知
	void notifyPlayerDead(void);
	// ボスキャラの撃破を通知
	void notifySpecialEnemyDead(unsigned int objectId);

	// 利用可能な画面サイズを取得
	float getAvalableDisplayWidth(void);
	float getAvalableDisplayHeight(void);

private:
	core2d::Sprite* m_background[2];		// 背景用スプライト
	core2d::Text* m_titleText;
	core2d::Text* m_indicateText;
	core2d::Text* m_overText;
	core2d::Sprite* m_playerCountIcon;		// 残機表示アイコン
	core2d::Text* m_playerCountText;		// 残機表示テキスト
	core2d::Text* m_totalScoreText;			// 得点表示
	core2d::Text* m_playerSpeedText;		// 自機スピードテキスト
	core2d::Sprite* m_uiField;				// 上部UI表示領域用スプライト
	unsigned int m_playerObjectId;			// ユーザー操作キャラID
	unsigned int m_notifyObjectId;			// 通知を送ってきたObjectのID
	int m_playerCount;						// プレイヤー残機数
	GameState m_gameState;					// ゲーム状態
	unsigned int m_stageFrameCount;			// MainStageでの経過フレーム数
	const FrameInfo* m_stageData;			// ステージデータ配列へのポインタ
	int m_readPos;							// ステージデータの読み込み位置
	bool m_playerDead;
	bool m_specialEnemyDead;

	int m_totalScore;						//スコア
	bool m_updateTotalScore;

	bool m_updatePlayerSpeed;

	// ==============================================================
	// GameObjectの管理
	// ==============================================================
	// オブジェクトの識別番号を生成します
	unsigned int generateId(void);

public:
	// 各GameObjectの生成破棄
	Player* createPlayer(float initPosX, float initPosY);
	Enemy* createEnemy(int enemyType);
	SpecialEnemy* createSpecialEnemy(void);
	PlayerBullet* createPlayerBullet(void);
	EnemyBullet* createEnemyBullet(int imageId);
	UpgradeItem* createUpgradeItem(void);
	ExplosionEffect* createExplosionEffect();

	//プレイヤーオブジェクトの取得
	Player* getPlayerObject();

	// 指定のオブジェクトに破棄命令を出す
	void destroyGameObject(GameObject* p);
	void destroyGameObject(unsigned int id);

	// 全てのGameObjectに破棄命令を出す
	void destroyAll(void);

private:
	GameObject* getGameObject(unsigned int id);


	// =========================================================
	// 入力処理
	// =========================================================
private:
	// システムの入力を取得しゲーム用に加工して保持
	void updateInput(void);

public:
	// 押されているか否かを返します
	bool getPressed(ButtonItem item);

	// 今フレームに押されたか否かを返します
	bool getPushed(ButtonItem item);

	// 左スティックの値を[-1,1]の範囲で取得
	float getThumbX();
	float getThumbY();

private:
	bool m_buttons[static_cast<int>(ButtonItem::ButtonCount)];		// フレームのボタンの状態
	bool m_prevButtons[static_cast<int>(ButtonItem::ButtonCount)];	// 前フレームのボタンの状態
	float m_thumbX;									// フレームの左スティックの状態[-1.0, 1.0]
	float m_thumbY;									// フレームの左スティックの状態[-1.0, 1.0]


	// =========================================================
	// 当たり判定
	// =========================================================
private:
	void updateCollision();

//private:
//	unsigned int m_randomSeed;				// 乱数シード
//	std::mt19937 m_engine;					// 乱数生成器

#if COLLISION_VISIBLE
	bool m_collisionVisible;
#endif

	// =========================================================
	// 残機表示
	// =========================================================
private:
	void updatePlayerCountText(bool active = true);

	// =========================================================
	// スコア表示
	// =========================================================
public:
	void addScore(int score);
	int getTotalScore() { return m_totalScore; }
	void notifyUpdateTotalScore();
protected:
	void updateTotalScoreText(bool active = true);

	// =========================================================
	// 自機スピード表示
	// =========================================================
public:
	void notifyUpdateSpeed();
protected:
	void updatePlayerSpeedText(bool active = true);


	// =========================================================
	// 画面遷移
	// =========================================================
protected:
	//タイトルへ移動
	void gotoTitle(); 

	//ゲームオーバーへ移動
	void gotoGameOver();


	// =========================================================
	// GameObjects
	// =========================================================
public:
	class GameObjects
	{
	
	public:
		GameObjects();
		~GameObjects();

		std::unordered_map<unsigned int, GameObject*>::iterator begin();
		std::unordered_map<unsigned int, GameObject*>::iterator end();

		unsigned int generateId(void);

		void addObject(unsigned int id, GameObject* obj);
		GameObject* getGameObject(unsigned int id);
#if COLLISION_VISIBLE
		void update(bool collisionVisible);
#else
		void update();
#endif

		void destroyObject(unsigned int id);
		void destroyAll();

	private:
		unsigned int m_idSeed;										// GameObjectの管理番号の元
		std::unordered_map<unsigned int, GameObject*> m_creates;	// 新規作成GameObject
		std::unordered_map<unsigned int, GameObject*> m_objects;	// 管理中のGameObject
	};
protected:
	GameObjects* m_gameObjects;

};

#endif