#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

float crossProduct(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Point> convexHull(std::vector<Point>& points) {
    std::vector<Point> hull;
    if (points.size() < 3) return hull;

    // Sort points lexicographically (by x, then by y)
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    // Build the lower hull
    for (const auto& p : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Build the upper hull
    size_t lowerHullSize = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        const auto& p = points[i];
        while (hull.size() > lowerHullSize && crossProduct(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    hull.pop_back(); // Remove the last point as it's the same as the first one
    return hull;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Convex Hull with SFML");
    std::vector<Point> points;
    std::vector<Point> hull;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    points.emplace_back(event.mouseButton.x, event.mouseButton.y);
                    hull = convexHull(points);
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw points
        for (const auto& p : points) {
            sf::CircleShape shape(3);
            shape.setPosition(p.x - 3, p.y - 3);
            shape.setFillColor(sf::Color::Red);
            window.draw(shape);
        }

        // Draw convex hull
        if (!hull.empty()) {
            for (size_t i = 0; i < hull.size(); ++i) {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(hull[i].x, hull[i].y), sf::Color::Blue),
                    sf::Vertex(sf::Vector2f(hull[(i + 1)].x, hull[(i + 1)].y), sf::Color::Blue)
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        window.display();
    }

    return 0;
}
