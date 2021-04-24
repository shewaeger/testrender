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
	void drawLine(int x0, int y0, int x1, int y1, sf::Color &color);
public:
	explicit Video(unsigned x, unsigned y);
	void drawLinedMesh(RObject &object);
	sf::Image &getImage();
};


#endif //TESTRENDER_VIDEO_H