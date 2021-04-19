//
// Created by shewa on 18.04.2021.
//

#include <fstream>
#include <string>
#include <regex>
#include "ObjParser.h"
#include "Logger.hpp"

#define COMMENT_REGEX R"(\s*#.*)"
#define VERTEX_REGEX R"(\s*v\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)(\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?))?)"
#define VERTEX_NORMALS_REGEX R"(\s*vn\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)\s+([+-]?([0-9]*[.])?[0-9]+(e[+-]?\d+)?)\s*)"
#define FACE_REGEX R"(\s*f\s+(.*))"
#define FACE_VERTEX_REGEX R"((\d+)(\/(\d+)?(\/(\d+))?)?)"
ObjParser::ObjParser(const char *filename) {
	this->filename = filename;
}

RObject ObjParser::load() {

	if(!testFile()) {
		throw std::runtime_error("Unable to load file");
	}

	std::vector<Vertex3d> vertexes;
	std::vector<Vector3d> normals;
	std::vector<std::vector<std::tuple<long, long, long>>> facesInit;
	std::vector<std::vector<size_t>> faces;

	std::ifstream file(this->filename);
	std::string line;

	while(std::getline(file, line)) {
		std::smatch matches;

		if(std::regex_search(line, std::regex(COMMENT_REGEX))){
			continue;
		}

		if(std::regex_search(line, matches, std::regex(VERTEX_REGEX))) {
			float x, y, z, w = 1;
			x = std::stof(matches[1]);
			y = std::stof(matches[4]);
			z = std::stof(matches[7]);
			if(!matches[11].str().empty()) {
				w = std::stof(matches[11]);
			}

			vertexes.emplace_back(x, y, z, w);
			continue;
		}

		if(std::regex_search(line, matches, std::regex(VERTEX_NORMALS_REGEX))) {
			float x, y, z;
			x = std::stof(matches[1]);
			y = std::stof(matches[4]);
			z = std::stof(matches[7]);
			normals.emplace_back(x, y, z);
			continue;
		}

		if(std::regex_search(line, matches, std::regex(FACE_REGEX))) {
			if(matches.size() != 2) {
				Logger::warning("Corrupted data in file");
				continue;
			}

			std::string data(matches[1]);

			// as in obj file: vertexNum, UV, normalNum
			std::vector<std::tuple<long, long, long>> face;

			while(std::regex_search(data, matches, std::regex(FACE_VERTEX_REGEX))) {
				long vertexNum, textureNum = 0, normalNum = 0;
				vertexNum = std::stol(matches[1]);
				if(matches[3].matched) {
					textureNum = std::stoi(matches[3]);
				}
				if(matches[5].matched) {
					normalNum = std::stoi(matches[5]);
				}

				face.emplace_back(vertexNum, textureNum, normalNum);
				data = matches.suffix();
			}
			facesInit.push_back(face);
		}
	}

	for(const auto& face : facesInit) {
		if(face.empty()) {
			throw std::runtime_error("Face is empty. Check file");
		}
		std::vector<size_t> faceNew;
		for(const auto& tuple : face) {
			long vertexNum, textureNum, normalNum;
			std::tie(vertexNum, textureNum, normalNum) = tuple;
			size_t vertexPos = vertexNum > 0 ? vertexNum - 1 : vertexes.size() + vertexNum;
			Vertex3d &vertex = vertexes.at(vertexPos);
			if(normalNum && vertex.getNormal().isNoLength()) {
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

	return object;
}

bool ObjParser::testFile() {
	std::ifstream file(this->filename);

	if(!file.good()) {
		Logger::info("Unable to load file");
		return false;
	}
	file.close();
	return true;
}