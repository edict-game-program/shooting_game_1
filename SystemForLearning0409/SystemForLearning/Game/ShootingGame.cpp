#include "ShootingGame.h"

#include <limits>
//#include <random>
#include <string>

#include <ImageResourceManager.h>
#include <GamePad.h>
#include <Sprite.h>
#include <Text.h>
#include <Collision.h>
#include <CollisionUtil.h>

#include <Sound.h>

#include "Player.h"
#include "Enemy.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "Enemy04.h"
#include "SpecialEnemy.h"
#include "Bullet.h"
#include "UpgradeItem.h"
#include "ExplosionEffect.h"

#define IMAGE_WIEW (0)

static const unsigned int cUiFieldHeight = 40;	// UI表示領域の高さ

// 読み込み画像リスト
static core2d::ImageInfo s_images[ImageCount]
{
	{ ImageBackGroundFar,		"Assets/Images/bg_1.png" },
	{ ImageBackGroundNear,		"Assets/Images/bg_2.png" },
	{ ImagePlayerBomb1,			"Assets/Images/bomb_1.png" },
	{ ImagePlayerBomb2,			"Assets/Images/bomb_2.png" },
	{ ImagePlayerBomb3,			"Assets/Images/bomb_3.png" },
	{ ImagePlayerBomb4,			"Assets/Images/bomb_4.png" },
	{ ImagePlayerBomb5,			"Assets/Images/bomb_5.png" },
	{ ImagePlayerBomb6,			"Assets/Images/bomb_6.png" },
	{ ImageEnemy1_1,			"Assets/Images/enemy_1_1.png" },
	{ ImageEnemy1_2,			"Assets/Images/enemy_1_2.png" },
	{ ImageEnemy2_1,			"Assets/Images/enemy_2_1.png" },
	{ ImageEnemy2_2,			"Assets/Images/enemy_2_2.png" },
	{ ImageEnemy3_1,			"Assets/Images/enemy_3_1.png" },
	{ ImageEnemy3_2,			"Assets/Images/enemy_3_2.png" },
	{ ImageEnemy4_1,			"Assets/Images/enemy_4_1.png" },
	{ ImageEnemy4_2,			"Assets/Images/enemy_4_2.png" },
	{ ImageEnemyBomb1,			"Assets/Images/enemy_bomb_1.png" },
	{ ImageEnemyBomb2,			"Assets/Images/enemy_bomb_2.png" },
	{ ImageEnemyBomb3,			"Assets/Images/enemy_bomb_3.png" },
	{ ImageEnemyBomb4,			"Assets/Images/enemy_bomb_4.png" },
	{ ImageEnemyBomb5,			"Assets/Images/enemy_bomb_5.png" },
	{ ImageEnemyBullet1,		"Assets/Images/enemy_bullet_1.png" },
	{ ImageEnemyBullet2,		"Assets/Images/enemy_bullet_2.png" },
	{ ImageEnemyBullet3,		"Assets/Images/enemy_bullet_3.png" },
	{ ImagePlayerBullet1,		"Assets/Images/player_bullet_1.png" },
	{ ImagePlayerBullet2,		"Assets/Images/player_bullet_2.png" },
	{ ImagePlayerFire1,			"Assets/Images/fire_1.png" },
	{ ImagePlayerFire2,			"Assets/Images/fire_2.png" },
	{ ImagePlayerFire3,			"Assets/Images/fire_3.png" },
	{ ImagePlayerFireBig1,		"Assets/Images/fire_4.png" },
	{ ImagePlayerFireBig2,		"Assets/Images/fire_5.png" },
	{ ImagePlayerFireBig3,		"Assets/Images/fire_6.png" },
	{ ImagePlayerFireSmall1,	"Assets/Images/fire_7.png" },
	{ ImagePlayerFireSmall2,	"Assets/Images/fire_8.png" },
	{ ImagePlayerFireSmall3,	"Assets/Images/fire_9.png" },
	{ ImageObstacle1,			"Assets/Images/obstacle_01.png" },
	{ ImageObstacle2,			"Assets/Images/obstacle_02.png" },
	{ ImageObstacle3,			"Assets/Images/obstacle_03.png" },
	{ ImageObstacle4,			"Assets/Images/obstacle_04.png" },
	{ ImagePlayer,				"Assets/Images/player_1.png" },
	{ ImagePlayerUp1,			"Assets/Images/player_2.png" },
	{ ImagePlayerUp2,			"Assets/Images/player_3.png" },
	{ ImagePlayerUp3,			"Assets/Images/player_4.png" },
	{ ImagePlayerDown1,			"Assets/Images/player_5.png" },
	{ ImagePlayerDown2,			"Assets/Images/player_6.png" },
	{ ImagePlayerDown3,			"Assets/Images/player_7.png" },
	{ ImagePlayerRemainingIcon,	"Assets/Images/player_remaining.png" },
	{ ImagePlayerSub1,			"Assets/Images/player_parts_1.png" },
	{ ImagePlayerSub2,			"Assets/Images/player_parts_2.png" },
	{ ImageSpecialEnemy1,		"Assets/Images/boss_1.png" },
	{ ImageSpecialEnemy2,		"Assets/Images/boss_2.png" },
	{ ImageSpecialEnemy3,		"Assets/Images/boss_3.png" },
	{ ImageItem1,				"Assets/Images/item_1.png" },
	{ ImageItem2,				"Assets/Images/item_2.png" },
	{ ImageItem3,				"Assets/Images/item_3.png" },
};

