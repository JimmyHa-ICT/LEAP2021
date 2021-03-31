#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

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

	//pause panel
	/*texture = ResourceManagers::GetInstance()->GetTexture("panel_pause");
	m_PausePanel = std::make_shared<Sprite2D>(model, shader, texture);
	m_PausePanel->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_PausePanel->SetSize(screenWidth / 4, screenHeight / 2);
	*/

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

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("kenvector_future_thin");
	m_score = std::make_shared< Text>(shader, font, "100025", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(25, 50));
}

void GSPlay::Exit()
{

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
				//std::cout << "Collide!" << std::endl;
				obj->Reset();
				meteor->Reset();
			}
		}
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	
	for (auto button : m_listButton)
	{
		button->Draw();
	}

	m_player->Draw();

	m_enemyPool->Draw();
	m_bulletPool->Draw();
	m_meteorPool->Draw();
	//m_PausePanel->Draw();
}

void GSPlay::PauseGame()
{
	if (this->isPlaying)
	{
		this->isPlaying = false;
	}
}