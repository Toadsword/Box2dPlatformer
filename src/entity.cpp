#include "entity.h"

Entity::Entity(b2Vec2 position, sf::Texture * texture, b2BodyType bodyType, b2World & world): texture(texture), bodyType(bodyType)
{
	//Body
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position = position;
	bodyDef.fixedRotation = true;
	body = world.CreateBody(&bodyDef);

	// main Fixture
	b2PolygonShape fixtureDef;
	// one meter, divided by 2 because it takes the center of the box for the base, so he guesses we give him half of it
	fixtureDef.SetAsBox(1.f / 2.f, 1.f / 2.f); 
	body->CreateFixture(&fixtureDef, 0.f);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &fixtureDef;
	myFixtureDef.density = 1;

	sprite.setTexture(*texture);
	sprite.setPosition(World::meter2pixel(body->GetPosition()));
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow & window)
{
	if(this->bodyType == b2_dynamicBody)
		sprite.setPosition(World::meter2pixel(body->GetPosition()));
	window.draw(sprite);
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