// コンストラクタ：初期化子リストで変数の初期化
ShootingGame::ShootingGame(unsigned int fps)
	: GameFramework(fps)
	, m_background{ nullptr, nullptr }
	, m_titleText(nullptr)
	, m_indicateText(nullptr)
	, m_overText(nullptr)
	, m_playerCountIcon(nullptr)
	, m_playerCountText(nullptr)
	, m_totalScoreText(nullptr)
	, m_playerSpeedText(nullptr)
	, m_uiField(nullptr)
	, m_playerCount(0)
	, m_playerObjectId(0)
	, m_notifyObjectId(0)
	, m_gameState(GameState::Title)
	, m_stageFrameCount(0)
	, m_stageData(nullptr)
	, m_readPos(0)
	, m_playerDead(false)
	, m_specialEnemyDead(false)
	, m_totalScore(0)
	, m_updateTotalScore(false)
	, m_updatePlayerSpeed(false)
	, m_buttons{}
	, m_prevButtons{}
	, m_thumbX(0.0f)
	, m_thumbY(0.0f)
	//, m_randomSeed(0)
	//, m_engine()
	, m_gameObjects(nullptr)
#if COLLISION_VISIBLE
	, m_collisionVisible(false)
#endif
{
	// 初期化の実処理はinitializeGameで記述
}

ShootingGame::~ShootingGame(void)
{
	// 全ての終了処理をfinalizeGameで記述
}

// 全体の初期化を行う
bool ShootingGame::initializeGame(void)
{

	//
	m_gameObjects = new GameObjects();


	//std::random_device seed;
	//m_randomSeed = seed();					// ランダムシードを記憶
	//m_engine = std::mt19937(m_randomSeed);	// メルセンヌツイスタ疑似乱数生成器を初期化

	// 使用するイメージデータを読み込み
	core2d::ImageResourceManager::instance()->loadImage(s_images, ImageId::ImageCount);

	//サウンドロード
	core2d::SoundManager::instance()->loadWave(GameSeId::WindowOpen, "Assets/SE/01_WindowOpen_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::CursorMove, "Assets/SE/02_Cur_Move_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::Enter, "Assets/SE/03_Cur_Enter_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::Cancel, "Assets/SE/04_Cur_Cancel_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::ItemGet, "Assets/SE/05_Item_Get_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::Shot, "Assets/SE/06_Shot_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::SubShot, "Assets/SE/07_SecondWeapon_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::Bomber, "Assets/SE/08_Bomber_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::BossWarning, "Assets/SE/09_Warning.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::BossChargeAttack, "Assets/SE/10_ChargeAttack_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::BossChargeLoop, "Assets/SE/12_Charge_Loop_01.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::BossShot, "Assets/SE/06_Shot_02.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::BossBomber, "Assets/SE/08_Bomber_04.wav");
	core2d::SoundManager::instance()->loadWave(GameSeId::GameOver, "Assets/SE/11_GameOver_01.wav");

	// 遠景
	m_background[0] = new core2d::Sprite(ImageBackGroundFar);
	m_background[0]->setPriority(static_cast<unsigned int>(DrawPriority::BgFar));
	m_background[0]->setPosition(320.0f, 240.0f);
	m_background[0]->setScrollAnim(0.0f, 0.0f, 0.001f, 0.0f);
	// 近景
	m_background[1] = new core2d::Sprite(ImageBackGroundNear);
	m_background[1]->setPriority(static_cast<unsigned int>(DrawPriority::BgNear));
	m_background[1]->setPosition(320.0f, 240.0f);
	m_background[1]->setScrollAnim(0.0f, 0.0f, 0.0015f, 0.0f);

	// タイトル
	m_titleText = new core2d::Text("Shooting Game");
	m_titleText->setPosition(320.f, 300.f);
	m_titleText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_titleText->setFontSize(64);
	m_titleText->setColor(1.0f, 0.7f, 0.0f, 0.9f);

	// 指示
	m_indicateText = new core2d::Text("Push A Button");
	m_indicateText->setPosition(320.f, 200.f);
	m_indicateText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_indicateText->setFontSize(24);
	m_indicateText->setColor(1.0f, 0.7f, 0.0f, 0.9f);

	// オーバー
	m_overText = new core2d::Text();
	m_overText->setPosition(320.f, 300.f);
	m_overText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_overText->setFontSize(64);
	m_overText->setActive(false);


	//ベース
	{
		m_uiField = new core2d::Sprite(640, cUiFieldHeight);
		m_uiField->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_uiField->setPosition(getDisplayWidth() * 0.5f, getDisplayHeight() - static_cast<float>(cUiFieldHeight / 2));
		m_uiField->setMaterialColor(0.0f, 0.4f, 0.6f);
		m_uiField->setActive(false);
	}

	//残機
	{

		m_playerCountIcon = new core2d::Sprite(ImagePlayerRemainingIcon);
		m_playerCountIcon->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_playerCountIcon->setPosition(16.f, 460.f);
		m_playerCountIcon->setScale(2.f, 2.f);
		
		m_playerCountText = new core2d::Text();
		m_playerCountText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_playerCountText->setOriginPosition(core2d::Text::OriginPosition::Left);
		m_playerCountText->setPosition(20.f, 460.f);
		m_playerCountText->setFontSize(20);

		updatePlayerCountText(false);

	}

	//スコア
	{
		m_totalScoreText = new core2d::Text();
		m_totalScoreText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_totalScoreText->setOriginPosition(core2d::Text::OriginPosition::Left);
		m_totalScoreText->setPosition(60, 460.f);
		m_totalScoreText->setFontSize(20);
		m_totalScoreText->setColor(0.f, 1.f, 0.f);

		updateTotalScoreText(false);
	}

	//自機スピード
	{
		m_playerSpeedText = new core2d::Text();
		m_playerSpeedText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_playerSpeedText->setOriginPosition(core2d::Text::OriginPosition::Left);
		m_playerSpeedText->setPosition(320, 460.f);
		m_playerSpeedText->setFontSize(20);
		m_playerSpeedText->setColor(0.f, 1.f, 1.f);

		updatePlayerSpeedText(false);
	}

#if IMAGE_WIEW
	float x = 0;
	float hMax = 0;
	float lineTopY = 480.0f;
	for (int i = 2; i < ImageId::ImageCount; ++i)
	{
		auto sprite = new core2d::Sprite(s_images[i].id);
		float w = 1.5f * sprite->getWidth();
		float h = 1.5f * sprite->getHeight();
		sprite->setScale(1.5f, 1.5f);

		if (x + w> 640.0f)
		{
			lineTopY -= hMax;
			x = 0.0f;
			hMax = 0;
		}
		sprite->setPosition(x + w * 0.5f , lineTopY - h * 0.5f);
		if (h > hMax)
		{
			hMax = h;
		}
		x += w;
	}
#endif

	return true;
}

