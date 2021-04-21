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

static const unsigned int cUiFieldHeight = 40;	// UI�\���̈�̍���

// �ǂݍ��݉摜���X�g
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

// �R���X�g���N�^�F�������q���X�g�ŕϐ��̏�����
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
	// �������̎�������initializeGame�ŋL�q
}

ShootingGame::~ShootingGame(void)
{
	// �S�Ă̏I��������finalizeGame�ŋL�q
}

// �S�̂̏��������s��
bool ShootingGame::initializeGame(void)
{

	//
	m_gameObjects = new GameObjects();


	//std::random_device seed;
	//m_randomSeed = seed();					// �����_���V�[�h���L��
	//m_engine = std::mt19937(m_randomSeed);	// �����Z���k�c�C�X�^�^�������������������

	// �g�p����C���[�W�f�[�^��ǂݍ���
	core2d::ImageResourceManager::instance()->loadImage(s_images, ImageId::ImageCount);

	//�T�E���h���[�h
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

	// ���i
	m_background[0] = new core2d::Sprite(ImageBackGroundFar);
	m_background[0]->setPriority(static_cast<unsigned int>(DrawPriority::BgFar));
	m_background[0]->setPosition(320.0f, 240.0f);
	m_background[0]->setScrollAnim(0.0f, 0.0f, 0.001f, 0.0f);
	// �ߌi
	m_background[1] = new core2d::Sprite(ImageBackGroundNear);
	m_background[1]->setPriority(static_cast<unsigned int>(DrawPriority::BgNear));
	m_background[1]->setPosition(320.0f, 240.0f);
	m_background[1]->setScrollAnim(0.0f, 0.0f, 0.0015f, 0.0f);

	// �^�C�g��
	m_titleText = new core2d::Text("Shooting Game");
	m_titleText->setPosition(320.f, 300.f);
	m_titleText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_titleText->setFontSize(64);
	m_titleText->setColor(1.0f, 0.7f, 0.0f, 0.9f);

	// �w��
	m_indicateText = new core2d::Text("Push A Button");
	m_indicateText->setPosition(320.f, 200.f);
	m_indicateText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_indicateText->setFontSize(24);
	m_indicateText->setColor(1.0f, 0.7f, 0.0f, 0.9f);

	// �I�[�o�[
	m_overText = new core2d::Text();
	m_overText->setPosition(320.f, 300.f);
	m_overText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
	m_overText->setFontSize(64);
	m_overText->setActive(false);


	//�x�[�X
	{
		m_uiField = new core2d::Sprite(640, cUiFieldHeight);
		m_uiField->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_uiField->setPosition(getDisplayWidth() * 0.5f, getDisplayHeight() - static_cast<float>(cUiFieldHeight / 2));
		m_uiField->setMaterialColor(0.0f, 0.4f, 0.6f);
		m_uiField->setActive(false);
	}

	//�c�@
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

	//�X�R�A
	{
		m_totalScoreText = new core2d::Text();
		m_totalScoreText->setPriority(static_cast<unsigned int>(DrawPriority::UI));
		m_totalScoreText->setOriginPosition(core2d::Text::OriginPosition::Left);
		m_totalScoreText->setPosition(60, 460.f);
		m_totalScoreText->setFontSize(20);
		m_totalScoreText->setColor(0.f, 1.f, 0.f);

		updateTotalScoreText(false);
	}

	//���@�X�s�[�h
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

// �S�̂̏I������
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

	// �I�u�W�F�N�g��S�Ĕj��
	if (m_gameObjects)
	{
		delete m_gameObjects;
		m_gameObjects = nullptr;
	}

	//�T�E���h���\�[�X�j��(stopAllSounds�ł��ׂẴT�E���h���~�߂Ă���j�����Ȃ��ƃN���b�V������)
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

	// �摜���\�[�X�j��
	core2d::ImageResourceManager::instance()->unloadImage(s_images, ImageId::ImageCount);
}


