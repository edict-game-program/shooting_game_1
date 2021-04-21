#include "StageData.h"
#include "ShootingGameDef.h"

// ------------------------------------------------------------------------
// �}�b�v�����f�[�^
// ------------------------------------------------------------------------
// �I�u�W�F�N�g�̌ʃf�[�^
static ObjectInfo s_objectData[] =
{
	// �I�u�W�F�N�g�̎��, �s���p�^�[��, �A�C�e���̎��
	{ GameObjectType::Enemy, 0, UpgradeType::ItemNone  },	// 0
	{ GameObjectType::Enemy, 0, UpgradeType::MainPower },	// 1
	{ GameObjectType::Enemy, 0, UpgradeType::Forward   },	// 2
	{ GameObjectType::Enemy, 0, UpgradeType::Diffusion },	// 3

	{ GameObjectType::Enemy, 1, UpgradeType::ItemNone  },	// 4
	{ GameObjectType::Enemy, 1, UpgradeType::MainPower },	// 5
	{ GameObjectType::Enemy, 1, UpgradeType::Forward   },	// 6
	{ GameObjectType::Enemy, 1, UpgradeType::Diffusion },	// 7

	{ GameObjectType::Enemy, 2, UpgradeType::ItemNone  },	// 8
	{ GameObjectType::Enemy, 2, UpgradeType::MainPower },	// 9
	{ GameObjectType::Enemy, 2, UpgradeType::Forward   },	// 10
	{ GameObjectType::Enemy, 2, UpgradeType::Diffusion },	// 11

	{ GameObjectType::Enemy, 3, UpgradeType::ItemNone  },	// 12
	{ GameObjectType::Enemy, 3, UpgradeType::MainPower },	// 13
	{ GameObjectType::Enemy, 3, UpgradeType::Forward   },	// 14
	{ GameObjectType::Enemy, 3, UpgradeType::Diffusion },	// 15

	{ GameObjectType::SpecialEnemy, 0, UpgradeType::ItemNone }		// 16 �{�X
};

#define ENEMY_01	 (0)
#define ENEMY_02	 (4)
#define ENEMY_03	 (8)
#define ENEMY_04	(12)
#define ENEMY_SP	(16)

#define ITEM_N		 (0)		// None
#define ITEM_P		 (1)		// PowerUp
#define ITEM_F		 (2)		// Forward
#define ITEM_D		 (3)		// Diffusion

// �G�̎�ނƃA�C�e���ŃC���f�b�N�X���Z�o
#define OBJECT_INDEX(enemy,item) (enemy + item)

// GameObject�������L�q
#define NULL_OBJECT {-1, 0.0f, 0.0f}

