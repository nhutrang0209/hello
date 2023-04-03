#include"GameField.h"
#include"Character.h"
#include"Sprite2D.h"
#include"ResourceManagers.h"
#include "Stage.h"

GameField::GameField() {
	Init();
};


GameField::~GameField() {

};

int GetRandom(int min, int max) {
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void GameField::Init() {
	power = 0;
	SetPhase(Phase::Jumping);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Group 1.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");

	m_character = std::make_shared<Character>(model, shader, texture, 2, 2, 0, 0.1f);
	m_character->Set2DPosition(140.0f, 200.0f);
	m_character->SetSize(40, 60);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Stage.tga");
	m_barbase = std::make_shared<Sprite2D>(model, shader, texture);
	m_barbase->Set2DPosition(150.0f, 60.0f);
	m_barbase->SetSize(152, 22);

	texture = ResourceManagers::GetInstance()->GetTexture("Stagered.tga");
	m_bar = std::make_shared<Sprite2D>(model, shader, texture);
	m_bar->Set2DPosition(150.0f, 60.0f);
	m_bar->SetSize(150, 20);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Grass.tga");
	std::shared_ptr<Sprite2D> stage = std::make_shared<Sprite2D>(model, shader, texture);
	stage->Set2DPosition(140.0f, 400.0f);
	stage->SetSize(50, 30);
	m_listStage.push_back(stage);

	for (int i = 0; i < 5; i++) {

	stage = std::make_shared<Sprite2D>(model, shader, texture);
	stage->Set2DPosition(200+120*i, 400.0f);
	stage->SetSize(GetRandom(40,80), 30);
	m_listStage.push_back(stage);
	}
}
void GameField::SetPhase(Phase phase) {
	m_phase = phase;
}
void GameField::Update(float deltaTime) {

	m_character->Update(deltaTime);
	std::cout << m_character->Get2DPosition().y;
	for (auto a : m_listStage) {
		a->Update(deltaTime);
	}
	switch (m_phase) {
	case Phase::Idle:{
		std::cout << "Idle" << std::endl;

		m_character->SetVx(20+power/4);
		m_character->SetVy(-power);
		break;
		}
	case Phase::Jumping: {
		std::cout << "Jumping" << std::endl;
		m_character->Move(deltaTime);

		for(auto a:m_listStage)
		m_character->CheckCollision(a);
		if (m_character->GetCollision() && m_character->GetVy()>0) {
			m_character->SetVx(0);
			m_character->SetVy(0);
			SetPhase(Phase::Idle);
		}
		break;
		}
	}
}

bool GameField::IsIdle() {
	if (m_phase == Phase::Idle) {
		return true;
	}
	else return false;
}
void GameField::Draw() {
	m_character->Draw();
	for (auto a : m_listStage) {
		a->Draw();
	}
	m_barbase->Draw();
	m_bar->Draw();
}
