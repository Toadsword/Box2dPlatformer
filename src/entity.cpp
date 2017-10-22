#include "entity.h"

Entity::Entity(b2Vec2 position, sf::Texture * texture, b2BodyType bodyType, b2World & world): texture(texture), bodyType(bodyType)
{
	//Body
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position = position;
	body = world.CreateBody(&bodyDef);

	//Fixture
	b2PolygonShape fixtureDef;
	fixtureDef.SetAsBox(1.f / 2.f, 1.f / 2.f);
	body->CreateFixture(&fixtureDef, 0.f);

	sprite.setTexture(*texture);
	sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow & window)
{
	if(this->bodyType == b2_dynamicBody)
		sprite.setPosition(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);

	window.draw(sprite);
}

void Entity::move(double deltaX, double deltaY)
{
}

b2Body * Entity::getBody()
{
	return this->body;
}

b2BodyType Entity::getBodyType()
{
	return this->bodyType;
}

sf::Sprite * Entity::getSprite()
{
	return &this->sprite;
}
