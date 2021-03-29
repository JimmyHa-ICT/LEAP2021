#include "Enemy.h"


Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture), m_hp(2)
{
}

Enemy::~Enemy()
{
}

int Enemy::GetHP()
{
	return this->m_hp;
}

void Enemy::SetHP(int hp)
{
	this->m_hp = hp;
}

void Enemy::Update(GLfloat deltaTime)
{
	m_currentTime += deltaTime;

	if (m_currentTime > m_ShootInterval)
	{
		EnemyAttack();
		m_currentTime -= m_ShootInterval;
	}

	if (this->m_hp <= 0)
		this->Reset();
}

void Enemy::EnemyAttack()
{
	auto bullet = m_bulletPool->GetObjectT();
	bullet->Set2DPosition(Get2DPosition() + Vector2(sinf(Get2DRotation()) * 80, cosf(Get2DRotation()) * -80));
	bullet->SetVelocity(Vector2(sinf(Get2DRotation()), cosf(Get2DRotation())) * -500);
	bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("laserRed02"));
	bullet->SetSize(13, 37);
}

void Enemy::Reset()
{
	Set2DPosition(0, 0);
	isActive = false;
}

void Enemy::SetTexture(std::shared_ptr<Texture> texture)
{
	m_pTexture = texture;
}

void Enemy::SetBulletPool(std::shared_ptr<ObjectPool<Bullet>> bulletPool)
{
	m_bulletPool = bulletPool;
}