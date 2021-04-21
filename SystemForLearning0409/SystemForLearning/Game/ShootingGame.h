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

// �V���[�e�B���O�Q�[���N���X
class ShootingGame : public core2d::GameFramework
{
public:
	ShootingGame(void) = delete;
	ShootingGame(unsigned int fps);
	virtual ~ShootingGame(void);

private:
	// ���z�֐����I�[�o�[���C�h
	bool initializeGame(void) final;
	void finalizeGame(void) final;
	void updateGame(void) final;

	// ==============================================================
	// �Q�[���̐���
	// ==============================================================
private:
	// ��Ԃ�\���񋓑�
	enum class GameState
	{
		Title,
		MainStage,
		BossStage,
		DefeatBoss,
		GameOver,
		GameClear,
	};
	// �Q�[����Ԃ�ݒ�E�擾
	void setGameState(GameState state);
	GameState getGameState(void);

	// �X�e�[�W�f�[�^����I�u�W�F�N�g�𐶐�
	FrameKey createObjectFromStageData(int frameCount);

public:
	// �v���C���[�����񂾂��Ƃ�ʒm
	void notifyPlayerDead(void);
	// �{�X�L�����̌��j��ʒm
	void notifySpecialEnemyDead(unsigned int objectId);

	// ���p�\�ȉ�ʃT�C�Y���擾
	float getAvalableDisplayWidth(void);
	float getAvalableDisplayHeight(void);

private:
	core2d::Sprite* m_background[2];		// �w�i�p�X�v���C�g
	core2d::Text* m_titleText;
	core2d::Text* m_indicateText;
	core2d::Text* m_overText;
	core2d::Sprite* m_playerCountIcon;		// �c�@�\���A�C�R��
	core2d::Text* m_playerCountText;		// �c�@�\���e�L�X�g
	core2d::Text* m_totalScoreText;			// ���_�\��
	core2d::Text* m_playerSpeedText;		// ���@�X�s�[�h�e�L�X�g
	core2d::Sprite* m_uiField;				// �㕔UI�\���̈�p�X�v���C�g
	unsigned int m_playerObjectId;			// ���[�U�[����L����ID
	unsigned int m_notifyObjectId;			// �ʒm�𑗂��Ă���Object��ID
	int m_playerCount;						// �v���C���[�c�@��
	GameState m_gameState;					// �Q�[�����
	unsigned int m_stageFrameCount;			// MainStage�ł̌o�߃t���[����
	const FrameInfo* m_stageData;			// �X�e�[�W�f�[�^�z��ւ̃|�C���^
	int m_readPos;							// �X�e�[�W�f�[�^�̓ǂݍ��݈ʒu
	bool m_playerDead;
	bool m_specialEnemyDead;

	int m_totalScore;						//�X�R�A
	bool m_updateTotalScore;

	bool m_updatePlayerSpeed;

	// ==============================================================
	// GameObject�̊Ǘ�
	// ==============================================================
	// �I�u�W�F�N�g�̎��ʔԍ��𐶐����܂�
	unsigned int generateId(void);

public:
	// �eGameObject�̐����j��
	Player* createPlayer(float initPosX, float initPosY);
	Enemy* createEnemy(int enemyType);
	SpecialEnemy* createSpecialEnemy(void);
	PlayerBullet* createPlayerBullet(void);
	EnemyBullet* createEnemyBullet(int imageId);
	UpgradeItem* createUpgradeItem(void);
	ExplosionEffect* createExplosionEffect();

	//�v���C���[�I�u�W�F�N�g�̎擾
	Player* getPlayerObject();

	// �w��̃I�u�W�F�N�g�ɔj�����߂��o��
	void destroyGameObject(GameObject* p);
	void destroyGameObject(unsigned int id);

	// �S�Ă�GameObject�ɔj�����߂��o��
	void destroyAll(void);

private:
	GameObject* getGameObject(unsigned int id);


	// =========================================================
	// ���͏���
	// =========================================================
private:
	// �V�X�e���̓��͂��擾���Q�[���p�ɉ��H���ĕێ�
	void updateInput(void);

public:
	// ������Ă��邩�ۂ���Ԃ��܂�
	bool getPressed(ButtonItem item);

	// ���t���[���ɉ����ꂽ���ۂ���Ԃ��܂�
	bool getPushed(ButtonItem item);

	// ���X�e�B�b�N�̒l��[-1,1]�͈̔͂Ŏ擾
	float getThumbX();
	float getThumbY();

private:
	bool m_buttons[static_cast<int>(ButtonItem::ButtonCount)];		// �t���[���̃{�^���̏��
	bool m_prevButtons[static_cast<int>(ButtonItem::ButtonCount)];	// �O�t���[���̃{�^���̏��
	float m_thumbX;									// �t���[���̍��X�e�B�b�N�̏��[-1.0, 1.0]
	float m_thumbY;									// �t���[���̍��X�e�B�b�N�̏��[-1.0, 1.0]


	// =========================================================
	// �����蔻��
	// =========================================================
private:
	void updateCollision();

//private:
//	unsigned int m_randomSeed;				// �����V�[�h
//	std::mt19937 m_engine;					// ����������

#if COLLISION_VISIBLE
	bool m_collisionVisible;
#endif

	// =========================================================
	// �c�@�\��
	// =========================================================
private:
	void updatePlayerCountText(bool active = true);

	// =========================================================
	// �X�R�A�\��
	// =========================================================
public:
	void addScore(int score);
	int getTotalScore() { return m_totalScore; }
	void notifyUpdateTotalScore();
protected:
	void updateTotalScoreText(bool active = true);

	// =========================================================
	// ���@�X�s�[�h�\��
	// =========================================================
public:
	void notifyUpdateSpeed();
protected:
	void updatePlayerSpeedText(bool active = true);


	// =========================================================
	// ��ʑJ��
	// =========================================================
protected:
	//�^�C�g���ֈړ�
	void gotoTitle(); 

	//�Q�[���I�[�o�[�ֈړ�
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
		unsigned int m_idSeed;										// GameObject�̊Ǘ��ԍ��̌�
		std::unordered_map<unsigned int, GameObject*> m_creates;	// �V�K�쐬GameObject
		std::unordered_map<unsigned int, GameObject*> m_objects;	// �Ǘ�����GameObject
	};
protected:
	GameObjects* m_gameObjects;

};

#endif