/************

GravityLab
Entity.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (Ò¦Ô£ÐÀ).

Released under GPL-3.0 license

************/

#pragma once

#include "Vector2d.h"

#include <vector>
using std::vector;

inline int round(double number) {
	return int(number + 0.5);
}

class Entity {

public:
	Entity(const Vector2d &position, const Vector2d &velocity, double mass = 0) : 
		pos(position), initPos(position), vel(velocity), initVel(velocity), mass(mass),
		potential(0), initKineticEnergePerMass(velocity.squaredLength() * 0.5),
		initPotential() { }

	void setVelocity(const Vector2d &v) {
		initVel = vel = v;
		initKineticEnergePerMass = v.squaredLength() * 0.5;
	}

	const Vector2d & getPosition() const {
		return pos;
	}

	double getMass() const {
		return mass;
	}

	void reset() {
		track.clear();
		pos = initPos;
		vel = initVel;
		initPotential = 0;
	}

	void applyAcc(Vector2d & a) {
		acc += a;
	}

	Vector2d & getAcc() {
		return acc;
	}

	void nextState() {
		pos += vel * interval + (acc * (0.5 * interval * interval));
		vel += acc *= interval;
		acc.set(0, 0);
		tempAcc.set(0, 0);
		track.push_back(pos);
	}

	void tempState() {
		tempPos = pos + (vel * interval + (tempAcc * (0.5 * interval * interval)));
	}

	// still under debugging
	void resizeVel() {
		double kEnerge = initKineticEnergePerMass + initPotential - potential;

		double a = vel.length(), b = sqrt(2 * kEnerge);

//		if (kEnerge > 0)
//			vel.normalize() *= sqrt(2 * kEnerge);

/*		static int count = 0;

		if (count++ % 9 == 0) {
			CString str;
			str.Format(L"%lf\t", vel.length() - sqrt(2 * kEnerge));
			if ((count - 1) % 2) str += "\n";
			OutputDebugString(str);
		}
*/
		if (kEnerge > 0 || vel.length() < sqrt(2 * kEnerge))
			vel.normalize() *= a * 0.5 + b * 0.5;

//		if (kEnerge < 0) vel.set(0, 0);

		potential = 0;
	}

	bool isNoTrack() const {
		return !(track.size());
	}

	const Vector2d & getPosition(double time) const {
		unsigned int index = round(time / interval);
		if (index >= track.size()) return track[track.size() - 1];
		return track[index];
	}

	Vector2d tempPos, tempAcc;

	double potential, initKineticEnergePerMass, initPotential;

	friend class Space;
	
private:
	Vector2d pos, vel, acc;

	Vector2d initPos, initVel;
	double mass;

	vector<Vector2d> track;
	
	static double interval;
	
};