#include "ObjParser.h"
#include "Video.h"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "it work");

	auto parser = new ObjParser("/home/shewa/notebook/projects/testrender/head.obj");
	RObject object = parser->load();
	delete parser;

	Video video(800, 600);

	video.setLightDirection(Vector3d(1, 1, 1));
	video.drawRasterizedMesh(object, sf::Color(255, 0, 0));

	sf::Texture texture;
	sf::Image &image = video.getImage();
	image.flipVertically();
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	while(window.isOpen()) {
		sf::Event event{};
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

}
