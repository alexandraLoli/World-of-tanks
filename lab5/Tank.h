#pragma once
#include "core/gpu/mesh.h";
#include "utils/glm_utils.h"
#include "lab_m1/lab5/createObjects.h";
#include <string>

using namespace std;

namespace m1
{
	class Tank
	{
	public:
		Tank();
		~Tank();

		struct Projectile {
			float translateX, translateZ;
			glm::vec3 angle;
			glm::vec3 position;
			float life;
			bool show;
		};

		void init(float speed, string name);
		void update(float dt);
		void updateMotion(float dt);
		void rotateTank(float dt, bool left);
		void rotateTurret(float dir, Tank* player);
		void move(float dt, bool forward);
		void shoot();

		vector<Projectile> getProjectiles();
		void setTranslate(float dt, int idx);
		void updatePLife(int idx);

		void setPos();
		void Collision(glm::vec3 p);
		glm::vec3 getTrackPos();
		glm::vec3 getBodyPos();
		glm::vec3 getTurretPos();
		glm::vec3 getCannonPos();
		glm::vec3 getNextPos(float dt);
		glm::vec3 getDir();

		float getSpeed();
		float getTankAngle();
		float getTurretAngle();

		void setHealthPoints();
		int getHealthPoints();
		glm::vec3 getHP_vec();

		void setPoints();
		int getPoints();

		void createTank(string name);
		Mesh* getTrack();
		Mesh* getBody();
		Mesh* getTurret();
		Mesh* getCannon();

		float canShoot;
		bool freeze;
	private:
		glm::vec3 TrackPos;
		glm::vec3 BodyPos;
		glm::vec3 TurretPos;
		glm::vec3 CannonPos;

		glm::vec3 TrackDir;
		glm::vec3 BodyDir;
		glm::vec3 TurretDir;
		glm::vec3 CannonDir;

		int forwardFactor;

		float speed;
		float rotationSpeed;
		float tankAngle;
		float turretAngle;

		Mesh* track;
		Mesh* body;
		Mesh* turret;
		Mesh* cannon;

		float up;
		int state;
		string name;

		vector<Projectile> projectils;

		int HealthPoints;
		glm::vec3 hp_vec;

		int score;
	};
}
