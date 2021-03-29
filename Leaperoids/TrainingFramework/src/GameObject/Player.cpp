#include "Player.h"


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_lives = 6;

}

Player::~Player()
{
}

void Player::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	if ((x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		
	}
}

void Player::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (bIsPresseded)
	{
		if (key == 'A' || key == 'a')
			horizontalInput = -1;

		if (key == 'D' || key == 'd')
			horizontalInput = 1;

		if (key == 'S' || key == 's')
			verticalInput = 1;

		if (key == 'W' || key == 'w')
			verticalInput = -1;

		if (key == 'z' || key == 'Z')
			rotationInput = -1;
		if (key == 'c' || key == 'C')
		{
			rotationInput = 0;
			std::cout << m_2DRotation << std::endl;
		}
	}

	else
	{
		horizontalInput = verticalInput = 0;
	}
}

int Player::GetLives()
{
	return this->m_lives;
}

void Player::SetLives(int lives)
{
	this->m_lives = lives;
}

void Player::Update(GLfloat deltaTime)
{
	this->Set2DPosition(m_Vec2DPos.x + horizontalInput * m_velocity * deltaTime,
		m_Vec2DPos.y + verticalInput * m_velocity * deltaTime);
	this->Set2DRotation(m_2DRotation + rotationInput * 3.14 / 8 * deltaTime);
}