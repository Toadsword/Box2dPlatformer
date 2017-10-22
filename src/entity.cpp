#include "entity.h"

Entity::Entity(b2Vec2 position, sf::Texture * texture, b2BodyType bodyType, b2World & world): texture(texture), bodyType(bodyType)
{
	//Body
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position = position;
	body = world.CreateBody(&bodyDef);

	// main Fixture
	b2PolygonShape fixtureDef;
	fixtureDef.SetAsBox(1.f / 2.f, 1.f / 2.f);
	body->CreateFixture(&fixtureDef, 0.f);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &fixtureDef;
	myFixtureDef.density = 1;

	//foot sensor fixture
    myFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = body->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData((void*)3);

	
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

void Entity::Keyboard(sf::Keyboard::Key code)
{

	b2Vec2 vel = body->GetLinearVelocity();
	switch (code)
	{
	case sf::Keyboard::A: //move left
		vel.x += -5;
		body->SetLinearVelocity(vel);
		break;

	
	case sf::Keyboard::D: //move right
		vel.x += 5;
		body->SetLinearVelocity(vel);
		break;
	
	case sf::Keyboard::W:
	
		if (vel.y==0)
	
		vel.y -= 8;
		body->SetLinearVelocity(vel);
		
	break;
	}
	body->SetLinearVelocity(vel);
}


