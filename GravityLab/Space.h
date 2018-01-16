/************

GravityLab
Space.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (Ò¦Ô£ÐÀ).

Released under GPL-3.0 license

************/

#pragma once

#include <vector>
#include "Entity.h"

using std::vector;

#ifdef G
#undef G
#endif

#define G 1	/*(6.67384E-11)*/

class Space {

public:
	Space(double interval, int iterTimes);

	void newEntity(Vector2d position, Vector2d velocity, double mass = 0);

	void simulate(double time);

	void reset() {
		for (auto i = mEntities.begin(); i != mEntities.end(); i++) {
			i->reset();
		}
	}

	void clear() {
		mEntities.clear();
	}

	void init();

	const vector<Entity> & getEntities() {
		return mEntities;
	}

	Entity & modifyLastEntity() {
		reset();
		return mEntities.back();
	}

private:
	vector<Entity> mEntities;

	double mRestTime;

	unsigned mIterTimes;
};

