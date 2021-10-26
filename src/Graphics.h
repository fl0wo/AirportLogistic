//
// Created by flo on 10/19/2021.
//

#ifndef NOMPROJET_GRAPHICS_H
#define NOMPROJET_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "drawables/Conveyor.h"
#include "drawables/ThickLine.h"

using namespace sf;
using namespace std;

class Graphics {

    RenderWindow* window;
    int WINDOW_BORDER=0; // percentage border
    unsigned long clock; // defines the speed of animations

public:

    int POINT_RADIUS = 7;
    int originXY = 50;
    int sizeXY = 300;

    void initWindow(int W,int H,string title){
        window = new RenderWindow(VideoMode(W, H), title);
        clock = GETMS;
        // REMOVE
        /*
        View view;
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

            window->clear(sf::Color::White);
            drawLogic();
            window->display();
        }
    }

    void drawLine(int x1, int y1, int x2, int y2,string color="green",float thick = 4.0) {
        ThickLine line = ThickLine(mapPoint(x1, y1),mapPoint(x2, y2), thick, mapColor(color));
        window->draw(line);
    }

    void drawTransporter(int x1, int y1, int x2, int y2,string color="black") {
        Conveyor belt = Conveyor(mapPoint(x1, y1),mapPoint(x2, y2),clock);
        //window->draw(belt);
        belt.drawInto(window);
    }

    void drawTransporterRaw(int x1, int y1, int x2, int y2,string color="black") {
        Conveyor belt = Conveyor(x1, y1,x2, y2,clock);
        //window->draw(belt);
        belt.drawInto(window);
    }

    Vector2f mapPoint(float x,float y){
        x += window->getSize().x * WINDOW_BORDER / 100;
        y = window->getSize().y - (window->getSize().y*WINDOW_BORDER / 100) - y;
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
        if (colorName == "black") return Color::Black;

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
