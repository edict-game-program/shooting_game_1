#pragma once
#ifndef __SHOOTINGGAMEDEF_HEADER__
#define __SHOOTINGGAMEDEF_HEADER__

#ifdef _DEBUG
#define COLLISION_VISIBLE (0)
#else
#define COLLISION_VISIBLE (0)
#endif

// オブジェクト識別タグ
enum GameObjectTag : unsigned int
{
	PlayerTag,
	PlayerBulletTag,
	EnemyTag,
	EnemyBulletTag,
	SpecialEnemyTag,
	UpgradeItemTag,
};

// 使用する画像列挙体
enum ImageId : int
{
	ImageBackGroundFar = 0,
	ImageBackGroundNear,
	ImagePlayerBomb1,		// 自機撃墜エフェクト
	ImagePlayerBomb2,
	ImagePlayerBomb3,
	ImagePlayerBomb4,
	ImagePlayerBomb5,
	ImagePlayerBomb6,
	ImageEnemy1_1,
	ImageEnemy1_2,
	ImageEnemy2_1,
	ImageEnemy2_2,
	ImageEnemy3_1,
	ImageEnemy3_2,
	ImageEnemy4_1,
	ImageEnemy4_2,
	ImageEnemyBomb1,		// 敵撃墜エフェクト
	ImageEnemyBomb2,
	ImageEnemyBomb3,
	ImageEnemyBomb4,
	ImageEnemyBomb5,
	ImageEnemyBullet1,
	ImageEnemyBullet2,
	ImageEnemyBullet3,
	ImagePlayerBullet1,
	ImagePlayerBullet2,
	ImagePlayerFire1,
	ImagePlayerFire2,
	ImagePlayerFire3,
	ImagePlayerFireBig1,
	ImagePlayerFireBig2,
	ImagePlayerFireBig3,
	ImagePlayerFireSmall1,
	ImagePlayerFireSmall2,
	ImagePlayerFireSmall3,
	ImageObstacle1,
	ImageObstacle2,
	ImageObstacle3,
	ImageObstacle4,
	ImagePlayer,
	ImagePlayerUp1,
	ImagePlayerUp2,
	ImagePlayerUp3,
	ImagePlayerDown1,
	ImagePlayerDown2,
	ImagePlayerDown3,
	ImagePlayerRemainingIcon,
	ImagePlayerSub1,
	ImagePlayerSub2,
	ImageSpecialEnemy1,
	ImageSpecialEnemy2,
	ImageSpecialEnemy3,
	ImageItem1,
	ImageItem2,
	ImageItem3,

	ImageCount
};

// 入力を定義
enum class ButtonItem : int
{
	A = 0,
	B,
	X,
	Y,
	Start,
	Back,
	Up,
	Down,
	Left,
	Right,
	LeftShoulder,
	RightShoulder,

	ButtonCount,
};

// アイテムによる強化の種類
enum UpgradeType : int
{
	MainPower = 0,	// メイン
	Forward,		// 補助武器１
	Diffusion,		// 補助武器２

	ItemNone = -1,
};


//ゲームSEのID。自由に追加してみましょう。
enum GameSeId : int
{
	WindowOpen = 0,	//ウインドウ表示音
	CursorMove,		//カーソル移動音
	Enter,			//決定音
	Cancel,			//キャンセル
	ItemGet,		//アイテムゲット
	Shot,			//弾発射
	SubShot,		//補助武器弾発射
	Bomber,			//撃破音
	BossWarning,		//ボス登場
	BossChargeAttack,	//ボス突進攻撃音
	BossChargeLoop,		//ボス突進前チャージ音
	BossShot,			//ボス弾発射
	BossBomber,			//ボス爆破音
	GameOver,			//ゲームオーバー

};


//描画優先優先(0～100。0が一番手前)
enum class DrawPriority : unsigned int
{
	Mask = 0,		//マスク

	UI	 = 10,		//UI

	Effect = 20,	//エフェクト

	Player = 30,	//プレイヤーオブジェクト
	Enemy,			//敵

	Bullet = 40,	//弾

	Item = 50,		//アイテム

	BgNear = 95,	//背景(近景)
	BgFar = 100,	//背景(遠景)

};

// 算術計算用定義
static const float cPi = 3.14159265f;
#define RAD_TO_DEG(radian) ((radian) / cPi * 180.0f)
#define DEG_TO_RAD(degree) ((degree) / 180.0f * cPi)

//ゲームスコア
static const int cTotalScoreMax = 99999999;

#endif