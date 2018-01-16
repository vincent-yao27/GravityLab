/************

Vector2d Class

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (Ò¦Ô£ÐÀ).

Released under GPL-3.0 license

************/


#ifndef CANDY_VECTOR2D_H
#define CANDY_VECTOR2D_H

#include <cmath>

class Vector2d {
public:
	Vector2d() : x(0), y(0) { }
	Vector2d(double x, double y) : x(x), y(y) { }
	
	double x, y;


	Vector2d clone() const {
		return Vector2d(*this);
	}

	Vector2d & set(double x, double y) {
		this->x = x;
		this->y = y;
		return *this;
	}

	Vector2d & set(const Vector2d &v) {
		this->x = v.x;
		this->y = v.y;
		return *this;
	}

	Vector2d & normalize() {
		double l = this->length();
		if (l) {
			x /= l;
			y /= l;
		}
		return *this;
	}

	Vector2d & rotate(double angle) {
		double cosVal = std::cos(angle), sinVal = std::sin(angle);
		x = x * cosVal - y * sinVal;
		y = x * sinVal + y * cosVal;
		return *this;
	}

	Vector2d & operator= (const Vector2d &v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2d & operator+= (const Vector2d &v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2d & operator-= (const Vector2d &v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2d & operator*= (double k) {
		x *= k;
		y *= k;
		return *this;
	}

	Vector2d operator- () const {
		Vector2d v;
		v.x = -x;
		v.y = -y;
		return v;
	}

	Vector2d operator+ (const Vector2d &v) const {
		return clone() += v;
	}

	Vector2d operator- (const Vector2d &v) const {
		return clone() -= v;
	}

	Vector2d operator* (double k) const {
		return clone() *= k;
	}


	double length() const {
		return std::sqrt(x * x + y * y);
	}

	double squaredLength() const {
		return x * x + y * y;
	}

	double dist(const Vector2d &v) const {
		return (*this - v).length();
	}

	double squaredDist(const Vector2d &v) const {
		return (*this - v).squaredLength();
	}

};

#endif