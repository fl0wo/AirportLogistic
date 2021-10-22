//
// Created by flo on 10/22/2021.
//

#include<iostream>
#include "Node.h"

int testDistancePointFromLine(){
    Point v = {0, 0};
    Node x;
    x.da = {-1,3};
    x.a = {3,3};
    std::cout << v.distanceFromLine(x.da,x.a);
}

int testDistanceTwoLines(){
    Node a = {{0, 0}, {1, 1}};
    Node b = {{2, 2}, {3, 3}};
    std::cout << a.distanceFromNode(b);
}