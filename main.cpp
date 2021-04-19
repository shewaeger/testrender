#include "ObjParser.h"
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "it work");

//	ObjParser parser("/home/shewa/notebook/projects/testrender/head.obj");
//
//	RObject object = parser.load();

	sf::Image image;
	image.create(800, 600);
	sf::Texture texture;
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
