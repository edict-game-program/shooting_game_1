#include "GameObject.h"

GameObject::GameObject(ShootingGame* manager)
	: m_manager(manager)
	, m_id(0)
	, m_tag(0)
	, m_active(true)
	, m_destroy(false)
	, m_positionX(0.0f)
	, m_positionY(0.0f)
	, m_scaleX(1.0f)
	, m_scaleY(1.0f)
	, m_rotation(0.0f)
#if COLLISION_VISIBLE
	, m_collisionVisible(false)
#endif
{
	m_collisions.clear();
}

GameObject::~GameObject(void)
{
	m_manager = nullptr;

	m_collisions.clear(); //ƒRƒŠƒWƒ‡ƒ“‚Ì”jŠü‚Í“o˜^Œ³‚Å‚·‚é
	
}

void GameObject::setId(unsigned int id)
{
	m_id = id;
}

unsigned int GameObject::getId(void)
{
	return m_id;
}

void GameObject::setTag(unsigned int tag)
{
	m_tag = tag;
}

unsigned int GameObject::getTag(void)
{
	return m_tag;
}

void GameObject::setActive(bool active)
{
	m_active = active;
}

bool GameObject::isActive(void)
{
	return m_active && !m_destroy;
}

void GameObject::setDestroy(void)
{
	m_destroy = true;
}

bool GameObject::isDestroy(void)
{
	return m_destroy;
}

void GameObject::setPosition(float x, float y)
{
	m_positionX = x;
	m_positionY = y;
}

float GameObject::getPositionX(void)
{
	return m_positionX;
}

float GameObject::getPositionY(void)
{
	return m_positionY;
}

void GameObject::setScale(float x, float y)
{
	m_scaleX = x;
	m_scaleY = y;
}

float GameObject::getScaleX(void)
{
	return m_scaleX;
}
float GameObject::getScaleY(void)
{
	return m_scaleY;
}

void GameObject::setRotation(float degree)
{
	m_rotation = degree;
}

float GameObject::getRotation(void)
{
	return m_rotation;
}

unsigned int GameObject::getCollisionNum()
{
	if (m_collisions.empty()) return 0;
	return static_cast<unsigned int>(m_collisions.size());
}

void GameObject::addCollision(core2d::Collision::CollisionBase* collision)
{
	m_collisions.push_back(collision);
}

void GameObject::removeCollision()
{
	m_collisions.clear();
}

core2d::Collision::CollisionBase* GameObject::getCollision(unsigned int number)
{
	return m_collisions[number];
}