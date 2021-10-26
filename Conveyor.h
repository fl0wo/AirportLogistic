//
// Created by flo on 10/26/2021.
//

#ifndef NOMPROJET_CONVEYOR_H
#define NOMPROJET_CONVEYOR_H


#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "Utils.h"
#include "ThickLine.h"

using namespace sf;

class Conveyor : public Drawable{
private:
    string PATH_SPRITE = "C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\input_files\\conveyor_sprite_15_white.png";

public:

    float x1,y1,x2,y2;

    Conveyor(float x1, float y1, float x2, float y2) {
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
    }

    Conveyor(Vector2<float> p1, Vector2<float> p2){
        this->x1=p1.x;
        this->y1=p1.y;
        this->x2=p2.x;
        this->y2=p2.y;
    }

    void draw(RenderTarget &target, RenderStates states) const override {
        ThickLine line(x1,y1,x2,y2);
        Texture texture;

        if(texture.loadFromFile(PATH_SPRITE)) {
            texture.setSmooth(true);
            texture.setRepeated(true);
            line.applySprite(&texture);
        }

        target.draw(line,states);
    }

};




#endif //NOMPROJET_CONVEYOR_H
