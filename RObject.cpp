//
// Created by shewa on 19.04.2021.
//

#include <stdexcept>
#include "RObject.h"

RObject::RObject()= default;

void RObject::setVertexes(std::vector<Vertex3d> &vertexesNew) {
	this->vertexes = vertexesNew;
}

void RObject::setFaces(std::vector<std::vector<size_t>> &facesNew) {
	this->faces = facesNew;
}


std::vector<Vertex3d> RObject::getFacesVertexes(size_t n) {
	if(n >= faces.size()) {
		throw std::runtime_error("Out of memory");
	}
	auto face = faces[n];
	std::vector<Vertex3d> faceNew;
	faceNew.reserve(face.size());

	for(size_t i : face) {
		faceNew.push_back(vertexes[i]);
	}

	return faceNew;
}

size_t RObject::getFacesCount() const {
	return this->faces.size();
}

std::vector<Vertex3d> RObject::operator[](size_t n) {
	return this->getFacesVertexes(n);
}

void RObject::convert(Matrix4x4 const &matrix) {
	for(size_t i = 0; i < vertexes.size(); i++){
		vertexes[i] = matrix * vertexes[i];
	}
}