// �O���[�v�f�[�^
static GroupInfo s_groupData[] =
{
	// (�I�u�W�F�N�g�ԍ�, x, y) x cGroupObjectMax(6)
	// 0 �{�X
	{
		OBJECT_INDEX(ENEMY_SP, ITEM_N), 0.0f, 0.0f,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
	},

	// 1
	{
		OBJECT_INDEX(ENEMY_01, ITEM_N), 0.0f, 0.0f,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT
	},

	// 2
	{
		OBJECT_INDEX(ENEMY_02, ITEM_N), 0.0f, 0.0f,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT,
		NULL_OBJECT
	},

	// 3
	{
		OBJECT_INDEX(ENEMY_01, ITEM_F), 0.0f, 0.0f,		//
		NULL_OBJECT,									//
		NULL_OBJECT,									// 1f
		NULL_OBJECT,									//   4p
		OBJECT_INDEX(ENEMY_04, ITEM_P), 64.0f, -64.0f,	//
		NULL_OBJECT,									//
	},

	// 4
	{
		OBJECT_INDEX(ENEMY_03, ITEM_D), 0.0f, 0.0f,		//
		OBJECT_INDEX(ENEMY_01, ITEM_N), 0.0f, 32.0f,	// 1
		NULL_OBJECT,									// 3d
		NULL_OBJECT,									//
		NULL_OBJECT,									//
		NULL_OBJECT,									//
	},

	// 5
	{
		OBJECT_INDEX(ENEMY_01, ITEM_N), 32.0f, 64.0f,	//   1
		OBJECT_INDEX(ENEMY_01, ITEM_N), 16.0f, 32.0f,	//  1
		OBJECT_INDEX(ENEMY_01, ITEM_N), 0.0f, 0.0f,		// 1
		OBJECT_INDEX(ENEMY_01, ITEM_P), 16.0f, -32.0f,	//  1p
		OBJECT_INDEX(ENEMY_01, ITEM_N), 32.0f, -64.0f,	//   1
		NULL_OBJECT,									//
	},

	// 6
	{
		OBJECT_INDEX(ENEMY_02, ITEM_N), 0.0f, 0.0f,		// 
		OBJECT_INDEX(ENEMY_02, ITEM_N), 16.0f, 32.0f,	//   2
		OBJECT_INDEX(ENEMY_02, ITEM_N), 32.0f, 64.0f,	//     1f
		OBJECT_INDEX(ENEMY_01, ITEM_F), 64.0f, 48.0f,	//  2
		NULL_OBJECT,									// 2
		NULL_OBJECT,									//
	},

	// 7
	{
		OBJECT_INDEX(ENEMY_04, ITEM_N),  0.0f,  200.0f,	// 4
		OBJECT_INDEX(ENEMY_04, ITEM_N), 64.0f, -200.0f,	// 
		OBJECT_INDEX(ENEMY_01, ITEM_N), 32.0f, 64.0f,	//  1   1f
		OBJECT_INDEX(ENEMY_01, ITEM_D), 96.0f, 64.0f,	// 
		NULL_OBJECT,									//
		NULL_OBJECT,									//   4
	},

};

// �b�Ŏw�肵�ăt���[���ɕϊ�(�����͐؂�̂�)
#define SEC2FRAME(sec) (int)(60.0 * sec)

// ���C���X�e�[�W�̍\�����
static FrameInfo s_stageData0[] =
{
	// �����t���[��, �O���[�v�ԍ�, �z�u��_(x,y), �}�b�v�L�[
	{ SEC2FRAME(0),		1, 650.0f, 240.0f, FrameKey::None },
	{ SEC2FRAME(2),		2, 650.0f, 100.0f, FrameKey::None },
	{ SEC2FRAME(4.6),	2, 650.0f, 200.0f, FrameKey::None },
	{ SEC2FRAME(13),	1, 650.0f, 300.0f, FrameKey::None },
	{ SEC2FRAME(20),	2, 650.0f, 150.0f, FrameKey::None },
	{ SEC2FRAME(26),	7, 650.0f, 220.0f, FrameKey::None },
	{ SEC2FRAME(30),	4, 650.0f, 350.0f, FrameKey::None },
	{ SEC2FRAME(35),	6, 650.0f, 300.0f, FrameKey::None },
	{ SEC2FRAME(40),	3, 650.0f, 150.0f, FrameKey::None },
	{ SEC2FRAME(45),	5, 650.0f, 180.0f, FrameKey::None },
	{ SEC2FRAME(50),	2, 650.0f,  50.0f, FrameKey::None },
	{ SEC2FRAME(60),	0, 640.0f, 240.0f, FrameKey::End },	// �{�X�o��
};

// �{�X�X�e�[�W�̍\�����
static FrameInfo s_stageData1[] =
{
	{ SEC2FRAME(10),	1, 650.0f, 100.0f, FrameKey::None },
	{ SEC2FRAME(20),	2, 650.0f, 200.0f, FrameKey::None },
	{ SEC2FRAME(30),	1, 650.0f, 300.0f, FrameKey::None },
	{ SEC2FRAME(40),	2, 650.0f, 240.0f, FrameKey::End },	// �J��Ԃ��|�C���g
};

// ------------------------------------------------------------------------
// �擾�֐�
// ------------------------------------------------------------------------
ObjectInfo getObjectData(int index)
{
	return s_objectData[index];
}

const GroupInfo* getGroupData(int index)
{
	return &s_groupData[index];
}

const FrameInfo* getStageData(StageIndex index)
{
	switch (index)
	{
	case StageIndex::Stage1: return s_stageData0;
	case StageIndex::Boss: return s_stageData1;
	default: return s_stageData0;
	}
}