// 全体の終了処理
void ShootingGame::finalizeGame(void)
{
	for (int i = 0; i < 2; ++i)
	{
		core2d::Sprite::destroy(m_background[i]);
		m_background[i] = nullptr;
	}
	if (m_titleText)
	{
		core2d::Text::destroy(m_titleText);
		m_titleText = nullptr;
	}
	if (m_indicateText)
	{
		core2d::Text::destroy(m_indicateText);
		m_indicateText = nullptr;
	}
	if (m_overText)
	{
		core2d::Text::destroy(m_overText);
		m_overText = nullptr;
	}
	if (m_playerCountText)
	{
		core2d::Text::destroy(m_playerCountText);
		m_playerCountText = nullptr;
	}
	if (m_playerCountIcon)
	{
		core2d::Sprite::destroy(m_playerCountIcon);
		m_playerCountIcon = nullptr;
	}
	if (m_totalScoreText)
	{
		core2d::Text::destroy(m_totalScoreText);
		m_totalScoreText = nullptr;
	}
	if (m_playerSpeedText)
	{
		core2d::Text::destroy(m_playerSpeedText);
		m_playerSpeedText = nullptr;
	}
	if (m_uiField)
	{
		core2d::Sprite::destroy(m_uiField);
		m_uiField = nullptr;
	}

	// オブジェクトを全て破棄
	if (m_gameObjects)
	{
		delete m_gameObjects;
		m_gameObjects = nullptr;
	}

	//サウンドリソース破棄(stopAllSoundsですべてのサウンドを止めてから破棄しないとクラッシュする)
	core2d::SoundManager::instance()->stopAllSounds();
	core2d::SoundManager::instance()->releaseWave(GameSeId::WindowOpen);
	core2d::SoundManager::instance()->releaseWave(GameSeId::CursorMove);
	core2d::SoundManager::instance()->releaseWave(GameSeId::Enter);
	core2d::SoundManager::instance()->releaseWave(GameSeId::Cancel);
	core2d::SoundManager::instance()->releaseWave(GameSeId::ItemGet);
	core2d::SoundManager::instance()->releaseWave(GameSeId::Shot);
	core2d::SoundManager::instance()->releaseWave(GameSeId::SubShot);
	core2d::SoundManager::instance()->releaseWave(GameSeId::Bomber);
	core2d::SoundManager::instance()->releaseWave(GameSeId::BossWarning);
	core2d::SoundManager::instance()->releaseWave(GameSeId::BossChargeAttack);
	core2d::SoundManager::instance()->releaseWave(GameSeId::BossChargeLoop);
	core2d::SoundManager::instance()->releaseWave(GameSeId::BossShot);
	core2d::SoundManager::instance()->releaseWave(GameSeId::BossBomber);
	core2d::SoundManager::instance()->releaseWave(GameSeId::GameOver);

	// 画像リソース破棄
	core2d::ImageResourceManager::instance()->unloadImage(s_images, ImageId::ImageCount);
}


