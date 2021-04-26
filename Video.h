//
// Created by shewa on 19.04.2021.
//

#ifndef TESTRENDER_VIDEO_H
#define TESTRENDER_VIDEO_H


#include <SFML/Graphics/Image.hpp>
#include "RObject.h"

class Video {
private:
	sf::Image image;

	Vector3d lightDirection;

public:
	explicit Video(unsigned x, unsigned y);

	void drawLinedMesh(RObject &object, sf::Color const &color);

	void drawLine(int x0, int y0, int x1, int y1, sf::Color const &color);

	void drawLine(Vertex3d const &begin, Vertex3d const &end, sf::Color const &color);

	void drawTriangle(std::vector<Vertex3d> const &face, sf::Color const &color);

	void drawRasterizedMesh(RObject &object, sf::Color const &color);

	void setLightDirection(Vector3d const &vector);

	sf::Image &getImage();
};


#endif //TESTRENDER_VIDEO_H
