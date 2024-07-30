The program requires SFML to be compiled and executed.
Compilation and execution:
g++ -c polygon.c++

g++ polygon.o -o polygon -lsfml-graphics -lsfml-window -lsfml-system

./polygon


Program Description:

The program is designed to compute and visualize the convex hull of points entered via mouse clicks in an SFML window. The convex hull is the smallest polygon that can enclose all given points.

Functionality Overview
Window Creation:

The main function initializes an SFML window (sf::RenderWindow) with dimensions 800x600 and the title "Convex Hull with SFML".
Point Struct:

A Point struct is defined to store the x and y coordinates of each point. The struct includes a constructor for easy initialization.
Event Handling:

The program runs an event loop (window.isOpen()) to handle window events. It checks for two main events:
Window Close Event: Closes the window when the close button is clicked.
Mouse Click Event: Records the coordinates of the left mouse button click and adds them to a vector of points.
Drawing Points:

For each recorded point, a small red circle (sf::CircleShape) is drawn at the clicked location. The circle's position is adjusted to center it on the point.
Convex Hull Calculation:

The convex hull is calculated using Graham's scan algorithm, which is more efficient than the naive O(n2) method. Graham's scan has a time complexity of O(nlogn).
If the number of points is at least three, the algorithm constructs the convex hull by sorting the points and then iteratively determining which points form the boundary of the hull.
Drawing Convex Hull:

The points forming the convex hull are connected by lines (sf::VertexArray), which are drawn in blue to distinguish them from the input points.
