#pragma once
#ifndef __SHOOTINGGAMEDEF_HEADER__
#define __SHOOTINGGAMEDEF_HEADER__

#ifdef _DEBUG
#define COLLISION_VISIBLE (0)
#else
#define COLLISION_VISIBLE (0)
#endif

// �I�u�W�F�N�g���ʃ^�O
enum GameObjectTag : unsigned int
{
	PlayerTag,
	PlayerBulletTag,
	EnemyTag,
	EnemyBulletTag,
	SpecialEnemyTag,
	UpgradeItemTag,
};

// �g�p����摜�񋓑�
enum ImageId : int
{
	ImageBackGroundFar = 0,
	ImageBackGroundNear,
	ImagePlayerBomb1,		// ���@���ăG�t�F�N�g
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
	ImageEnemyBomb1,		// �G���ăG�t�F�N�g
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

// ���͂��`
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

// �A�C�e���ɂ�鋭���̎��
enum UpgradeType : int
{
	MainPower = 0,	// ���C��
	Forward,		// �⏕����P
	Diffusion,		// �⏕����Q

	ItemNone = -1,
};


//�Q�[��SE��ID�B���R�ɒǉ����Ă݂܂��傤�B
enum GameSeId : int
{
	WindowOpen = 0,	//�E�C���h�E�\����
	CursorMove,		//�J�[�\���ړ���
	Enter,			//���艹
	Cancel,			//�L�����Z��
	ItemGet,		//�A�C�e���Q�b�g
	Shot,			//�e����
	SubShot,		//�⏕����e����
	Bomber,			//���j��
	BossWarning,		//�{�X�o��
	BossChargeAttack,	//�{�X�ːi�U����
	BossChargeLoop,		//�{�X�ːi�O�`���[�W��
	BossShot,			//�{�X�e����
	BossBomber,			//�{�X���j��
	GameOver,			//�Q�[���I�[�o�[

};


//�`��D��D��(0�`100�B0����Ԏ�O)
enum class DrawPriority : unsigned int
{
	Mask = 0,		//�}�X�N

	UI	 = 10,		//UI

	Effect = 20,	//�G�t�F�N�g

	Player = 30,	//�v���C���[�I�u�W�F�N�g
	Enemy,			//�G

	Bullet = 40,	//�e

	Item = 50,		//�A�C�e��

	BgNear = 95,	//�w�i(�ߌi)
	BgFar = 100,	//�w�i(���i)

};

// �Z�p�v�Z�p��`
static const float cPi = 3.14159265f;
#define RAD_TO_DEG(radian) ((radian) / cPi * 180.0f)
#define DEG_TO_RAD(degree) ((degree) / 180.0f * cPi)

//�Q�[���X�R�A
static const int cTotalScoreMax = 99999999;

#endif