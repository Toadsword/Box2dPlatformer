#include "objectManager.h"

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
