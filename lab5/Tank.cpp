#include <iostream>

#include "lab_m1/lab5/Tank.h"

using namespace m1;
using namespace std;
using namespace glm;
using namespace createObjects;

Tank::Tank() {

}

Tank::~Tank() {

}

void Tank::init(float speed, string name) {

	this->speed = speed;
	this->name = name;

	TrackPos = vec3(0, 0.3, 0);
	BodyPos = vec3(0, 0.9, 0);
	TurretPos = vec3(0, 1.8, 0);
	CannonPos = vec3(0, 1.9, 0);

	tankAngle = 0;
	turretAngle = 0;
	TrackDir = vec3(sin(tankAngle), 0, cos(tankAngle));
	BodyDir = vec3(sin(tankAngle), 0, cos(tankAngle));
	TurretDir = vec3(sin(turretAngle), 0, cos(turretAngle));
	CannonDir = vec3(sin(turretAngle), 0, cos(turretAngle));

	forwardFactor = 1;

	rotationSpeed = M_PI / 2;

	up = rand() % (4 - 3 + 1) + 1;
	state = rand() % 4;

	canShoot = 0;

	createTank(name);

	freeze = false;

	HealthPoints = 3;
	hp_vec = vec3(3, 3, 3);
	score = 0;
}

void Tank::setPoints() {
	score += 1;
}
int Tank::getPoints() {
	return score;
}
void Tank::setHealthPoints() {
	HealthPoints -= 1;
	hp_vec -= vec3(1, 1, 1);
}
int Tank::getHealthPoints() {
	return HealthPoints;
}

glm::vec3 Tank::getHP_vec() {
	return hp_vec;
}
void Tank::setPos() {
	int random1, random2;

	random1 = rand() % (80 - (-80) + 1) + (-80);
	random2 = rand() % (80 - (-80) + 1) + (-80);
	
	TrackPos = vec3(random1, 0.3, random2);
	BodyPos = vec3(random1, 0.9, random2);
	TurretPos = vec3(random1, 1.8, random2);
	CannonPos = vec3(random1, 1.9, random2);
}

void Tank::update(float dt) {
	canShoot -= dt;
	if (name == "player") {
		glm::vec3 cen = glm::normalize(TrackPos);/*
		printf("cen: %f, %f\n", cen.x, cen.z);
		printf("poz: %f, %f\n", TrackDir.x, TrackDir.z);*/
	}
}

void Tank::updateMotion(float dt) {
	if (up <= 0) {
		up = rand() % (4 - 3 + 1) + 1;
		state = rand() % 4;
	}
	else {
		up -= dt;
		// forward
		if (state == 0){
			if (!(this->TrackPos.x > 100 || this->TrackPos.x < -100 || this->TrackPos.z < -100 || this->TrackPos.z > 100)) {
				this->move(dt, true);
			}
			
		}
		//backward
		else if (state == 1) {
			if (!(this->TrackPos.x > 100 || this->TrackPos.x < -100 || this->TrackPos.z < -100 || this->TrackPos.z > 100)) {
				this->move(dt, false);
			}
		}
		//right
		else if (state == 2) {
			this->rotateTank(dt * 10.0f, false);
			up = 0;
		}
		//left
		else if (state == 3) {
			this->rotateTank(dt * 10.0f, true);
			up = 0;
		}
	}
}

void Tank::Collision(vec3 p) {
	TrackPos += vec3(p.x, 0, p.z);
	BodyPos += vec3(p.x, 0, p.z);
	TurretPos += vec3(p.x, 0, p.z);
	CannonPos += vec3(p.x, 0, p.z);
}

void Tank::shoot() {
	projectils.push_back({ 0.0f, 0.0f, TurretDir, this->CannonPos, 2, true });
	canShoot = 1;
}

vector<Tank::Projectile> Tank::getProjectiles() {
	return projectils;
}

void Tank::setTranslate(float dt, int idx) {
	this->projectils[idx].translateX += dt * 10.0f * -projectils[idx].angle.x;
	this->projectils[idx].translateZ += dt * 10.0f * -projectils[idx].angle.z;
	this->projectils[idx].life -= dt;
	if (this->projectils[idx].life <= 0) {
		this->projectils[idx].show = false;
	}
}

