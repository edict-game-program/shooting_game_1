#pragma once
#ifndef __STAGEDATA_HEADER__
#define __STAGEDATA_HEADER__

// ��̃O���[�v�Ɋ܂ނ��Ƃ̂ł���I�u�W�F�N�g�̍ő吔
static const int cGroupObjectMax = 6;

// �t���[���̓���
enum class FrameKey : int
{
	None = 0,
	End = 1
};

// GameObject�̎��
enum class GameObjectType : int
{
	Player,
	Enemy,
	SpecialEnemy,
};

// �X�e�[�W�ԍ�
enum class StageIndex : int
{
	Stage1,
	Boss,
};

// �P�̃I�u�W�F�N�g���\����
struct ObjectInfo
{
	GameObjectType objectType;		// �����I�u�W�F�N�g�̎��
	// �ȉ��U�R�G�ł̂ݓK�p
	int behaviorType;				// �U�R�G�̍s���p�^�[��
	int itemType;					// �����A�C�e���̗L���F0:���A1:�啐�틭���A2:�⏕�P�؂�ւ��Ƌ����A3:�⏕�Q�؂�ւ��Ƌ���
};

// �O���[�v���\����
struct GroupInfo
{
	struct Item
	{
		int id;
		float x, y;
	} object[cGroupObjectMax];		// �I�u�W�F�N�g�ԍ��A�z�u�ꏊ(x, y)
};

// �t���[�����\����
struct FrameInfo
{
	int frameCount;					// �Ή��t���[���ԍ�
	int groupId;					// �z�u����O���[�v�ԍ�
	float x;						// ������_ x
	float y;						// ������_ y
	FrameKey key;					// �����Ȃ����0����ȊO�͔C�ӂ̒l
};

// ------------------------------------------------------------------------
// �擾�֐�
// ------------------------------------------------------------------------
// GameObjet�f�[�^���擾
ObjectInfo getObjectData(int index);

// �O���[�v�f�[�^�ւ̃|�C���^���擾
const GroupInfo* getGroupData(int index);

// �}�b�v�f�[�^(�t���[�����z��)�ւ̃|�C���^���擾
const FrameInfo* getStageData(StageIndex index);

#endif // __GAMEMAP_HEADER__