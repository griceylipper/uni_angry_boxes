#include "GameObject.h"
#include <iostream>
#include <string>

#define M_PI 3.14159265358979323846

GameObject::GameObject(PhysicsObject* object, std::string filename, float mass, const Vector2& position, const OrientedBoundingBox& shape) : m_object(object)
{
	if (!m_texture.loadFromFile(filename, sf::IntRect(10, 10, object->shape().width, object->shape().height)))
	{
		std::cout << "ERROR CAN'T LOAD " << filename << " (GameObject::GameObject())" << std::endl;
	}
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}


void GameObject::updateGraphics()
{
	m_sprite.setScale(2, 2);
	//m_sprite.setPosition(position().x - (shape().width / 2 * cosf(rotation())), position().y - (shape().height / 2 * sinf(rotation())));
	m_sprite.setPosition(m_object->position().x, m_object->position().y);
	m_sprite.setRotation(m_object->rotation()*180/M_PI);
}

const sf::Sprite& GameObject::getSprite()
{
	return m_sprite;
}

PhysicsObject* GameObject::getObject()
{
	return m_object;
}