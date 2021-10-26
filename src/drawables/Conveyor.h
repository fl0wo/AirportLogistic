//
// Created by flo on 10/26/2021.
//

#ifndef NOMPROJET_CONVEYOR_H
#define NOMPROJET_CONVEYOR_H

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "../logic/Utils.h"
#include "ThickLine.h"

using namespace sf;

class Conveyor : public Drawable{
private:
    string PATH_SPRITE = "C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\input_files\\conveyor_sprite_20_white.png";

public:

    float x1,y1,x2,y2;
    unsigned long lastDrawMs;
    Texture texture;
    bool loadedTexture = false;
    float ANIMATION_MS = 200;

    Conveyor(float x1, float y1, float x2, float y2,unsigned long clock = GETMS) {
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
        this->lastDrawMs = clock;
        this->loadedTexture = texture.loadFromFile(PATH_SPRITE);
    }

    Conveyor(Vector2<float> p1, Vector2<float> p2,unsigned long clock = GETMS){
        this->x1=p1.x;
        this->y1=p1.y;
        this->x2=p2.x;
        this->y2=p2.y;
        this->lastDrawMs = clock;
        this->loadedTexture = texture.loadFromFile(PATH_SPRITE);
    }

    void draw(RenderTarget &target, RenderStates states) const override {
        ThickLine line(x1,y1,x2,y2);
        target.draw(line,states);
    }

    void drawInto(RenderWindow *window) {
        ThickLine line(x1,y1,x2,y2);
        Texture texture2;
        unsigned long curDrawMs = GETMS;
        cout << lastDrawMs << " : " << curDrawMs << endl;
        if(loadedTexture) {
            Image image = texture.copyToImage();

            float delta = (curDrawMs - lastDrawMs) / ANIMATION_MS;
            int offsetX = (image.getSize().x) * delta;

            Image translated = Utils::translateImage(image,offsetX,0);

            texture2.setSmooth(true);
            texture2.setRepeated(true);
            texture2.loadFromImage(translated);
            line.applySprite(&texture2);
        }

        window->draw(line);
    }
};




#endif //NOMPROJET_CONVEYOR_H
