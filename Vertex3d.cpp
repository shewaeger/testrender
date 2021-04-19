//
// Created by shewa on 18.04.2021.
//

#include "Vertex3d.h"

Vertex3d::Vertex3d() : Vector3d() {

}

Vertex3d::Vertex3d(float x, float y, float z, float w, Vector3d const &normal):
	Vector3d(x, y, z, w),
	normal(normal)
{}

void Vertex3d::setNormal(Vector3d const &normal) {
	this->normal = normal;
}

Vector3d &Vertex3d::getNormal() {
	return this->normal;
}

Vertex3d::Vertex3d(Vertex3d const &vertex) = default;