// 毎フレームの更新処理
void ShootingGame::updateGame(void)
{
	// 入力を更新
	updateInput();

#if COLLISION_VISIBLE
	if (getPushed(ButtonItem::Back))
	{
		m_collisionVisible = !m_collisionVisible;
	}
#endif

	// 新規GameObjectを追加
#if COLLISION_VISIBLE
	m_gameObjects->update(m_collisionVisible);
#else
	m_gameObjects->update();
#endif

	updateCollision();

	// ゲームシステムの更新処理
	switch (getGameState())
	{
	case GameState::Title:
		if (getPushed(ButtonItem::A))
		{
			core2d::SoundManager::instance()->startSe(GameSeId::Enter);

			setGameState(GameState::MainStage);
			// プレイヤーを作成
			Player* player = createPlayer(64, 240);
			m_playerObjectId = player->getId();

			// ステージを初期化
			m_stageFrameCount = 0;
			m_readPos = 0;
			m_stageData = getStageData(StageIndex::Stage1);
			m_playerCount = 2;

			m_playerDead = false;
			m_specialEnemyDead = false;

			m_totalScore = 0;

			//残機表示
			updatePlayerCountText(true);

			//スコア表示
			updateTotalScoreText(true);

			//スピード表示
			updatePlayerSpeedText(true);

			// 表示領域表示
			m_uiField->setActive();

			// 不要なものを非表示
			m_titleText->setActive(false);
			m_indicateText->setActive(false);
			m_overText->setActive(false);
		}
		break;

	case GameState::MainStage:{
		// オブジェクトを生成
		FrameKey key = createObjectFromStageData(m_stageFrameCount++);
		// ステージが終了したのでボスステージへ移行
		if (key == FrameKey::End)
		{
			setGameState(GameState::BossStage);
			m_stageFrameCount = 0;
			m_readPos = 0;
			m_stageData = getStageData(StageIndex::Boss);
			break;
		}

		// プレイヤーの撃墜を検知した場合
		if (m_playerDead)
		{
			m_playerDead = false;

			m_playerCount -= 1;
			if (m_playerCount < 0)
			{
				gotoGameOver();
			}
			else
			{
				auto player = getGameObject(m_playerObjectId);
				player->setDestroy();

				player = createPlayer(64, 240);
				m_playerObjectId = player->getId();

				updatePlayerCountText(true);
				updateTotalScoreText(true);
				updatePlayerSpeedText(true);
			}
		}

		if (m_updateTotalScore)
		{
			updateTotalScoreText(true);
			m_updateTotalScore = false;
		}

		if (m_updatePlayerSpeed)
		{
			updatePlayerSpeedText(true);
			m_updatePlayerSpeed = false;
		}

		// DEBUG : 強制タイトル
		if (getPushed(ButtonItem::LeftShoulder))
		{
			gotoTitle();
		}
		// DEBUG : 強制ボスステージ
		else if (getPushed(ButtonItem::RightShoulder))
		{
			SpecialEnemy* boss = createSpecialEnemy();
			core2d::SoundManager::instance()->startSe(GameSeId::BossWarning);
			boss->setPosition(getDisplayWidth() + 64.0f, getDisplayHeight() * 0.5f);

			setGameState(GameState::BossStage);
			m_stageFrameCount = 0;
			m_readPos = 0;
			m_stageData = getStageData(StageIndex::Boss);
		}
		//++m_stageFrameCount;
		break;}

	case GameState::BossStage:{
		FrameKey key = createObjectFromStageData(m_stageFrameCount++);
		// ボス戦終了まで繰り返し
		if (key == FrameKey::End)
		{
			m_stageFrameCount = 0;
			m_readPos = 0;
			break;
		}

		// プレイヤーの撃墜通知を受けた場合
		if (m_playerDead)
		{
			m_playerDead = false;

			m_playerCount -= 1;
			if (m_playerCount < 0)
			{
				gotoGameOver();
			}
			else
			{
				auto player = getGameObject(m_playerObjectId);
				player->setDestroy();

				player = createPlayer(64, 240);
				m_playerObjectId = player->getId();

				updatePlayerCountText(true);
				updateTotalScoreText(true);
				updatePlayerSpeedText(true);
			}
		}
		// ボス撃破
		else if(m_specialEnemyDead)
		{
			setGameState(GameState::DefeatBoss);
			m_stageFrameCount = 0;
		}

		if (m_updateTotalScore)
		{
			updateTotalScoreText(true);
			m_updateTotalScore = false;
		}

		if (m_updatePlayerSpeed)
		{
			updatePlayerSpeedText(true);
			m_updatePlayerSpeed = false;
		}

		// DEBUG : 強制タイトル
		if (getPushed(ButtonItem::LeftShoulder))
		{
			gotoTitle();
		}
		//++m_stageFrameCount;
		break;}

	case GameState::DefeatBoss:
		if (m_stageFrameCount < 300)
		{
			if (m_stageFrameCount % 24 == 0)
			{
				GameObject* object = getGameObject(m_notifyObjectId);
				float x = static_cast<float>(rand() % 128 - 64) + object->getPositionX();
				float y = static_cast<float>(rand() % 128 - 64) + object->getPositionY();

				auto bomb = createExplosionEffect();
				bomb->setPosition(x, y);
				bomb->playOnceDestroy();
				core2d::SoundManager::instance()->startSe(GameSeId::BossBomber);
			}
			++m_stageFrameCount;
		}
		else if (m_stageFrameCount < 420)
		{
			if (m_stageFrameCount == 320)
			{
				GameObject* object = getGameObject(m_notifyObjectId);
				if (object)
				{
					destroyGameObject(m_notifyObjectId);
				}
			}
			++m_stageFrameCount;
		}
		else
		{
			setGameState(GameState::GameClear);
			m_overText->setText("Game Clear");
			m_overText->setActive();
			m_stageFrameCount = 0;
		}
		break;

	case GameState::GameOver:
		if (getPushed(ButtonItem::A) || getPushed(ButtonItem::B) || getPushed(ButtonItem::Start) || getPushed(ButtonItem::LeftShoulder) || getPushed(ButtonItem::RightShoulder))
		{
			gotoTitle();
		}
		break;

	case GameState::GameClear:
		if (getPushed(ButtonItem::A) || getPushed(ButtonItem::B) || getPushed(ButtonItem::Start) || getPushed(ButtonItem::LeftShoulder) || getPushed(ButtonItem::RightShoulder))
		{
			gotoTitle();
		}
		break;

	default:
		break;
	}
}


