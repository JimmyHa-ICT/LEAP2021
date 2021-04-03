#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "Util.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_black");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 150, 50);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
		//exit(0);
	});
	m_listButton.push_back(button);

	//main player
	texture = ResourceManagers::GetInstance()->GetTexture("playerShip3_blue");
	m_player = std::make_shared<Player>(model, shader, texture);
	m_player->Set2DPosition(screenWidth / 2, screenHeight - 100);
	m_player->Set2DRotation(0);
	m_player->SetSize(66, 50);

	// all lives
	for (int i = 0; i < m_player->GetLives(); i++)
	{
		texture = ResourceManagers::GetInstance()->GetTexture("playerLife3_blue");
		auto li = std::make_shared<Sprite2D>(model, shader, texture);
		li->Set2DPosition(25 + 36 * i, 80);
		li->SetSize(32, 26);
		m_liveRenderer.push_back(li);
	}

	//bullet pool
	
	m_bulletPool = std::make_shared<ObjectPool<Bullet>>();


	// enemy pool
	m_enemyPool = std::make_shared<ObjectPool<Enemy>>();
	/*for (int i = 0; i < 5; i++)
	{
		auto l_enemy = m_enemyPool->GetObjectT();
		l_enemy->Set2DPosition(i * 250 + 100, 100);
		l_enemy->Set2DRotation(PI);
		l_enemy->SetSize(93, 84);
		l_enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("enemyBlack1"));
		l_enemy->SetBulletPool(m_bulletPool);
	}*/

	// meteor pool
	m_meteorPool = std::make_shared<ObjectPool<Meteor>>();
	m_meteorPool->StartSpawning(0.5f);

	//sample particle system
	m_particleSystem = std::make_shared<ParticleSystem>();
	m_particleSystem->SetLifeTime(2, 3);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("kenvector_future_thin");
	m_score_text = std::make_shared< Text>(shader, font, Util::ToStringFixedLength(m_currentScore, 6), TEXT_COLOR::RED, 1.0);
	m_score_text->Set2DPosition(Vector2(25, 50));
}

void GSPlay::Exit()
{
	Util::SetFinalScore(m_currentScore);
}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_player->HandleKeyEvent(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}

	//player rotation
	m_player->HandleTouchEvents(x, y, bIsPressed);

	// player shooting
	if (bIsPressed)
	{
		ResourceManagers::GetInstance()->PlaySound("sfx_laser1.ogg");
		auto bullet = m_bulletPool->GetObjectT();
		bullet->Set2DPosition(m_player->Get2DPosition() + 
			Vector2(-50 * sinf(m_player->Get2DRotation()), -50 * cosf(m_player->Get2DRotation())));
		bullet->SetVelocity(Vector2(sinf(m_player->Get2DRotation()), cosf(m_player->Get2DRotation())) * -500);
		bullet->SetTexture(ResourceManagers::GetInstance()->GetTexture("laserRed02"));
		bullet->Set2DRotation(m_player->Get2DRotation());
		bullet->SetSize(13, 37);
	}
}

void GSPlay::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_player->Update(deltaTime);
	m_bulletPool->Update(deltaTime);

	m_enemyPool->Update(deltaTime);
	m_meteorPool->Update(deltaTime);
	
	for (auto enemy : m_enemyPool->GetAllActive())
	{
		for (auto obj : m_bulletPool->GetAllActive())
		{
			if (obj->IsCollided(enemy))
			{
				//std::cout << "Collide!" << std::endl;
				obj->Reset();
				enemy->SetHP(enemy->GetHP() - 1);
			}
		}
	}

	for (auto meteor : m_meteorPool->GetAllActive())
	{
		for (auto obj : m_bulletPool->GetAllActive())
		{
			if (obj->IsCollided(meteor))
			{
				m_particleSystem->Emit("particle", 8, meteor->Get2DPosition());
				obj->Reset();
				meteor->Reset();
				m_currentScore += 10;
				m_score_text->setText(Util::ToStringFixedLength(m_currentScore, 6));
			}
		}

		if (m_player->IsCollided(meteor))
		{
			ResourceManagers::GetInstance()->PlaySound("rollover1.ogg");
			meteor->Reset();
			m_player->SetLives(m_player->GetLives() - 1);
			if (m_player->GetLives() == 0)
			{
				ResourceManagers::GetInstance()->PlaySound("sfx_lose.ogg");
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
			}

		}
	}

	m_particleSystem->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score_text->Draw();
	
	for (auto button : m_listButton)
	{
		button->Draw();
	}

	m_player->Draw();

	m_enemyPool->Draw();
	m_bulletPool->Draw();
	m_meteorPool->Draw();

	for (int i = 0; i < m_player->GetLives(); i++)
	{
		m_liveRenderer[i]->Draw();
	}
	m_particleSystem->Draw();
}