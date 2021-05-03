//
// Created by shewa on 25.04.2021.
//

#include <cmath>
#include <cstring>
#include <stdexcept>
#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::rotate(float rad, Matrix4x4::Axis axis) {
	float sin = std::sin(rad);
	float cos = std::cos(rad);
	if(axis == OX) {
		float value [4][4] =  {
				{1,   0,    0, 0},
				{0, cos, -sin, 0},
				{0, sin,  cos, 0},
				{0,   0,    0, 1}
		};
		return value;
	} else if(axis == OY) {
		float value [4][4] = {
				{cos,  0,  sin, 0},
				{  0,  1,    0, 0},
				{-sin, 0,  cos, 0},
				{   0, 0,    0, 1}
		};
		return value;
	} else if(axis == OZ) {
		float value [4][4] =  {
				{cos, -sin, 0, 0},
				{sin,  cos, 0, 0},
				{  0,    0, 1, 0},
				{  0,    0, 0, 1}
		};
		return value;
	}
	throw std::invalid_argument("Unknown axis");
}

Matrix4x4 Matrix4x4::move(Vector3d const& vector) {
	return translate(vector.getX(), vector.getY(), vector.getZ());
}

Matrix4x4 Matrix4x4::translate(float x, float y, float z) {
	float value [4][4] =  {
			{1, 0, 0, x},
			{0, 1, 0, y},
			{0, 0, 1, z},
			{0, 0, 0, 1}
	};
	return value;
}

Matrix4x4 Matrix4x4::mirror(Matrix4x4::Axis axis, Vector3d const& point) {
	return {};
}

Matrix4x4 Matrix4x4::scale(float k, Matrix4x4::Axis axis) {
	float value [4][4] =  {
			{axis & OX ? k : 1, 0, 0, 0},
			{0, axis & OY ? k : 1, 0, 0},
			{0, 0, axis & OZ ? k : 1, 0},
			{0, 0,                  0, 1}
	};

	return value;
}

Matrix4x4 &Matrix4x4::operator=(float basis[4][4]) {
	memcpy(this->values, basis, sizeof(float) * 4 * 4);
	return *this;
}

Matrix4x4::Matrix4x4(float basis[4][4]) {
	memcpy(this->values, basis, sizeof(float) * 4 * 4);
}

float Matrix4x4::get(size_t i, size_t j) const {
	if(i >= 4 || j >= 4){
		throw std::invalid_argument("i and j great that or equal 4");
	}

	return values[i][j];
}

Matrix4x4 Matrix4x4::identity() {
	float value [4][4] =  {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
	};
	return value;
}

Matrix4x4 operator*(Matrix4x4 const &l, Matrix4x4 const &r) {
	float value [4][4] = {
			{
				l.get(0, 0) * r.get(0, 0) + l.get(0, 1) * r.get(1, 0) + l.get(0, 2) * r.get(2, 0) + l.get(0, 3) * r.get(3, 0),
				l.get(0, 0) * r.get(0, 1) + l.get(0, 1) * r.get(1, 1) + l.get(0, 2) * r.get(2, 1) + l.get(0, 3) * r.get(3, 1),
				l.get(0, 0) * r.get(0, 2) + l.get(0, 1) * r.get(1, 2) + l.get(0, 2) * r.get(2, 2) + l.get(0, 3) * r.get(3, 2),
				l.get(0, 0) * r.get(0, 3) + l.get(0, 1) * r.get(1, 3) + l.get(0, 2) * r.get(2, 3) + l.get(0, 3) * r.get(3, 3),
			},
			{
				l.get(1, 0) * r.get(0, 0) + l.get(1, 1) * r.get(1, 0) + l.get(1, 2) * r.get(2, 0) + l.get(1, 3) * r.get(3, 0),
				l.get(1, 0) * r.get(0, 1) + l.get(1, 1) * r.get(1, 1) + l.get(1, 2) * r.get(2, 1) + l.get(1, 3) * r.get(3, 1),
				l.get(1, 0) * r.get(0, 2) + l.get(1, 1) * r.get(1, 2) + l.get(1, 2) * r.get(2, 2) + l.get(1, 3) * r.get(3, 2),
				l.get(1, 0) * r.get(0, 3) + l.get(1, 1) * r.get(1, 3) + l.get(1, 2) * r.get(2, 3) + l.get(1, 3) * r.get(3, 3),
			},
			{
				l.get(2, 0) * r.get(0, 0) + l.get(2, 1) * r.get(1, 0) + l.get(2, 2) * r.get(2, 0) + l.get(2, 3) * r.get(3, 0),
				l.get(2, 0) * r.get(0, 1) + l.get(2, 1) * r.get(1, 1) + l.get(2, 2) * r.get(2, 1) + l.get(2, 3) * r.get(3, 1),
				l.get(2, 0) * r.get(0, 2) + l.get(2, 1) * r.get(1, 2) + l.get(2, 2) * r.get(2, 2) + l.get(2, 3) * r.get(3, 2),
				l.get(2, 0) * r.get(0, 3) + l.get(2, 1) * r.get(1, 3) + l.get(2, 2) * r.get(2, 3) + l.get(2, 3) * r.get(3, 3),
			},
			{
				l.get(3, 0) * r.get(0, 0) + l.get(3, 1) * r.get(1, 0) + l.get(3, 2) * r.get(2, 0) + l.get(3, 3) * r.get(3, 0),
				l.get(3, 0) * r.get(0, 1) + l.get(3, 1) * r.get(1, 1) + l.get(3, 2) * r.get(2, 1) + l.get(3, 3) * r.get(3, 1),
				l.get(3, 0) * r.get(0, 2) + l.get(3, 1) * r.get(1, 2) + l.get(3, 2) * r.get(2, 2) + l.get(3, 3) * r.get(3, 2),
				l.get(3, 0) * r.get(0, 3) + l.get(3, 1) * r.get(1, 3) + l.get(3, 2) * r.get(2, 3) + l.get(3, 3) * r.get(3, 3),
			}
	};
	return value;
}

