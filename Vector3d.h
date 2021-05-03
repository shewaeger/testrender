//
// Created by shewa on 18.04.2021.
//

#ifndef TESTRENDER_VECTOR3D_H
#define TESTRENDER_VECTOR3D_H


class Vector3d {
protected:
	float x,y,z,w;
public:
	Vector3d();
	Vector3d (float x, float y, float z, float w = 1);
	Vector3d(Vector3d const & vector);
	Vector3d& operator=(Vector3d const& vector);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);

	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;

	bool isUnit() const;
	bool isNoLength() const;
	float length() const;

	Vector3d makeUnit() const ;
};

Vector3d operator+(Vector3d const &left, Vector3d const &right);
Vector3d operator-(Vector3d const &left, Vector3d const &right);
Vector3d operator^(Vector3d const &left, Vector3d const &right);
Vector3d operator/(Vector3d const & left, float num);
Vector3d operator*(Vector3d const & left, float num);
float operator*(Vector3d const & left, Vector3d const & right);
#endif //TESTRENDER_VECTOR3D_H
