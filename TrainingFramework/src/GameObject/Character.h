#pragma once
#include"SpriteAnimation.h"
#include "Sprite2D.h"

#define g 200
class Character : public SpriteAnimation {
public:
	Character();
	Character(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frameTime) :
		SpriteAnimation(model, shader, texture, numFrames, numActions, currentAction, frameTime),m_isCollision(false),vy(-50),vx(0) {};

	~Character();
	void SetVx(float _vx);
	float GetVx();
	void SetVy(float _vy);
	float GetVy();
	bool GetCollision();
	void CheckCollision(std::shared_ptr<Sprite2D> stage);
	void Move(float deltaTime);
private:
	float vx;
	float vy;
	bool m_isCollision;
};