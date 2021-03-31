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
	Vector2 pos = Get2DPosition();
	if (y - pos.y < 0)
		this->Set2DRotation(atanf((x - pos.x) / (y - pos.y)));
	else
		this->Set2DRotation(atanf((x - pos.x) / (y - pos.y)) - PI);
}

void Player::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (bIsPresseded)
	{
		if (key == KEY_MOVE_LEFT)
			horizontalInput = -1;

		if (key == KEY_MOVE_RIGHT)
			horizontalInput = 1;

		if (key == KEY_MOVE_BACKWORD)
			verticalInput = 1;

		if (key == KEY_MOVE_FORWORD)
			verticalInput = -1;

		/*if (key == 'z' || key == 'Z')
			rotationInput = -1;
		if (key == 'c' || key == 'C')
		{
			rotationInput = 0;
			std::cout << m_2DRotation << std::endl;
		}*/
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
	//this->Set2DRotation(m_2DRotation + rotationInput * 3.14 / 8 * deltaTime);
}