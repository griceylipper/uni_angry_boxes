#ifndef PhysicsSimulation_h__
#define PhysicsSimulation_h__

#include "Vector2.h"
#include "OrientedBoundingBox.h"
#include <vector>
#include <string>

class GameObject;
class PhysicsObject;

class PhysicsSimulation {
public:
	PhysicsSimulation();
	~PhysicsSimulation();

	GameObject* createObject(PhysicsObject*, std::string, float mass, const Vector2& position, const OrientedBoundingBox& shape);
	void destroyObject(GameObject* object);
	void step(float dt);

	const std::vector<GameObject*>& getObjects() { return m_objects; }

	inline void gravity(const Vector2& gravity) { m_gravity = gravity; }
	inline const Vector2 gravity() const { return m_gravity; }
private:
	void collisionCheckAndRespond(GameObject* obj);

	std::vector<GameObject*> m_objects;
	Vector2 m_gravity;
};

#endif // PhysicsSimulation_h__