// ==============================================================
// ゲームの制御
// ==============================================================
void ShootingGame::setGameState(GameState state)
{
	m_gameState = state;
}

ShootingGame::GameState ShootingGame::getGameState(void)
{
	return m_gameState;
}

FrameKey ShootingGame::createObjectFromStageData(int frameCount)
{
	// 読み込み位置のデータを取得
	FrameInfo frameData = m_stageData[m_readPos];
	// データ指定のframeCountになっていたら実行
	if (frameCount >= frameData.frameCount)
	{
		const GroupInfo* group = getGroupData(frameData.groupId);
		for (int i = 0; i < cGroupObjectMax; ++i)
		{
			// 項目を取得
			auto item = group->object[i];
			// GameObject無しで次のループへスキップ
			if (item.id < 0)
			{
				continue;
			}
			// 生成情報を取得
			ObjectInfo data = getObjectData(item.id);
			if (data.objectType == GameObjectType::Enemy)
			{
				//int enemytype = rand() % 4;
				Enemy* enemy = createEnemy(data.behaviorType);
				enemy->setPosition(frameData.x + item.x, frameData.y + item.y);
				enemy->setUpgradeItem(data.itemType);
			}
			else if (data.objectType == GameObjectType::SpecialEnemy)
			{
				SpecialEnemy* boss = createSpecialEnemy();
				boss->setPosition(frameData.x + item.x, frameData.y + item.y);
				core2d::SoundManager::instance()->startSe(GameSeId::BossWarning);
			}
		}
		// 読み込み位置を進める
		++m_readPos;
		// 設定されたキーを返す
		return frameData.key;
	}
	// 何もなしのキーを返す
	return FrameKey::None;
}

void ShootingGame::notifyPlayerDead(void)
{
	m_playerDead = true;
}

void ShootingGame::notifySpecialEnemyDead(unsigned int objectId)
{
	m_notifyObjectId = objectId;
	m_specialEnemyDead = true;
}

float ShootingGame::getAvalableDisplayWidth(void)
{
	return getDisplayWidth();
}

float ShootingGame::getAvalableDisplayHeight(void)
{
	return getDisplayHeight() - static_cast<float>(cUiFieldHeight);
}

// ==============================================================
// MainGame内オブジェクトの生成破棄
// ==============================================================
unsigned int ShootingGame::generateId()
{
	return m_gameObjects->generateId();
}

