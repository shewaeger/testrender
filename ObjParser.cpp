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
	std::vector<std::vector<std::tuple<int, int, int>>> faces;

	std::ifstream file(this->filename);
	std::string line;

	while(!file.eof()) {
		std::getline(file, line);
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
			std::vector<std::tuple<int, int, int>> face;

			while(std::regex_search(data, matches, std::regex(FACE_VERTEX_REGEX))) {
				int vertexNum, textureNum = -1, normalNum = -1;
				vertexNum = std::stoi(matches[1]);
				if(matches[2].matched) {
					textureNum = std::stoi(matches[2]);
				}
				if(matches[4].matched) {
					normalNum = std::stoi(matches[4]);
				}

				face.emplace_back(vertexNum, textureNum, normalNum);
				data = matches.suffix();
			}
			faces.push_back(face);
		}
	}

	RObject object;

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
