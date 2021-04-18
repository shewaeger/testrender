//
// Created by shewa on 18.04.2021.
//

#ifndef TESTRENDER_OBJPARSER_H
#define TESTRENDER_OBJPARSER_H


#include <vector>
#include <tuple>
#include "Vertex3d.h"
#include "RObject.h"

class ObjParser {

private:
	const char* filename;

	bool testFile();

public:
	explicit ObjParser(const char *filename);

	RObject load();
};


#endif //TESTRENDER_OBJPARSER_H
