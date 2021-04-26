//
// Created by shewa on 19.04.2021.
//

#include <stdexcept>
#include "Video.h"

void Video::drawLinedMesh(RObject &object, sf::Color const &color) {
	sf::Color red(255, 0,0);
	sf::Color green(0, 255, 0);
	for(size_t i = 0; i < object.getFacesCount(); i++) {
		auto face = object.getFacesVertexes(i);
		for(size_t j = 0; j < face.size(); j++) {
			size_t nextPoint = j < face.size() - 1 ? j + 1 : 0;
			Vertex3d beg = face[j] * 250;
			Vertex3d end = face[nextPoint] * 250;
			this->drawLine(beg.getX() + 400, beg.getY() + 300, end.getX() + 400, end.getY() + 300, j < face.size() - 1 ? red : green);
		}
	}
}

void Video::drawLine(int x0, int y0, int x1, int y1, sf::Color const &color) {
	auto imageSize = image.getSize();
	bool steep = false;
	if (std::abs(x0-x1)< std::abs(y0-y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0>x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1-x0;
	int dy = y1-y0;
	int derror2 = std::abs(dy)*2;
	int error2 = 0;
	int y = y0;
	for (int x=x0; x<=x1; x++) {
		if(y >= 0 && x >= 0 && x <= imageSize.x && y <= imageSize.y) {
			if (steep) {
				image.setPixel(y, x, color);
			} else {
				image.setPixel(x, y, color);
			}
		}
		error2 += derror2;

		if (error2 > dx) {
			y += (y1>y0?1:-1);
			error2 -= dx*2;
		}
	}
}

void Video::drawLine(Vertex3d const &begin, Vertex3d const &end, sf::Color const &color) {
	this->drawLine(begin.getX(), begin.getY(), end.getX(), end.getY(), color);
}

Video::Video(unsigned x, unsigned y){
	image.create(x, y);
}

sf::Image &Video::getImage() {
	return this->image;
}

void Video::drawTriangle(const std::vector<Vertex3d> &face, sf::Color const & color) {
	if(face.size() != 3) {
		throw std::invalid_argument("Unable to draw triangle");
	}
	auto fx = [](Vertex3d const &start, Vertex3d const &end, int y) -> int {
		int y0 = start.getY(), x0 = start.getX(), y1 = end.getY(), x1 = end.getX();
		if(y1 - y0 == 0) {
			return x0;
		}
		return y1 - y0 == 0 ? x0 : (y - y0)*(x1 -x0) / (y1 - y0) + x0;
	};
	for(int i = (int)face[0].getY(); i <= (int)face[2].getY(); i++ ) {
		size_t currentPoint = i <= face[1].getY() ? 0 : 1;
		int startDraw = fx(face[currentPoint], face[currentPoint + 1], i);
		int endDraw = fx(face[0], face[2], i);
		if(startDraw > endDraw)
			std::swap(startDraw, endDraw);
		for(int j = startDraw; j < endDraw; j++) {
			image.setPixel(j, i, color);
		}
	}
}

void Video::drawRasterizedMesh(RObject &object, sf::Color const &color) {
	for(int i = 0; i < object.getFacesCount(); i++){
		auto face = object.getFacesVertexes(i);
		for(int j = 0; j < face.size(); j ++) {
			face[j] = face[j] * 250;
			face[j].setX(face[j].getX() + 400);
			face[j].setY(face[j].getY() + 300);
		}

		Vector3d normal = (face[0].getNormal() + face[1].getNormal() + face[2].getNormal()).makeUnit();
		float intenc = normal*this->lightDirection;
		if(intenc < 0) {
			continue;
		}
		drawTriangle(face, sf::Color(255 * intenc, 255 * intenc, 255 * intenc));
	}
}

void Video::setLightDirection(Vector3d const &vector) {
	this->lightDirection = vector.makeUnit();
}
