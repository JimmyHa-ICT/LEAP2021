#include "GSShipSelect.h"
#include "Util.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSShipSelect::GSShipSelect()
{

}


GSShipSelect::~GSShipSelect()
{
}



void GSShipSelect::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_blue");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//spaceship
	texture = ResourceManagers::GetInstance()->GetTexture("playerShip3_blue");
	m_ship = std::make_shared<Sprite2D>(model, shader, texture);
	m_ship->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_ship->SetSize(136, 100);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 625);
	button->SetSize(275, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);


	//text game over
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("kenvector_future");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SELECT PADDLE", TEXT_COLOR::RED, 1.5);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 180, 120));
}

void GSShipSelect::Exit()
{
	Util::shipColor = m_currentSelect;
}


void GSShipSelect::Pause()
{

}

void GSShipSelect::Resume()
{

}


void GSShipSelect::HandleEvents()
{

}

void GSShipSelect::HandleKeyEvents(int key, bool bIsPressed)
{
	if ((key == KEY_MOVE_LEFT || key == KEY_LEFT) && bIsPressed)
	{
		if (m_currentSelect > 0)
			m_currentSelect--;
	}

	if ((key == KEY_MOVE_RIGHT || key == KEY_RIGHT) && bIsPressed)
	{
		if (m_currentSelect < 3)
			m_currentSelect++;
	}

	auto texture = ResourceManagers::GetInstance()->GetTexture(Util::ConvertShipTexture(m_currentSelect));
	m_ship->SetTexture(texture);
}

void GSShipSelect::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSShipSelect::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSShipSelect::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
	m_ship->Draw();
}
