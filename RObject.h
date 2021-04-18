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

	std::vector<int> faces;

public:

	RObject();

};


#endif //TESTRENDER_ROBJECT_H
