//
// Created by flo on 10/26/2021.
//

#ifndef NOMPROJET_CONTROLLER_H
#define NOMPROJET_CONTROLLER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <utility>

using namespace sf;

class Controller {

private :
    void (*onLeftClick)(std::pair<int, int>, std::pair<int, int>);
    void (*onLeftMove)(std::pair<int, int>, std::pair<int, int>);

    bool drawingLine=false;

public:

    pii lastMouseClick = {-1,-1};
    pii curMousePos = {-1,-1};

    void bindOnMouseLeft(void (*onLeftClick)(std::pair<int, int>, std::pair<int, int>),
                         void (*onLeftMove)(std::pair<int, int>, std::pair<int, int>)
                         ){
        this->onLeftClick = onLeftClick;
        this->onLeftMove = onLeftMove;
    }

    void performChecks(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                curMousePos = make_pair(event.mouseButton.x, event.mouseButton.y);
                if (drawingLine) {
                    onLeftClick(lastMouseClick,curMousePos);
                } else {
                    lastMouseClick = curMousePos;
                }
                drawingLine = !drawingLine;
            }
        }else if (event.type == sf::Event::MouseMoved && drawingLine) {
            curMousePos = make_pair(event.mouseMove.x, event.mouseMove.y);
            onLeftMove(lastMouseClick,curMousePos);
        }
    }

};


#endif //NOMPROJET_CONTROLLER_H
