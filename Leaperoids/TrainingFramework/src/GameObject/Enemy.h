#pragma once 
#include "Sprite2D.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "ResourceManagers.h"

class Enemy : public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Enemy();
	void	Update(GLfloat deltaTime);
	int		GetHP();
	void	SetHP(int);
	void	EnemyAttack();
	bool	isActive = false;
	void	Reset();
	void	SetTexture(std::shared_ptr<Texture> texture);
	void	SetBulletPool(std::shared_ptr<ObjectPool<Bullet>>);
	void	SetVelocity(Vector2);
	void	Init();

private:
	int		m_hp;
	float	m_velocity = 150;
	float	m_currentTime = 0;
	float	m_ShootInterval = 1;
	std::shared_ptr<ObjectPool<Bullet>>	m_bulletPool;
};
