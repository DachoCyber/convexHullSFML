#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {

    RenderWindow window(VideoMode(640, 480), "polygon", Style::Default);
    ConvexShape shape;
    Texture buttonTexture;

    // Define the points of the convex shape
    shape.setPointCount(4);
    shape.setPoint(0, Vector2f(100, 100));
    shape.setPoint(1, Vector2f(200, 100));
    shape.setPoint(2, Vector2f(200, 200));
    shape.setPoint(3, Vector2f(100, 200));
    shape.setFillColor(Color::Green);

    if(!buttonTexture.loadFromFile("stopbtn.png", IntRect(10, 10, 32, 32))) {
        cout << "-1" << endl;
        return EXIT_FAILURE; // Missing semicolon added here
    }

    Sprite sprite;
    sprite.setTexture(buttonTexture);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
        }

        Color color(255, 240, 7, 255);
        window.clear(color);
        window.draw(shape);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

