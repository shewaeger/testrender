//
// Created by shewa on 19.04.2021.
//

#ifndef TESTRENDER_ROBJECT_H
#define TESTRENDER_ROBJECT_H


#include <vector>
#include "Vertex3d.h"

class RObject {

private:
	std::vector<Vertex3d> vertexes;

	std::vector<std::vector<size_t>> faces;

public:

	RObject();

	void setVertexes(std::vector<Vertex3d> &vertexesNew);
	void setFaces(std::vector<std::vector<size_t>> &facesNew);
	size_t getFacesCount() const;
	std::vector<Vertex3d> getFacesVertexes(size_t n);
	std::vector<Vertex3d> operator[](size_t n);
};


#endif //TESTRENDER_ROBJECT_H
