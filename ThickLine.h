//
// Created by flo on 10/26/2021.
//

#ifndef NOMPROJET_THICKLINE_H
#define NOMPROJET_THICKLINE_H

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Utils.h"

using namespace sf;

class ThickLine : public Drawable{

public:

    float x1,y1,x2,y2;
    float RECT_HEIGHT;
    Color color;
    Texture* texture = NULL;

    ThickLine(float x1, float y1, float x2, float y2,float thick = 15,Color color = Color::Black) {
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
        this->RECT_HEIGHT = thick;
        this->color = color;
    }

    ThickLine(Vector2<float> p1, Vector2<float> p2,float thick = 15,Color color = Color::Black){
        this->x1=p1.x;
        this->y1=p1.y;
        this->x2=p2.x;
        this->y2=p2.y;
        this->RECT_HEIGHT = thick;
        this->color = color;
    }

    void draw(RenderTarget &target, RenderStates states) const override {

        float angle = Utils::angleBetween(x1,y1,x2,y2);
        float rectWidth = Utils::pDistances(x1,y1,x2,y2);
        float originX = rectWidth / 2;
        float originY = RECT_HEIGHT / 2;
        float posX = (x1 + x2) / 2;
        float posY = (y1 + y2) / 2;

        if (!texture){
            RectangleShape rectangle = createRect(angle,rectWidth,RECT_HEIGHT,originX,originY,posX,posY,color);
            target.draw(rectangle,states);
        } else {
            Sprite sprite = createSprite(angle,rectWidth,RECT_HEIGHT,originX,originY,posX,posY);
            target.draw(sprite,states);
        }
        /*
        if (!texture) line.setFillColor(color);
        else {
            texture->setRepeated(true);
            //line.setTextureRect({ 0, 0, 100, 100 });
            line.setTexture(texture,true);
        }
        target.draw(line,states);
         */
    }

    RectangleShape createRect(float angle,float rectWidth,float rectHeight,float originX,float originY,float posX,float posY,Color color) const {
        RectangleShape line({rectWidth, rectHeight});
        line.setOrigin(originX, originY);
        line.setPosition(posX, posY);
        line.rotate(angle);
        line.setFillColor(color);
        return line;
    }

    Sprite createSprite(float angle,float rectWidth,float rectHeight,float originX,float originY,float posX,float posY) const {
        Sprite line;
        line.setTextureRect({ 0, 0, static_cast<int>(rectWidth), static_cast<int>(rectHeight) });
        line.setScale(-1,1);
        line.setOrigin(originX, originY);
        line.setPosition(posX, posY);
        line.rotate(angle);
        line.setTexture(*texture);
        cout << "qui";
        return line;
    }

    void applySprite(Texture* texture){
        this->texture = texture;
    }
};



#endif //NOMPROJET_THICKLINE_H
