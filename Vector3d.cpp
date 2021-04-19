//
// Created by shewa on 18.04.2021.
//

#include <stdexcept>
#include <cmath>
#include "Vector3d.h"
#include "defines.h"

Vector3d::Vector3d(): x(0), y(0), z(0), w(1)
{}

Vector3d::Vector3d(float x, float y, float z, float w): x(x), y(y), z(z), w(w)
{}

void Vector3d::setX(float x) {
	this->x = x;
}

void Vector3d::setY(float y) {
	this->y = y;
}

void Vector3d::setZ(float z) {
	this->z = z;
}

void Vector3d::setW(float w) {
	this->w = w;
}

Vector3d::Vector3d(Vector3d const &vector) {
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = vector.w;
}

Vector3d &Vector3d::operator=(Vector3d const &vector) {

	if(this == &vector) {
		return *this;
	}

	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = vector.w;

	return *this;
}

bool Vector3d::isUnit() {
	return fabsf(length() - 1) < PRECISION;
}

bool Vector3d::isNoLength() {
	return this->x == 0 && this->y == 0 && this->z == 0;
}

float Vector3d::length() {
	return sqrtf(x*x + y*y + z*z);
}

Vector3d Vector3d::makeUnit() {
	return (*this) / this->length();
}

float Vector3d::getX() const {
	return x;
}
float Vector3d::getY() const {
	return y;
}
float Vector3d::getZ() const {
	return z;
}
float Vector3d::getW() const {
	return w;
}


Vector3d operator/(Vector3d const & left, float num) {
	return Vector3d(left.getX() / num, left.getY() / num, left.getZ() / num);
}