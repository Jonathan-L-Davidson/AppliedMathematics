#include "Debug.h"
#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::Start() {
	m_oldPos = _owner->transform->position;
}

void PhysicsComponent::Update(float deltaTime) {
	if (useGravity) {
		HandleGravity();
	}

	UpdatePhysics(deltaTime);
}

void PhysicsComponent::CalculateForces(float deltaTime) {
	for (Vector3 force : m_forces) {
		m_forceTotal += force;
	}

	float velMagnitude = m_velocity.SquareMagnitude();

	// handle drag:
	if (velMagnitude != 0) {
		//DebugPrintF("Velocity: %f \n", velMagnitude);
		if (useDrag) {
			Vector3 dragForce = m_velocity;
			dragForce.Normalise();

			// turbulent
			if (useTurbulentDrag) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef));
				dragForce *= force * -1;
			}
			// laminar
			else if (useLaminarDrag) {
				float force = (0.5f * (dragAmount * velMagnitude * dragCoef));
				dragForce *= force * -1;
			}
		
			m_forceTotal += dragForce;
		}
	}

	// handle friction:
	if (hasFriction) {
		Vector3 forceApplication = m_forceTotal;
		forceApplication.Normalise();
		// kinetic friction
		if (velMagnitude > (friction * frictionCoef)) {
			forceApplication *= (friction * mass) * frictionCoef;
			forceApplication *= -1;

			m_forceTotal += forceApplication;
		}
		// static friction
		else {
			if (m_forceTotal.SquareMagnitude() < friction) {
				m_forceTotal = Vector3(); // we apply no more forces.

				if (velMagnitude != 0) {
					m_velocity -= m_velocity / ((friction * mass) * frictionCoef); // this is cheating, I know.
				}
			}
		}
	}
}

void PhysicsComponent::CalculateAcceleration(float deltaTime) {
	if (!useConstantAcceleration) {
		m_acceleration += (m_forceTotal / mass) * deltaTime;
	}
	else {
		m_acceleration += m_forceTotal / mass;
	}
}

void PhysicsComponent::CalculateVelocity(float deltaTime) {
	if (!useConstantVelocity) {
		m_velocity += m_acceleration * deltaTime;
	}
	else {
		m_velocity += m_acceleration;
	}
}

void PhysicsComponent::UpdatePosition(float deltaTime) {
	float magnitude = m_velocity.Magnitude();

	if (magnitude > m_maxSpeed) {
		m_velocity.Normalise();
		m_velocity *= m_maxSpeed;
	}

	if (magnitude != 0) {
		Vector3 pos = m_oldPos + (m_velocity * deltaTime);
		_owner->SetPosition(pos);
		m_oldPos = pos;
	}

}

void PhysicsComponent::Destroy() {
	
}

void PhysicsComponent::UpdatePhysics(float deltaTime) {
	CalculateForces(deltaTime);
	CalculateAcceleration(deltaTime);
	CalculateVelocity(deltaTime);
	UpdatePosition(deltaTime);

	m_forceTotal = Vector3(); // Resets it by returning default values.
	m_forces.clear();
	m_acceleration = Vector3();
	// 
}

void PhysicsComponent::HandleGravity() {
	if (_owner->GetPosition().y < 0) {
		Vector3 pos = _owner->transform->position;
		pos.y = 0;
		_owner->SetPosition(pos);
		if (m_velocity.y < 0) {
			m_velocity.y = 0;
		}
		
		hasFriction = true;
	}
	else if(_owner->GetPosition().y > 0) {
		AddForce(gravity * mass);
		hasFriction = false;
	}
}