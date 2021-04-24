//
// Created by shewa on 19.04.2021.
//

#include "Video.h"

void Video::drawLinedMesh(RObject &object) {
	sf::Color color(255, 0, 0);
	for(size_t i = 0; i < object.getFacesCount(); i++) {
		auto face = object.getFacesVertexes(i);
		for(size_t j = 0; j < face.size(); j++) {
			size_t nextPoint = j < face.size() - 1 ? j + 1 : 0;
			Vertex3d beg = face[j] * 250;
			Vertex3d end = face[nextPoint] * 250;
			this->drawLine(beg.getX() + 400, beg.getY() + 300, end.getX() + 400, end.getY() + 300, color);
		}
	}
}

void Video::drawLine(int x0, int y0, int x1, int y1, sf::Color &color) {
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
		if(y >= 0 && x >= 0) {
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

Video::Video(unsigned x, unsigned y){
	image.create(x, y);
}

sf::Image &Video::getImage() {
	return this->image;
}
