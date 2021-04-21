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

// �Q�[���ł̍X�V�P�ʂ�\�����ۃN���X
class GameObject
{
	friend class ShootingGame::GameObjects; //GameObjects::update()����onFirstUpdate���R�[�������邽�߂̃t�����h�N���X

public:
	GameObject(void) = delete;	// �f�t�H���g�R���X�g���N�^���폜
	GameObject(ShootingGame* manager);
	virtual ~GameObject(void);

	// �X�V�����̏������z�֐� ���p����ŃI�[�o�[���C�h���K�{
	virtual void update(void) = 0;

	// ���ʎq�ݒ�E�擾
	void setId(unsigned int id);
	unsigned int getId(void);

	// �C�ӂ̎��ʃ^�O�ݒ�E�擾
	void setTag(unsigned int tag);
	unsigned int getTag(void);

	// �X�V�t���O�̐ݒ�E�擾
	virtual void setActive(bool active = true);
	bool isActive(void);

	// �j����Ԃ̐ݒ�E�擾
	virtual void setDestroy(void);
	bool isDestroy(void);

	// ���W�̐ݒ�E�擾
	void setPosition(float x, float y);
	float getPositionX(void);
	float getPositionY(void);

	// �g�k�̐ݒ�E�擾
	void setScale(float x, float y);
	float getScaleX(void);
	float getScaleY(void);

	// ��]�̐ݒ�E�擾
	void setRotation(float degree);
	float getRotation(void);


	//�R���W������
	unsigned int getCollisionNum();

	//�R���W�����̓o�^
	void addCollision(core2d::Collision::CollisionBase* collision);

	//�R���W�����̓o�^����
	void removeCollision();

	//�R���W�����̎擾
	core2d::Collision::CollisionBase* getCollision(unsigned int index);

	//�ڐG�����ꍇ�ɌĂ΂��B
	//�ڐG���������̃R���W�����A����̃R���W�����A�����GameObject�������Ƃ��ēn�����
	virtual void onCollision(core2d::Collision::CollisionBase* myCollision, core2d::Collision::CollisionBase* targetCollision, GameObject* target){};

protected:
	ShootingGame* manager(void) { return m_manager; }

	//update�̑O�Ɉ�x�����Ă΂��
	virtual void onFirstUpdate() {};

private:
	ShootingGame* m_manager;		// �Ǘ��҂ւ̃A�N�Z�T
	unsigned int m_id;				// �I�u�W�F�N�g�̎��ʔԍ�
	unsigned int m_tag;				// �C�ӂ̎��ʎq
	bool m_active;					// �X�V�t���O
	bool m_destroy;					// �j���t���O

protected:
	float m_positionX, m_positionY;	// ���W
	float m_scaleX, m_scaleY;		// �g�k
	float m_rotation;				// ��]

	std::vector<core2d::Collision::CollisionBase*> m_collisions; //�R���W�����B�P�̃I�u�W�F�N�g�ŕ����̓�����������Ƃ�����

#if COLLISION_VISIBLE
public:
	void setCollisionVisible(bool flag) { m_collisionVisible = flag; }
	bool getCollisionVisible(void) { return m_collisionVisible; }
private:
	bool m_collisionVisible;
#endif
};

#endif