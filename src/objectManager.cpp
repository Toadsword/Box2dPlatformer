#include "objectManager.h"
enum MOVE_STATE
{
	LEFT,
	RIGHT
	//UP
};
objectManager::objectManager(sf::Vector2f position, sf::Texture* texture, b2Body* body) : position(position), texture(texture), body(body)
{
	sprite.setTexture(*texture);
	sprite.setPosition(position);
}

objectManager::~objectManager()
{
}

void objectManager::draw(sf::RenderWindow & window)
{
	window.draw(this->sprite);
}

void objectManager::move(double deltaX, double deltaY)
{
	this->position += sf::Vector2f(deltaX, deltaY);
	sprite.setPosition(this->position);
}

b2Body* objectManager::getBody()
{
	return this->body;
}

sf::Sprite* objectManager::getSprite()
{
	return &this->sprite;
}
//  - keyboard
// Description : permet de bouger le corps physique
void objectManager::keyboard(unsigned char key)
{
	MOVE_STATE move_state;

	switch (key)
	{
	case 'a': //move left
		move_state = LEFT;
		break;


	case 'd': //move right
		move_state = RIGHT;
		break;

	case 'w': //jump

		b2Vec2 vel = body->GetLinearVelocity();
		vel.y = 10;
		body->SetLinearVelocity(vel);
		break;
	//case 'w':utilise methode impusle
	//{
	//	//to change velocity by 10
	//	float impulse = body->GetMass() * 10;
	//	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());
	//}
	//break;
	}


}