//
// Created by shewa on 18.04.2021.
//

#ifndef TESTRENDER_VERTEX3D_H
#define TESTRENDER_VERTEX3D_H


#include "Vector3d.h"

class Vertex3d : public Vector3d{
	Vector3d normal;
public:
	Vertex3d();

	Vertex3d(float x, float y, float z, float w = 1, Vector3d const &normal = Vector3d());

	Vertex3d(Vertex3d const &vertex);

	void setNormal(Vector3d const &normal);
};


#endif //TESTRENDER_VERTEX3D_H