// ���t���[���̍X�V����
void ShootingGame::updateGame(void)
{
	// ���͂��X�V
	updateInput();

#if COLLISION_VISIBLE
	if (getPushed(ButtonItem::Back))
	{
		m_collisionVisible = !m_collisionVisible;
	}
#endif

	// �V�KGameObject��ǉ�
#if COLLISION_VISIBLE
	m_gameObjects->update(m_collisionVisible);
#else
	m_gameObjects->update();
#endif

	updateCollision();

	// �Q�[���V�X�e���̍X�V����
	switch (getGameState())
	{
	case GameState::Title:
		if (getPushed(ButtonItem::A))
		{
			core2d::SoundManager::instance()->startSe(GameSeId::Enter);

			setGameState(GameState::MainStage);
			// �v���C���[���쐬
			Player* player = createPlayer(64, 240);
			m_playerObjectId = player->getId();

			// �X�e�[�W��������
			m_stageFrameCount = 0;
			m_readPos = 0;
			m_stageData = getStageData(StageIndex::Stage1);
			m_playerCount = 2;

			m_playerDead = false;
			m_specialEnemyDead = false;

			m_totalScore = 0;

			//�c�@�\��
			updatePlayerCountText(true);

			//�X�R�A�\��
			updateTotalScoreText(true);

			//�X�s�[�h�\��
			updatePlayerSpeedText(true);

			// �\���̈�\��
			m_uiField->setActive();

			// �s�v�Ȃ��̂��\��
			m_titleText->setActive(false);
			m_indicateText->setActive(false);
			m_overText->setActive(false);
		}
		break;

	case GameState::MainStage:{
		// �I�u�W�F�N�g�𐶐�
		FrameKey key = createObjectFromStageData(m_stageFrameCount++);
		// �X�e�[�W���I�������̂Ń{�X�X�e�[�W�ֈڍs
		if (key == FrameKey::End)
		{
			setGameState(GameState::BossStage);
			m_stageFrameCount = 0;
			m_readPos = 0;
			m_stageData = getStageData(StageIndex::Boss);
			break;
		}

		// �v���C���[�̌��Ă����m�����ꍇ
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

		// DEBUG : �����^�C�g��
		if (getPushed(ButtonItem::LeftShoulder))
		{
			gotoTitle();
		}
		// DEBUG : �����{�X�X�e�[�W
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
		// �{�X��I���܂ŌJ��Ԃ�
		if (key == FrameKey::End)
		{
			m_stageFrameCount = 0;
			m_readPos = 0;
			break;
		}

		// �v���C���[�̌��Ēʒm���󂯂��ꍇ
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
		// �{�X���j
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

		// DEBUG : �����^�C�g��
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
// �Q�[���̐���
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
	// �ǂݍ��݈ʒu�̃f�[�^���擾
	FrameInfo frameData = m_stageData[m_readPos];
	// �f�[�^�w���frameCount�ɂȂ��Ă�������s
	if (frameCount >= frameData.frameCount)
	{
		const GroupInfo* group = getGroupData(frameData.groupId);
		for (int i = 0; i < cGroupObjectMax; ++i)
		{
			// ���ڂ��擾
			auto item = group->object[i];
			// GameObject�����Ŏ��̃��[�v�փX�L�b�v
			if (item.id < 0)
			{
				continue;
			}
			// ���������擾
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
		// �ǂݍ��݈ʒu��i�߂�
		++m_readPos;
		// �ݒ肳�ꂽ�L�[��Ԃ�
		return frameData.key;
	}
	// �����Ȃ��̃L�[��Ԃ�
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
// MainGame���I�u�W�F�N�g�̐����j��
// ==============================================================
unsigned int ShootingGame::generateId()
{
	return m_gameObjects->generateId();
}

Player* ShootingGame::createPlayer(float initPosX, float initPosY)
{
	// Player�̃I�u�W�F�N�g���m��
	auto p = new Player(this, initPosX, initPosY);
	// �m�ۂɎ��s������nullptr��Ԃ�
	if (!p)
	{
		return nullptr;
	}
	// ���ʔԍ����擾���ăI�u�W�F�N�g�ɐݒ�
	unsigned int id = generateId();
	p->setId(id);
	p->setTag(PlayerTag);
	// �V�K�����R���e�i�ɒǉ�
	m_gameObjects->addObject(id, p);
	//m_creates.emplace(id, p);
	// �I�u�W�F�N�g��Ԃ�
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
	// �j����Ԃɂ���
	// ����̃Q�[���̍X�V��delete����܂�
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
// ���͊֌W
// ================================================================
void ShootingGame::updateInput(void)
{
	auto pad = core2d::GamePad::instance();
	if (!pad->isActive())
	{
		// �l���N���A
		for (int i = 0; i < static_cast<int>(ButtonItem::ButtonCount); ++i)
		{
			m_prevButtons[i] = false;
			m_buttons[i] = false;
		}
		m_thumbX = 0.0f;
		m_thumbY = 0.0f;
		return;
	}

	// �O�t���[���̓��͂�ۑ�
	for (int i = 0; i < static_cast<int>(ButtonItem::ButtonCount); ++i)
	{
		m_prevButtons[i] = m_buttons[i];
	}

	// ���݂̃t���[���̓��͂��擾
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

	// ��쓮��h�����ߔ��ׂȒl��؂�̂�
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

	// ���͒l��short����float�ɕϊ�����[-1, 1]�ɔ[�߂�
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
// �����蔻��
// =========================================================
void ShootingGame::updateCollision()
{
#if 1
	//���@�Ƃ̓�����
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

							//�Փˊm�F
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

	//���@�̒e�Ƃ̓����蔻��
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

						//�Փˊm�F(���葤�ɒʒm����)
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
// �c�@
// =========================================================
void ShootingGame::updatePlayerCountText(bool active)
{
	if (m_playerCountText)
	{
		std::string str = "�~";
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
// �X�R�A
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
// ���@�X�s�[�h�\��
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
// ��ʑJ��
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
	// �I�u�W�F�N�g��S�Ĕj��
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
	// break���Ă΂��܂Ŗ������[�v
	while (1)
	{
		// �����̂��̂Əd�������ꍇ�l��ύX
		if (m_creates.count(m_idSeed) == 1)
		{
			++m_idSeed;
			// ���̃��[�v�փX�L�b�v
			continue;
		}
		// �d�����Ȃ������Ƃ��ă��[�v�𔲂���
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
	// ���ʔԍ���Ԃ��ԍ���i�߂�
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
	// �V�KGameObject��ǉ�
	for (auto it = m_creates.begin(); it != m_creates.end(); ++it)
	{
		(*it).second->onFirstUpdate();
		m_objects.emplace((*it).first, (*it).second);
	}
	m_creates.clear();
	// �j�����߂̐ݒ肳��Ă���GameObject���폜
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
	// �A�N�e�B�u��GameObject���X�V
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
	// ���ʔԍ��̃I�u�W�F�N�g������
	auto it = m_creates.find(id);
	if (it != m_creates.end())
	{
		// �j����Ԃɂ��ďI��
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
	// �R���e�i�ɏ�������S�ẴI�u�W�F�N�g�ɑ΂��Ĕj�����߂�ݒ�
	for (auto it = m_creates.begin(); it != m_creates.end(); ++it)
	{
		it->second->setDestroy();
	}
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		it->second->setDestroy();
	}
}