//
// Created by shewa on 18.04.2021.
//

#include "Vector3d.h"

Vector3d::Vector3d(): x(0), y(0), z(0), w(0)
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
