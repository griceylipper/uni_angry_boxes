#ifndef GameObject_h__
#define GameObject_h__

#include "PhysicObject.h"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include <string>

class GameObject
{
public:
	GameObject(PhysicsObject*, std::string, float, const Vector2&, const OrientedBoundingBox&);
	
	const sf::Sprite& getSprite();
	void updateGraphics();
	PhysicsObject* getObject();

private:
	PhysicsObject* m_object;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};

#endif