void Tank::updatePLife(int idx) {
	this->projectils[idx].life = 0;
	if (this->projectils[idx].life <= 0) {
		this->projectils[idx].show = false;
	}
}

float Tank::getSpeed() {
	return speed;
}
float Tank::getTankAngle() {
	return tankAngle;
}
float Tank::getTurretAngle() {
	return turretAngle;
}

glm::vec3 Tank::getTrackPos() {
	return TrackPos;
}
glm::vec3 Tank::getBodyPos() {
	return BodyPos;
}
glm::vec3 Tank::getTurretPos() {
	return TurretPos;
}
glm::vec3 Tank::getCannonPos() {
	return CannonPos;
}

void Tank::createTank(string name) {
	if (name == "player") {
		track = createTrack(glm::vec3(1, 0.8, 0.89), 0.1, "trackPlayer");
		body = createBody(glm::vec3(0.6, 0, 0.298), 0.1, "bodyPlayer");
		turret = createTurret(glm::vec3(1, 0, 0.498), 0.1, "turretPlayer");
		cannon = createCannon(glm::vec3(1, 0.4, 0.698), 0.02, "cannonPlayer");
	}
	else if (name == "enemy") {
		track = createTrack(glm::vec3(0.89, 0.8, 1), 0.1, "trackEnemy");
		body = createBody(glm::vec3(0.298, 0, 0.6), 0.1, "bodyEnemy");
		turret = createTurret(glm::vec3(0.6, 0.2, 1), 0.1, "turretEnemy");
		cannon = createCannon(glm::vec3(0.8, 0.6, 1), 0.02, "cannonEnemy");
	}
}

void Tank::rotateTank(float dt, bool left) {

	int rotDir = left ? 1 : -1;

	tankAngle += rotDir * rotationSpeed * dt;
	if (tankAngle < 0)
		tankAngle += 2 * M_PI;

	TrackDir.x = sin(tankAngle);
	TrackDir.z = cos(tankAngle);

	BodyDir.x = sin(tankAngle);
	BodyDir.z = cos(tankAngle);

	TurretDir.x = sin(tankAngle + turretAngle);
	TurretDir.z = cos(tankAngle + turretAngle);

	CannonDir.x = sin(tankAngle + turretAngle);
	CannonDir.z = cos(tankAngle + turretAngle);
}

glm::vec3 Tank::getDir() {
	return BodyDir;
}
void Tank::rotateTurret(float dir, Tank* player) {

	if (name == "player") {
		turretAngle -= dir * 0.001f;
		if (turretAngle < 0) {
			turretAngle += M_PI * 2;
		}
	}
	else if (name == "enemy") {
		glm::vec3 cen = glm::normalize(this->getTrackPos() - player->getTrackPos());
		float angle = glm::atan2(cen.z, cen.x) - glm::atan2(TurretDir.z, TurretDir.x);
		if (angle < 0) {
			angle += M_PI * 2;
		}
		if (angle >= 0.05) {
			turretAngle -= dir * 0.5f;
			freeze = true;
			if (turretAngle < 0)
				turretAngle += M_PI * 2;
		}
		else {
			if (this->canShoot <= 0) {
				this->shoot();
			}
		}
	}
	TurretDir.x = sin(tankAngle + turretAngle);
	TurretDir.z = cos(tankAngle + turretAngle);

	CannonDir.x = sin(tankAngle + turretAngle);
	CannonDir.z = cos(tankAngle + turretAngle);
}
void Tank::move(float dt, bool forward) {
	forwardFactor = forward ? -1 : 1;

	TrackPos += speed * forwardFactor * dt * TrackDir;
	BodyPos += speed * forwardFactor * dt * BodyDir;
	TurretPos += speed * forwardFactor * dt * BodyDir;
	CannonPos += speed * forwardFactor * dt * BodyDir;
}

Mesh* Tank::getTrack() {
	return track;
}
Mesh* Tank::getBody() {
	return body;
}
Mesh* Tank::getTurret() {
	return turret;
}
Mesh* Tank::getCannon() {
	return cannon;
}