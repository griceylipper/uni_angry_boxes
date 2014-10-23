#include "PhysicsSimulation.h"
#include "GameObject.h"

#define M_PI 3.14159265358979323846

PhysicsSimulation::PhysicsSimulation() : m_gravity(Vector2(0,0)) {

}

PhysicsSimulation::~PhysicsSimulation() {
	// Destroy all the objects.
	for(std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		delete (*it);
	}
	m_objects.clear();
}

GameObject* PhysicsSimulation::createObject(PhysicsObject* physobject, std::string filename, float mass, const Vector2& position, const OrientedBoundingBox& shape) {
	GameObject* object = new GameObject(physobject, "RedBox.png", mass, position, shape);
	m_objects.push_back(object);
	return object;
}

void PhysicsSimulation::destroyObject(GameObject* object) {
	for(std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		if( (*it) == object ) {
			m_objects.erase(it);
			break;
		}
	}
}

void PhysicsSimulation::step(float dt) {
	// Move Objects

	for(std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) {
		GameObject* obj = *it;

		GameObject nextState = *obj;

		if (obj->getObject()->immovable() == false)
		{
			obj->getObject()->m_velocity += m_gravity * dt;
			obj->getObject()->m_angularVelocity *= 0.1;

			obj->getObject()->m_rotation += nextState.getObject()->m_angularVelocity * dt;
			obj->getObject()->m_shape.UpdateOBB2D(nextState.getObject()->position(), nextState.getObject()->rotation());
			collisionCheckAndRespond(obj);

			obj->getObject()->m_position.y += nextState.getObject()->m_velocity.y * dt;
			obj->getObject()->m_shape.UpdateOBB2D(nextState.getObject()->position(), nextState.getObject()->rotation());
			collisionCheckAndRespond(obj);

			obj->getObject()->m_position.x += nextState.getObject()->m_velocity.x * dt;
			obj->getObject()->m_shape.UpdateOBB2D(nextState.getObject()->position(), nextState.getObject()->rotation());
			collisionCheckAndRespond(obj);
		}

		obj->getObject()->m_shape.UpdateOBB2D(nextState.getObject()->position(), nextState.getObject()->rotation());
	}

	// Detect collision
	
	// Collision response
}

void PhysicsSimulation::collisionCheckAndRespond(GameObject* obj)
{
	GameObject& myObject = *obj;
	for(std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++) 
	{
		GameObject* collider = *it;
		if( collider == obj )
			continue;

		OverlapResult result;
		if (myObject.getObject()->m_shape.Overlaps(collider->getObject()->shape(), result)) {
			
			for ( int i = 0; i < 2; i++ )
			{
				float correction = result.amount[i];
				Vector2 offset = myObject.getObject()->m_shape.axis[i] * correction * 2;
				myObject.getObject()->position(myObject.getObject()->position() - offset);
			}

			//myObject.velocity(Vector2(0,0));
			//nextState.angularVelocity(angularVel);
		}
	}
}