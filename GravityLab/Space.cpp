/************

GravityLab
Space.cpp

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (Ò¦Ô£ÐÀ).

Released under GPL-3.0 license

************/

#include "StdAfx.h"
#include "Space.h"

Space::Space(double interval, int iterTimes) : mRestTime(0), mIterTimes(iterTimes) {
	Entity::interval = interval;
}

void Space::init() {
	for (int i = 0; i < mEntities.size(); i++) {
		for (int j = i + 1; j < mEntities.size(); j++) {
			if (!(mEntities[i].getMass() || mEntities[j].getMass())) continue;
			Vector2d diff = mEntities[i].getPosition() - mEntities[j].getPosition();
			double dist = diff.length();
			mEntities[i].initPotential += -G * mEntities[j].getMass() / dist;
			mEntities[j].initPotential += -G * mEntities[i].getMass() / dist;
		}
	}
}

void Space::newEntity(Vector2d position, Vector2d velocity, double mass) {
	reset();
	mEntities.push_back(Entity(position, velocity, mass));
//	init();
}

void Space::simulate(double time) {
	double crt = 0;
	for (; crt <= time + mRestTime; crt += Entity::interval) {
		/*
		for (int i = 0; i < mEntities.size(); i++) {
			for (int j = i + 1; j < mEntities.size(); j++) {
				if (!(mEntities[i].getMass() || mEntities[j].getMass())) continue;
				Vector2d diff = mEntities[i].getPosition() - mEntities[j].getPosition();
				double sqrDist = diff.squaredLength();
				diff.normalize();
				mEntities[i].applyAcc(-diff * (G * mEntities[j].getMass() / sqrDist));
				mEntities[j].applyAcc(diff * (G * mEntities[i].getMass() / sqrDist));
			}
		}
		for (int i = 0; i < mEntities.size(); i++) {
			mEntities[i].nextState();
		}
		*/
		for (int i = 0; i < mEntities.size(); i++) {
			for (int j = i + 1; j < mEntities.size(); j++) {
				if (!(mEntities[i].getMass() || mEntities[j].getMass())) continue;
				Vector2d diff = mEntities[i].getPosition() - mEntities[j].getPosition();
				double sqrDist = diff.squaredLength();
				diff.normalize();

				mEntities[i].tempAcc += -diff * (G * mEntities[j].getMass() / sqrDist);
				mEntities[j].tempAcc += diff * (G * mEntities[i].getMass() / sqrDist);
			}
		}

		int n = 0;
		do {
			for (int i = 0; i < mEntities.size(); i++) {
				mEntities[i].tempState();
				mEntities[i].getAcc() = mEntities[i].tempAcc * 0.5;
			}
			for (int i = 0; i < mEntities.size(); i++) {
				for (int j = i + 1; j < mEntities.size(); j++) {
					if (!(mEntities[i].getMass() || mEntities[j].getMass())) continue;
					Vector2d diff = mEntities[i].tempPos - mEntities[j].tempPos;
					double sqrDist = diff.squaredLength();
					diff.normalize();

					mEntities[i].applyAcc(-diff * (0.5 * G * mEntities[j].getMass() / sqrDist));
					mEntities[j].applyAcc(diff * (0.5 * G * mEntities[i].getMass() / sqrDist));
				}
			}
		} while (++n < mIterTimes);

		for (int i = 0; i < mEntities.size(); i++) {
			mEntities[i].nextState();
		}

		/*
		for (int i = 0; i < mEntities.size(); i++) {
			for (int j = i + 1; j < mEntities.size(); j++) {
				if (!(mEntities[i].getMass() || mEntities[j].getMass())) continue;
				Vector2d diff = mEntities[i].getPosition() - mEntities[j].getPosition();
				double dist = diff.length();
				mEntities[i].potential += -G * mEntities[j].getMass() / dist;
				mEntities[j].potential += -G * mEntities[i].getMass() / dist;
			}
		}

		for (int i = 0; i < mEntities.size(); i++) {
			mEntities[i].resizeVel();
		}
		*/
		
	}
	mRestTime = time + mRestTime - (crt - Entity::interval); 
}