//
// Created by shewa on 18.04.2021.
//

#ifndef TESTRENDER_OBJPARSER_H
#define TESTRENDER_OBJPARSER_H


#include <vector>
#include <tuple>
#include "Vertex3d.h"
#include "RObject.h"
#include "Vector2d.h"

class ObjParser {

private:

	enum NodeType {ignore, vertex, face, vertex_normal, vertex_texture, unknown} ;
	const char* filename;
	std::vector<Vertex3d> vertexes;
	std::vector<Vector3d> normals;
	std::vector<std::vector<std::tuple<long, long, long>>> facesInit;

	bool testFile();

	static NodeType getNodeType(std::string const &str);

	static std::string substrArguments(std::string const &str);

	bool generateVertex(std::string const &str);

	bool generateFace(std::string const &str);

	bool generateVertexNormal(std::string const &str);

public:
	explicit ObjParser(const char *filename);

	RObject load();
};


#endif //TESTRENDER_OBJPARSER_H
