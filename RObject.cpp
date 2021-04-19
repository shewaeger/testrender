//
// Created by shewa on 19.04.2021.
//

#include "RObject.h"

RObject::RObject()= default;

void RObject::setVertexes(std::vector<Vertex3d> &vertexesNew) {
	this->vertexes = vertexesNew;
}

void RObject::setFaces(std::vector<std::vector<size_t>> &facesNew) {
	this->faces = facesNew;
}