Player* ShootingGame::createPlayer(float initPosX, float initPosY)
{
	// Playerのオブジェクトを確保
	auto p = new Player(this, initPosX, initPosY);
	// 確保に失敗したらnullptrを返す
	if (!p)
	{
		return nullptr;
	}
	// 識別番号を取得してオブジェクトに設定
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(PlayerTag);
	// 新規生成コンテナに追加
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	// オブジェクトを返す
	return p;
}

Enemy* ShootingGame::createEnemy(int enemyType)
{
	//auto p = new Enemy(this);
	Enemy* p = nullptr;

	switch (enemyType)
	{
	default:
	case 0:
		p = new Enemy01(this);
		break;

	case 1:
		p = new Enemy02(this);
		break;

	case 2:
		p = new Enemy03(this);
		break;

	case 3:
		p = new Enemy04(this);
		break;
	}

	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(EnemyTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

SpecialEnemy* ShootingGame::createSpecialEnemy(void)
{
	auto p = new SpecialEnemy(this);
	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(SpecialEnemyTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

PlayerBullet* ShootingGame::createPlayerBullet(void)
{
	auto p = new PlayerBullet(this);
	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(PlayerBulletTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

EnemyBullet* ShootingGame::createEnemyBullet(int imageId)
{
	auto p = new EnemyBullet(this , imageId);
	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(EnemyBulletTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

UpgradeItem* ShootingGame::createUpgradeItem(void)
{
	auto p = new UpgradeItem(this);
	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(UpgradeItemTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

ExplosionEffect* ShootingGame::createExplosionEffect()
{
	auto p = new ExplosionEffect(this);
	if (!p)
	{
		return nullptr;
	}
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(UpgradeItemTag);
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	return p;
}

Player* ShootingGame::getPlayerObject()
{
	Player* playerObject = static_cast<Player*>(getGameObject(m_playerObjectId));

	return playerObject;
}

void ShootingGame::destroyGameObject(GameObject* p)
{
	// 破棄状態にする
	// 次回のゲームの更新でdeleteされます
	p->setDestroy();
}

void ShootingGame::destroyGameObject(unsigned int id)
{
	m_gameObjects->destroyObject(id);
}

void ShootingGame::destroyAll(void)
{
	m_gameObjects->destroyAll();
}

GameObject* ShootingGame::getGameObject(unsigned int id)
{
	return m_gameObjects->getGameObject(id);
}

// ================================================================
// 入力関係
// ================================================================
void ShootingGame::updateInput(void)
{
	auto pad = core2d::GamePad::instance();
	if (!pad->isActive())
	{
		// 値をクリア
		for (int i = 0; i < static_cast<int>(ButtonItem::ButtonCount); ++i)
		{
			m_prevButtons[i] = false;
			m_buttons[i] = false;
		}
		m_thumbX = 0.0f;
		m_thumbY = 0.0f;
		return;
	}

	// 前フレームの入力を保存
	for (int i = 0; i < static_cast<int>(ButtonItem::ButtonCount); ++i)
	{
		m_prevButtons[i] = m_buttons[i];
	}

	// 現在のフレームの入力を取得
	m_buttons[static_cast<int>(ButtonItem::A)]				= pad->isButtonDown(XINPUT_GAMEPAD_A);
	m_buttons[static_cast<int>(ButtonItem::B)]				= pad->isButtonDown(XINPUT_GAMEPAD_B);
	m_buttons[static_cast<int>(ButtonItem::X)]				= pad->isButtonDown(XINPUT_GAMEPAD_X);
	m_buttons[static_cast<int>(ButtonItem::Y)]				= pad->isButtonDown(XINPUT_GAMEPAD_Y);
	m_buttons[static_cast<int>(ButtonItem::Start)]			= pad->isButtonDown(XINPUT_GAMEPAD_START);
	m_buttons[static_cast<int>(ButtonItem::Back)]			= pad->isButtonDown(XINPUT_GAMEPAD_BACK);
	m_buttons[static_cast<int>(ButtonItem::Up)]				= pad->isButtonDown(XINPUT_GAMEPAD_DPAD_UP);
	m_buttons[static_cast<int>(ButtonItem::Down)]			= pad->isButtonDown(XINPUT_GAMEPAD_DPAD_DOWN);
	m_buttons[static_cast<int>(ButtonItem::Left)]			= pad->isButtonDown(XINPUT_GAMEPAD_DPAD_LEFT);
	m_buttons[static_cast<int>(ButtonItem::Right)]			= pad->isButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT);
	m_buttons[static_cast<int>(ButtonItem::LeftShoulder)]	= pad->isButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER);
	m_buttons[static_cast<int>(ButtonItem::RightShoulder)]	= pad->isButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER);

	// 誤作動を防ぐため微細な値を切り捨て
	short thumbX = pad->getLeftThumbX();
	if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < thumbX && thumbX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		thumbX = 0;
	}
	short thumbY = pad->getLeftThumbY();
	if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < thumbY && thumbY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		thumbY = 0;
	}

	// 入力値をshortからfloatに変換して[-1, 1]に納める
	float denominator = static_cast<float>(SHRT_MIN);
	m_thumbX = static_cast<float>(thumbX) / -denominator;
	m_thumbY = static_cast<float>(thumbY) / -denominator;
}

bool ShootingGame::getPressed(ButtonItem item)
{
	return m_buttons[static_cast<int>(item)];
}

bool ShootingGame::getPushed(ButtonItem item)
{
	return m_buttons[static_cast<int>(item)] && !m_prevButtons[static_cast<int>(item)];
}

float ShootingGame::getThumbX()
{
	return m_thumbX;
}

float ShootingGame::getThumbY()
{
	return m_thumbY;
}

// =========================================================
// 当たり判定
// =========================================================
void ShootingGame::updateCollision()
{
#if 1
	//自機との当たり
	{
		GameObject* playerObject = getGameObject(m_playerObjectId);

		if (playerObject != nullptr
			&& !playerObject->isDestroy())
		{
			for (unsigned int i = 0; i < playerObject->getCollisionNum(); ++i)
			{
				core2d::Collision::CollisionBase* collision1 = playerObject->getCollision(i);
				if (collision1 == nullptr) continue;
				if (collision1->isActive() == false) continue;

				for (auto it = m_gameObjects->begin(); it != m_gameObjects->end(); ++it)
				{
					GameObject* target = it->second;

					if (!target->isActive()) continue;
					if (target->isDestroy()) continue;

					unsigned int tag = target->getTag();

					if (tag == GameObjectTag::EnemyBulletTag
						|| tag == GameObjectTag::EnemyTag
						|| tag == GameObjectTag::SpecialEnemyTag
						|| tag == GameObjectTag::UpgradeItemTag)
					{
						for (unsigned int j = 0; j < target->getCollisionNum(); ++j)
						{
							core2d::Collision::CollisionBase* collision2 = target->getCollision(j);
							if (collision2 == nullptr) continue;
							if (collision2->isActive() == false) continue;

							//衝突確認
							if (core2d::Collision::checkHit(*collision1, *collision2))
							{
								playerObject->onCollision(collision1, collision2, target);
							}
						}
					}

				}
			}
		}
	}

	//自機の弾との当たり判定
	{
		for (auto it1 = m_gameObjects->begin(); it1 != m_gameObjects->end(); ++it1)
		{
			GameObject* object = it1->second;

			if (!object->isActive()) continue;
			if (object->isDestroy()) continue;

			unsigned int tag = object->getTag();

			if (tag != GameObjectTag::PlayerBulletTag) continue;

			for (unsigned int i = 0; i < object->getCollisionNum(); ++i)
			{
				core2d::Collision::CollisionBase* collision1 = object->getCollision(i);
				if (collision1 == nullptr) continue;
				if (collision1->isActive() == false) continue;

				for (auto it2 = m_gameObjects->begin(); it2 != m_gameObjects->end(); ++it2)
				{
					GameObject* target = it2->second;

					if (!target->isActive()) continue;
					if (target->isDestroy()) continue;

					unsigned int tartgetTag = target->getTag();

					if (tartgetTag != GameObjectTag::EnemyTag
						&& tartgetTag != GameObjectTag::SpecialEnemyTag) continue;

					for (unsigned int j = 0; j < target->getCollisionNum(); ++j)
					{
						core2d::Collision::CollisionBase* collision2 = target->getCollision(j);
						if (collision2 == nullptr) continue;
						if (collision2->isActive() == false) continue;

						//衝突確認(相手側に通知する)
						if (core2d::Collision::checkHit(*collision1, *collision2))
						{
							target->onCollision(collision2, collision1, object);
						}
					}

				}
				
			}
		
		}
	}
#endif
}


// =========================================================
// 残機
// =========================================================
void ShootingGame::updatePlayerCountText(bool active)
{
	if (m_playerCountText)
	{
		std::string str = "×";
		str += std::to_string(m_playerCount);

		m_playerCountText->setText(str.c_str());

		m_playerCountText->setActive(active);
	}

	if (m_playerCountIcon)
	{
		m_playerCountIcon->setActive(active);
	}


}

// =========================================================
// スコア
// =========================================================
void ShootingGame::addScore(int score)
{
	m_totalScore += score;
	if (m_totalScore > cTotalScoreMax) m_totalScore = cTotalScoreMax;
	notifyUpdateTotalScore();
}

void ShootingGame::updateTotalScoreText(bool active)
{
	if (m_totalScoreText)
	{
		const int cBufferSize = 32;
		char buffer[cBufferSize];
		ZeroMemory(buffer, cBufferSize);
		sprintf_s(buffer, "Score:%08d", m_totalScore);

		m_totalScoreText->setText(buffer);
		m_totalScoreText->setActive(active);
	}
}

void ShootingGame::notifyUpdateTotalScore()
{
	m_updateTotalScore = true;
}


// =========================================================
// 自機スピード表示
// =========================================================
void ShootingGame::notifyUpdateSpeed()
{
	m_updatePlayerSpeed = true;
}

void ShootingGame::updatePlayerSpeedText(bool active)
{
	if (m_playerSpeedText)
	{
		m_playerSpeedText->setActive(active);

		Player* player = getPlayerObject();
		if (player == nullptr) return;

		const int cBufferSize = 256;
		char buffer[cBufferSize];
		ZeroMemory(buffer, cBufferSize);
		sprintf_s(buffer, "Speed:%d [X:down Y:up]", player->getSpeed());

		m_playerSpeedText->setText(buffer);
		m_playerSpeedText->setActive(active);
	}
}


// =========================================================
// 画面遷移
// =========================================================
void ShootingGame::gotoTitle()
{
	destroyAll();
	setGameState(GameState::Title);
	m_titleText->setActive(true);
	m_indicateText->setActive(true);
	updatePlayerCountText(false);
	updateTotalScoreText(false);
	updatePlayerSpeedText(false);
	m_overText->setActive(false);
	m_uiField->setActive(false);
}

void ShootingGame::gotoGameOver()
{
	destroyAll();
	setGameState(GameState::GameOver);
	m_overText->setText("Game Over");
	m_overText->setActive();

	core2d::SoundManager::instance()->startSe(GameSeId::GameOver);

	updatePlayerCountText(false);
	updateTotalScoreText(false);
	updatePlayerSpeedText(false);

	m_uiField->setActive(false);
}

// =========================================================
// GameObjects
// =========================================================
ShootingGame::GameObjects::GameObjects() :
	m_idSeed(0), m_creates(), m_objects()
{

}

ShootingGame::GameObjects::~GameObjects()
{
	// オブジェクトを全て破棄
	for (auto it = m_creates.begin(); it != m_creates.end(); ++it)
	{
		delete (*it).second;
	}
	m_creates.clear();

	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		delete (*it).second;
	}
	m_objects.clear();
}

std::unordered_map<unsigned int, GameObject*>::iterator ShootingGame::GameObjects::begin()
{
	return m_objects.begin();
}

std::unordered_map<unsigned int, GameObject*>::iterator ShootingGame::GameObjects::end()
{
	return m_objects.end();
}

unsigned int ShootingGame::GameObjects::generateId(void)
{
	// breakが呼ばれるまで無限ループ
	while (1)
	{
		// 既存のものと重複した場合値を変更
		if (m_creates.count(m_idSeed) == 1)
		{
			++m_idSeed;
			// 次のループへスキップ
			continue;
		}
		// 重複がなかったとしてループを抜ける
		break;
	}

	while (1)
	{
		if (m_objects.count(m_idSeed) == 1)
		{
			++m_idSeed;
			continue;
		}
		break;
	}
	// 識別番号を返し番号を進める
	return m_idSeed++;
}

void ShootingGame::GameObjects::addObject(unsigned int id, GameObject* obj)
{
	m_creates.emplace(id, obj);
}

GameObject* ShootingGame::GameObjects::getGameObject(unsigned int id)
{
	auto it = m_objects.find(id);
	if (it == m_objects.end())
	{
		it = m_creates.find(id);
		if (it == m_creates.end())
		{
			return nullptr;
		}
	}

	return it->second;
}

#if COLLISION_VISIBLE
void ShootingGame::GameObjects::update(bool collisionVisible)
#else
void ShootingGame::GameObjects::update()
#endif
{
	// 新規GameObjectを追加
	for (auto it = m_creates.begin(); it != m_creates.end(); ++it)
	{
		(*it).second->onFirstUpdate();
		m_objects.emplace((*it).first, (*it).second);
	}
	m_creates.clear();
	// 破棄命令の設定されているGameObjectを削除
	{
		auto it = m_objects.begin();
		while (it != m_objects.end())
		{
			if ((*it).second->isDestroy())
			{
				delete (*it).second;
				it = m_objects.erase(it);
				continue;
			}
			++it;
		}
	}
	// アクティブなGameObjectを更新
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		if ((*it).second->isActive())
		{
#if COLLISION_VISIBLE
			(*it).second->setCollisionVisible(collisionVisible);
#endif
			(*it).second->update();
		}
	}
}

void ShootingGame::GameObjects::destroyObject(unsigned int id)
{
	// 識別番号のオブジェクトを検索
	auto it = m_creates.find(id);
	if (it != m_creates.end())
	{
		// 破棄状態にして終了
		it->second->setDestroy();
		return;
	}
	it = m_objects.find(id);
	if (it != m_objects.end())
	{
		it->second->setDestroy();
		return;
	}
}

void ShootingGame::GameObjects::destroyAll()
{
	// コンテナに所属する全てのオブジェクトに対して破棄命令を設定
	for (auto it = m_creates.begin(); it != m_creates.end(); ++it)
	{
		it->second->setDestroy();
	}
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		it->second->setDestroy();
	}
}