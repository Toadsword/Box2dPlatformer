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

void Entity::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'a': //move left
		movestate = LEFT;
		break;


	case 'd': //move right
		movestate = RIGHT;
		break;
	
	case 'w':
	// utilise l'impulse pour sauter
		//to change velocity by 10
		float impulse = body->GetMass() * 10;
		body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(),true);
	break;
	}
}

// permet de faire en sorte que le body ne peut que sauter sur un sol
void Entity::beginContact(b2Contact* contact)
{
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		numcontact++;
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
		numcontact++;
}

void Entity::endContact(b2Contact* contact)
{
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		numcontact--;
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
		numcontact--;
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