//
// Created by shewa on 25.04.2021.
//

#ifndef TESTRENDER_MATRIX4X4_H
#define TESTRENDER_MATRIX4X4_H


#include <cstdlib>
#include "Vector3d.h"
#include "Vertex3d.h"

class Matrix4x4 {
private:
	float values[4][4]{};
public:
	Matrix4x4() = default;
	Matrix4x4(float basis[4][4]);

	enum Axis {OX = 1, OY = 2, OZ = 4, ALL = 0xff};
	static Matrix4x4 rotate(float rad, Axis axis);
	static Matrix4x4 move(Vector3d const& vector);
	static Matrix4x4 translate(float x, float y, float z);
	static Matrix4x4 mirror(Axis axis, Vector3d const& point = Vector3d(0, 0, 0));
	static Matrix4x4 scale(float k, Axis axis = Axis::ALL);
	static Matrix4x4 identity();
	float get(size_t i, size_t j) const;
	Matrix4x4 & operator =(float basis[4][4]);
};

Matrix4x4 operator*(Matrix4x4 const &l, Matrix4x4 const &r);
Matrix4x4 operator*(Matrix4x4 const &l, float r);
Vector3d  operator*(Matrix4x4 const &l, Vector3d const &r);
Vertex3d  operator*(Matrix4x4 const &l, Vertex3d const &r);
Matrix4x4 operator+(Matrix4x4 const &l, Matrix4x4 const &r);

#endif //TESTRENDER_MATRIX4X4_H
