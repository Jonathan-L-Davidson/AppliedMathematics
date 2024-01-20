#pragma once
#ifndef PHYSICS_COMP_H
#define PHYSICS_COMP_H
#include <vector>

#include "Component.h"
#include "Physics/Vector3.h"
using namespace Physics;

class PhysicsComponent : public Component
{
	public:
		PhysicsComponent() {};
		PhysicsComponent
		(	const float mass,
			const float dragCoef,
			const bool useConstantVel,
			const bool useConstantAcc) :
			mass(mass),
			dragCoef(dragCoef),
			useConstantVelocity(useConstantVel),
			useConstantAcceleration(useConstantAcc)
			{ };
		void Start();
		void Update(float deltaTime);
		void Destroy();

		void AddForce(const Vector3 force) { m_forces.push_back(force); };

		float mass = 1.0f;
		float dragAmount = 1.0f;
		float dragCoef = 1.05f; // cube coeff
		Vector3 gravity = Vector3(0, -981.0f, 0);

		bool useGravity = true;
		bool hasFriction = false;
		bool useConstantVelocity = false;
		bool useConstantAcceleration = false;
private:
		void UpdatePhysics(float deltaTime);
		void CalculateForces(float deltaTime);
		void CalculateAcceleration(float deltaTime);
		void CalculateVelocity(float deltaTime);
		void HandleGravity();

		void UpdatePosition(float deltatime);

		Vector3 m_velocity;
		Vector3 m_acceleration;
		Vector3 m_forceTotal;
		std::vector<Vector3> m_forces;

		Vector3 m_oldVelocity;
		Vector3 m_oldPos;

		float m_maxSpeed = 500.0f;
};

#endif // !PHYSICS_COMP_H
