//
// Created by flo on 10/22/2021.
//

#ifndef NOMPROJET_NODE_H
#define NOMPROJET_NODE_H

#include "Point.h"
#include "Utils.h"

struct Node {
    Point da;
    Point a;

    Node() {
        this->da = Point();
        this->a = Point();
    }

    Node(Point da, Point a) {
        this->da = da;
        this->a = a;
    }

    double distanceFromNode(Node b) {
        double p1 = da.distanceFromLine(b.da, b.a);
        double p2 = a.distanceFromLine(b.da, b.a);
        double p3 = b.da.distanceFromLine(da, a);
        double p4 = b.a.distanceFromLine(da, a);
        return Utils::min4(p1, p2, p3, p4);
    }

    std::pair<Point, Point> pathToNode(Node b) {
        Point p1 = da.closestPointToLine(b.da, b.a);
        Point p2 = a.closestPointToLine(b.da, b.a);
        Point p3 = b.da.closestPointToLine(da, a);
        Point p4 = b.a.closestPointToLine(da, a);

        double p1L = da.distanceFromLine(b.da, b.a);
        double p2L = a.distanceFromLine(b.da, b.a);
        double p3L = b.da.distanceFromLine(da, a);
        double p4L = b.a.distanceFromLine(da, a);

        double minCat = Utils::min4(p1L, p2L, p3L, p4L);

        if (minCat == p1L) {
            return mp(da,p1);
        } else if (minCat == p2L) {
            return mp(a,p2);
        } else if (minCat == p3L) {
            return mp(p3,b.da);
        } else if (minCat == p4L) {
            return mp(p4, b.a);
        }
    }

    int getId() { return da.id; }

    bool isPoint() { return da.equals(a); }

    bool equals(Node b) { return da.equals(b.da) && a.equals(b.a); }

    double lenght() const { return hypot(da.x - a.x, da.y - a.y); }

};


#endif //NOMPROJET_NODE_H
