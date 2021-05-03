//
// Created by shewa on 19.04.2021.
//

#include <stdexcept>
#include <math.h>
#include "Video.h"
#include "AngleConverter.hpp"

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

void Video::drawTriangle(const std::vector<Vertex3d> &face, float zBuffer[], size_t zBufferSize, sf::Color const &color) {
	auto imageSize = image.getSize();
	if(face.size() != 3) {
		throw std::invalid_argument("Unable to draw triangle");
	}
	auto fx = [](Vertex3d const &start, Vertex3d const &end, int y) -> int {
		// функция прямой через две точки
		int y0 = start.getY(), x0 = start.getX(), y1 = end.getY(), x1 = end.getX();
		if(y1 - y0 == 0) {
			return x0;
		}
		return y1 - y0 == 0 ? x0 : (y - y0)*(x1 -x0) / (y1 - y0) + x0;
	};


	auto faceFunction = [face](float x, float y) -> float {
		// функция площади через три точки
		float x0 = face[0].getX(), y0 = face[0].getY(), z0 = face[0].getZ();
		float x1 = face[1].getX(), y1 = face[1].getY(), z1 = face[1].getZ();
		float x2 = face[2].getX(), y2 = face[2].getY(), z2 = face[2].getZ();

		float a11 = x - x0, a12 = x1 - x0, a13 = x2-x0,
				a21 = y - y0, a22 = y1 - y0, a23 = y2-y0,
		/*a31 = z - z0*/ a32 = z1 - z0, a33 = z2-z0;
		if(a13 == 0 || a22 == 0 || a12 == 0 || a23 == 0)
			return z0;
		return (a11*a22*a33 - a11*a23*a32 - a12*a21*a33 + a13*a21*a32)/(a13*a22 - a12*a23) + z0;
	} ;

	for(int i = (int)face[0].getY(); i <= (int)face[2].getY(); i++ ) {
		size_t currentPoint = i <= face[1].getY() ? 0 : 1;
		int startDraw = fx(face[currentPoint], face[currentPoint + 1], i);
		int endDraw = fx(face[0], face[2], i);
		if(startDraw > endDraw)
			std::swap(startDraw, endDraw);
		endDraw = endDraw >= imageSize.x ? imageSize.x - 1 : endDraw;
		startDraw = startDraw < 0 ? 0 : startDraw;
		for(int j = startDraw; j <= endDraw; j++) {
			float zCoord = faceFunction(j, i);
			if(zBuffer[i * imageSize.x + j] > zCoord) {
				zBuffer[i * imageSize.x + j] = zCoord;
				image.setPixel(j, i, color);
			}
		}
	}
}

void Video::drawRasterizedMesh(RObject &object, sf::Color const &color) {
	auto size = image.getSize();
	size_t bufferSize = size.x * size.y;
	auto zBuffer = new float[bufferSize];

	for(int i = 0; i < bufferSize; i++) {
		zBuffer[i] = std::numeric_limits<float>::min();
	}

	Matrix4x4 conv = Matrix4x4::translate(400, 300, 0) * Matrix4x4::scale(250) * Matrix4x4::rotate(to_radians(30), Matrix4x4::OZ);
	object.convert(conv);

	for(int i = 0; i < object.getFacesCount(); i++){
		auto face = object.getFacesVertexes(i);

//		for(int j = 0; j < face.size(); j ++) {
//			face[j] = face[j] * 250;
//			face[j].setX(face[j].getX() + 400);
//			face[j].setY(face[j].getY() + 300);
//		}

		Vector3d normal = (face[0].getNormal() + face[1].getNormal() + face[2].getNormal()).makeUnit();
		float intenc = normal*this->lightDirection;
		if(intenc < 0) {
			continue;
		}
//		intenc = std::abs(intenc);
		drawTriangle(face, zBuffer, bufferSize, sf::Color(255 * intenc, 255 * intenc, 255 * intenc));
	}
}

void Video::setLightDirection(Vector3d const &vector) {
	this->lightDirection = vector.makeUnit();
}
