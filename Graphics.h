//
// Created by flo on 10/19/2021.
//

#ifndef NOMPROJET_GRAPHICS_H
#define NOMPROJET_GRAPHICS_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Graphics {

    RenderWindow* window;
    int WINDOW_BORDER=10; // percentage border

public:

    int originXY = 100;
    int sizeXY = 200;

    void initWindow(int W,int H,string title){
        window = new RenderWindow(VideoMode(W, H), title);

        // REMOVE
        /*View view;
        view.setCenter(mapPoint(originXY, originXY));
        view.setSize(Vector2f(sizeXY, sizeXY));
        window->setView(view);
*/
    }

    void bindOnInit(void (*drawLogic)(),void (*controllerLogic)(Event)) {
        while (window->isOpen()) {
            Event event;

            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                controllerLogic(event);
            }

            window->clear(sf::Color::Black);
            drawLogic();
            window->display();
        }
    }

    void drawLine(int x1, int y1, int x2, int y2,
                  string color="white") {

        Vertex line[] = {Vertex(mapPoint(x1, y1),mapColor(color)),
                         Vertex(mapPoint(x2, y2),mapColor(color))};

        window->draw(line, 2, Lines);
    }

    void drawLineRaw(float x1, float y1, float x2, float y2,
                  string color="white") {

        Vertex line[] = {Vertex(Vector2f(x1, y1),mapColor(color)),
                         Vertex(Vector2f(x2, y2),mapColor(color))};

        window->draw(line, 2, Lines);
    }

    Vector2f mapPoint(float x,float y){
        x += window->getSize().x * WINDOW_BORDER / 100;
        y = window->getSize().y -
                (window->getSize().y*WINDOW_BORDER/100)
                - y;
        return Vector2f(x, y);
    }

    pair<float,float> deMapPoint(float x,float y){
        // x : wSize == ? : 200
        // ? x*200)/wSize
        // x = (x*sizeXY)/600.0f;
        // y = (y*sizeXY)/600.0f;
        x -= window->getSize().x * WINDOW_BORDER / 100;
        y = window->getSize().y -
            (window->getSize().y*WINDOW_BORDER/100)
            - y;
        return {x,y};
    }

    const Color& mapColor(string colorName) {

        if (colorName == "red") return Color::Red;
        if (colorName == "white") return Color::White;
        if (colorName == "magenta") return Color::Magenta;
        if (colorName == "yellow") return Color::Yellow;
        if (colorName == "blue") return Color::Blue;

        return Color::Green;
    }

    void drawPoint(int x, int y, float r=5.0, string color="red") {
        CircleShape circle(r);
        circle.setFillColor(mapColor(color));
        circle.setPosition(mapPoint(x-r,y+r));
        window->draw(circle);
    }

    RenderWindow* getWindow() {
        return window;
    }

};


#endif //NOMPROJET_GRAPHICS_H
