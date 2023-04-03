#include"Character.h"
#include "GameField.h"


Character::~Character() {

};
void Character::SetVx(float _vx) {
	vx = _vx;
}
float Character::GetVx() {
	return vx;
}
void Character::SetVy(float _vy) {
	vy = _vy;
}
float Character::GetVy() {
	return vy;
}
bool Character::GetCollision() {
	return m_isCollision;
}
void Character::CheckCollision(std::shared_ptr<Sprite2D> stage) {
	int x = this->Get2DPosition().x;
	int y =	this->Get2DPosition().y;
	int w = m_iWidth;
	int h = m_iHeight;

	int x2 = stage->Get2DPosition().x;
	int y2 = stage->Get2DPosition().y;
	int w2 = stage->GetScale().x;
	int h2 = stage->GetScale().y;
		if (
			x-w/2 < x2 + w2/2 &&
			x + w/2 > x2-w2/2 &&
			y-h/2 < y2 + h2/2 &&
			h/2 + y >y2-h2/2
			) {
			m_isCollision = true;
		}
		else {
			// No collision
		}
}

void Character::Move(float deltaTime) {
	m_isCollision = false;
		if (m_isCollision == false) {
			vy += g*deltaTime;
			Set2DPosition(Get2DPosition().x+vx*deltaTime, Get2DPosition().y +vy*deltaTime);
		}

}
