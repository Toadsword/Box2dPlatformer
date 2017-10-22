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
	sprite.setPosition(World::meter2pixel(body->GetPosition()));
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

void Entity::setLinearVelocity(b2Vec2 vect)
{
	body->SetLinearVelocity(vect);
}

void Entity::applyForce(b2Vec2 vect)
{
	body->ApplyForce(vect, body->GetWorldCenter(), true);
}

void Entity::applyLinearImpulse(b2Vec2 vect)
{
	body->ApplyLinearImpulse(vect, body->GetWorldCenter(), true);
}

b2Vec2 Entity::getLinearVelocity()
{
	return this->body->GetLinearVelocity();
}