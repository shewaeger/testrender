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

const Vector3d &Vertex3d::getNormal() const {
	return this->normal;
}

Vertex3d::Vertex3d(Vector3d const &vertex, const Vector3d &normal) :
Vector3d(vertex),
normal(normal)
{}

Vertex3d::Vertex3d(Vertex3d const &vertex) = default;

Vertex3d operator*(Vertex3d & left, float num) {
	return Vertex3d(left.getX() * num, left.getY() * num, left.getZ() * num, left.getW(), left.getNormal());
}

Vertex3d operator/(Vertex3d & left, float num) {
	return Vertex3d(left.getX() / num, left.getY() / num, left.getZ() / num, left.getW(), left.getNormal());
}
