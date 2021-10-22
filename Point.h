//
// Created by flo on 10/22/2021.
//

#ifndef NOMPROJET_POINT_H
#define NOMPROJET_POINT_H

#include <math.h>

struct Point{
    double x;
    double y;
    int id=-1;

    Point(){
        this->x=0;
        this->y=0;
    }

    Point(double x1, double y1){
        this->x=x1;
        this->y=y1;
    }

    double distanceFromPoint(Point b){
        return hypot(x-b.x,y-b.y);
    }

    Point closestPointToLine(Point a, Point b) {

        if(a.equals(b)){
            return {a.x,a.y};
        }

        double lineX = b.x - a.x;
        double lineY = b.y - a.y;
        double dot = (x - a.x) * lineX + (y - a.y) * lineY;
        double len_sq = lineX * lineX + lineY * lineY;
        double param = -1;
        double xx;
        double yy;

        if (len_sq != 0) {
            param = dot / len_sq;
        }

        if (param < 0) {
            xx = a.x;
            yy = a.y;
        }
        else if (param > 1) {
            xx = b.x;
            yy = b.y;
        }
        else {
            xx = a.x + param * lineX;
            yy = a.y + param * lineY;
        }

        return {xx,yy};
    }


    double distanceFromLine(Point a, Point b) {
        return distanceFromPoint(closestPointToLine(a,b));
    }

    double distanceFromInfiniteLine(Point a, Point b) {
        double lineX = b.x - a.x;
        double lineY = b.y - a.y;
        double dot = (x - a.x) * lineX + (y - a.y) * lineY;
        double len_sq = lineX * lineX + lineY * lineY;
        double param = -1;
        double xx;
        double yy;
        if (len_sq != 0) {
            param = dot / len_sq;
        }
        xx = a.x + param * lineX;
        yy = a.y + param * lineY;
        return distanceFromPoint({xx,yy});
    }

    bool equals(Point p) {
        return x==p.x && y==p.y;
    }

    Point followBy(double distance, Point a, Point b) {

        double vx = b.x - a.x;
        double vy = b.y - a.y;

        double mag = sqrt(vx*vx + vy*vy);

        vx /= mag;
        vy /= mag;

        double px = a.x + vx * (distance);
        double py = a.y + vy * (distance);

        return {px,py};
    }

    Point followByWithBounds(double distance, Point a, Point b) {
        double mag = hypot(b.x - a.x,b.y - a.y);
        if (distance>=mag) return b;
        if (distance<0) return a;
        return followBy(distance,a,b);
    }

};

#endif //NOMPROJET_POINT_H
