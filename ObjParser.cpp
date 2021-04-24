//
// Created by shewa on 18.04.2021.
//

#include <fstream>
#include <string>
#include <regex>
#include "ObjParser.h"
#include "Logger.hpp"

ObjParser::ObjParser(const char *filename) {
	this->filename = filename;
}

RObject ObjParser::load() {
	Logger::info("Loading file...");
	if (!testFile()) {
		throw std::runtime_error("Unable to load file");
	}


	std::vector<std::vector<size_t>> faces;

	std::ifstream file(this->filename);
	std::string line;
	size_t lineCount = 0;
	while (std::getline(file, line)) {
		lineCount++;
		NodeType nodeType = getNodeType(line);

		switch (nodeType) {
			case ignore:
				continue;
			case unknown: {
				std::stringstream message;
				message << "Unable to parse unknown node. Line: " << lineCount;
				throw std::runtime_error(message.str());
			}
			case vertex:
				if(!generateVertex(substrArguments(line))) {
					std::stringstream message;
					message << "Unable to parse vertex coordinates. Line: " << lineCount;
					throw std::runtime_error(message.str());
				}
				break;
			case face:
				if(!generateFace(substrArguments(line))){
					std::stringstream message;
					message << "Unable to parse face. Line: " << lineCount;
					throw std::runtime_error(message.str());
				}
				break;
			case vertex_normal:
				if(!generateVertexNormal(substrArguments(line))) {
					std::stringstream message;
					message << "Unable to parse vertex normal coordinates. Line: " << lineCount;
					throw std::runtime_error(message.str());
				}
				break;
			case vertex_texture:
				continue;
		}
	}

	for (const auto &face : facesInit) {
		if (face.empty()) {
			throw std::runtime_error("Face is ignore. Check file");
		}
		std::vector<size_t> faceNew;
		faceNew.reserve(face.size());
		for (const auto &tuple : face) {
			long vertexNum, textureNum, normalNum;
			std::tie(vertexNum, textureNum, normalNum) = tuple;
			size_t vertexPos = vertexNum > 0 ? vertexNum - 1 : vertexes.size() + vertexNum;
			Vertex3d &vertex = vertexes.at(vertexPos);
			if (normalNum && vertex.getNormal().isNoLength()) {
				size_t normalPos = normalNum > 0 ? normalNum - 1 : normals.size() + normalNum;
				Vector3d &normal = normals.at(normalPos);
				vertex.setNormal(normal.makeUnit());
			}
			faceNew.push_back(vertexNum);
		}
		faces.push_back(faceNew);
	}

	RObject object;
	object.setFaces(faces);
	object.setVertexes(vertexes);
	Logger::info("Loaded");
	return object;
}

bool ObjParser::testFile() {
	std::ifstream file(this->filename);

	if (!file.good()) {
		Logger::info("Unable to load file");
		return false;
	}
	file.close();
	return true;
}

ObjParser::NodeType ObjParser::getNodeType(std::string const &str) {
	size_t nodeNameStartPos = str.find_first_not_of(" \t");
	if (nodeNameStartPos == std::string::npos || str[nodeNameStartPos] == '#') {
		return NodeType::ignore;
	}

	size_t nodeNameEndPos = str.find_first_of(" \t", nodeNameStartPos);
	if (nodeNameEndPos == std::string::npos) {
		return NodeType::unknown;
	}

	std::string nodeName = str.substr(nodeNameStartPos, nodeNameEndPos);

	if (nodeName == "v") {
		return NodeType::vertex;
	}

	if (nodeName == "vn") {
		return NodeType::vertex_normal;
	}

	if(nodeName == "vt") {
		return NodeType::vertex_texture;
	}

	if (nodeName == "g" || nodeName == "s") {
		return NodeType::ignore;
	}

	if (nodeName == "p") {
		return NodeType::ignore;
	}

	if(nodeName == "f") {
		return NodeType::face;
	}

	if(nodeName == "mtllib" || nodeName == "usemtl") {
		return NodeType::ignore;
	}

	return NodeType::unknown;

}

std::string ObjParser::substrArguments(std::string const &str) {
	size_t nodeNameStartPos = str.find_first_not_of(" \t");
	if (nodeNameStartPos == std::string::npos || str[nodeNameStartPos] == '#') {
		throw std::invalid_argument("Not possible to load arguments from string");
	}

	size_t nodeNameEndPos = str.find_first_of(" \t", nodeNameStartPos);
	if (nodeNameEndPos == std::string::npos) {
		throw std::invalid_argument("Not possible to load arguments from string");
	}

	size_t argsStart = str.find_first_not_of(" \t", nodeNameEndPos);

	return str.substr(argsStart);
}

bool ObjParser::generateVertex(std::string const &str) {
	float x, y, z, w = 1;

	try {
		size_t pos = 0;
		size_t posGlobal = 0;
		x = std::stof(str, &pos);
		posGlobal += pos;
		y = std::stof(str.substr(posGlobal), &pos);
		posGlobal += pos;
		z = std::stof(str.substr(posGlobal));

		if(pos < str.size() && str.find_first_not_of(" \t", pos) != std::string::npos) {
			w = std::stof(str.substr(pos));
		}

		vertexes.emplace_back(x, y, z, w);
	} catch (std::exception &e) {
		Logger::error(e.what());
		return false;
	}

	return true;
}

bool ObjParser::generateFace(std::string const &str) {
	size_t pointStart = 0;
	size_t pointNum = 0;
	long vertex = 0,
		texture = 0,
		normal = 0;

	std::vector<std::tuple<long, long, long>> face;

	while (pointStart != std::string::npos) {
		size_t pointEnd = str.find_first_of(" \t", pointStart);
		if(pointEnd == std::string::npos)
			pointEnd = str.size();

		std::string pointInfo = str.substr(pointStart, pointEnd);
		size_t pos = 0;
		size_t posGlobal = 0;
		vertex = std::stol(pointInfo, &pos);
		posGlobal += pos;
		if(pos < pointInfo.size()) {
			//TODO: validate pointInfo
			posGlobal++;
			if(pointInfo[posGlobal] != '/') {
				texture = std::stol(pointInfo.substr(posGlobal), &pos);
				posGlobal += pos;
			}
			posGlobal++;
			if( pos < pointInfo.size()) {
				normal = std::stol(pointInfo.substr(posGlobal));
			}
		}
		face.emplace_back(vertex, texture, normal);
		pointStart = str.find_first_not_of(" \t", pointEnd);
		pointNum++;
	}

	if(pointNum <=2) {
		return false;
	}

	facesInit.push_back(face);

	return true;
}

bool ObjParser::generateVertexNormal(std::string const &str) {
	float x, y, z, w = 1;

	try {
		size_t pos = 0;
		size_t posGlobal = 0;
		x = std::stof(str, &pos);
		posGlobal += pos;
		y = std::stof(str.substr(posGlobal), &pos);
		posGlobal += pos;
		z = std::stof(str.substr(posGlobal));

		normals.emplace_back(x, y, z, w);
	} catch (std::exception &e) {
		Logger::error(e.what());
		return false;
	}

	return true;
}