Matrix4x4 operator*(Matrix4x4 const &l, float r) {
	float value[4][4] = {
			{l.get(0, 0) * r, l.get(0, 1) * r, l.get(0, 2) * r, l.get(0, 3) * r},
			{l.get(1, 0) * r, l.get(1, 1) * r, l.get(1, 2) * r, l.get(1, 3) * r},
			{l.get(2, 0) * r, l.get(2, 1) * r, l.get(2, 2) * r, l.get(2, 3) * r},
			{l.get(3, 0) * r, l.get(3, 1) * r, l.get(3, 2) * r, l.get(3, 3) * r},
	};
	return value;
}

Vector3d operator*(Matrix4x4 const &l, Vector3d const &r) {
	float x = l.get(0, 0) * r.getX() + l.get(0, 1) * r.getY() + l.get(0, 2) * r.getZ() + l.get(0, 3) * r.getW();
	float y = l.get(1, 0) * r.getX() + l.get(1, 1) * r.getY() + l.get(1, 2) * r.getZ() + l.get(1, 3) * r.getW();
	float z = l.get(2, 0) * r.getX() + l.get(2, 1) * r.getY() + l.get(2, 2) * r.getZ() + l.get(2, 3) * r.getW();
	float w = l.get(3, 0) * r.getX() + l.get(3, 1) * r.getY() + l.get(3, 2) * r.getZ() + l.get(3, 3) * r.getW();

	return Vector3d(x, y, z, w);
}

Vertex3d operator*(Matrix4x4 const &l, Vertex3d const &r) {
	Vector3d v = l * (Vector3d &)r;
//	Vector3d norm = (l * r.getNormal()).makeUnit();

	return Vertex3d(v, r.getNormal());
}

Matrix4x4 operator+(Matrix4x4 const &l, Matrix4x4 const &r) {
	float values[4][4] = {
			{l.get(0, 0) + r.get(0, 0), l.get(0, 1) + r.get(0, 1), l.get(0, 2) + r.get(0, 2), l.get(0, 3) + r.get(0, 3)},
			{l.get(1, 0) + r.get(1, 0), l.get(1, 1) + r.get(1, 1), l.get(1, 2) + r.get(1, 2), l.get(1, 3) + r.get(1, 3)},
			{l.get(2, 0) + r.get(2, 0), l.get(2, 1) + r.get(2, 1), l.get(2, 2) + r.get(2, 2), l.get(2, 3) + r.get(2, 3)},
			{l.get(3, 0) + r.get(3, 0), l.get(3, 1) + r.get(3, 1), l.get(3, 2) + r.get(3, 2), l.get(3, 3) + r.get(3, 3)},
	};
	return values;
}
