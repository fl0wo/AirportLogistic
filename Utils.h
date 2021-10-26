//
// Created by flo on 10/22/2021.
//

#ifndef NOMPROJET_UTILS_H
#define NOMPROJET_UTILS_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>

#define MAXN 1000
#define x_ first
#define y_ second
#define da_ first
#define a_ second
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(i,n) FOR(i,0,n-1)
#define abs2(a) (a<0?-a:a)
#define PII 3.141592653589793238463
#define GETMS  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()


using namespace std;
using namespace sf;

typedef pair<int,int> pii;

struct Utils{
    static int abs(int a) { return a < 0 ? -a : a; }
    static double min4(double a, double b, double c, double d) { return min(a, min(b, min(c, d))); }

    static double calcCat1(double cat2) { return ((2 * cat2) / sqrt(3)) / 2; }

    static double calcIpot(double cat1) { return cat1 * 2; }

    static float pDistances(float x1,float y1, float x2, float y2){
        return hypot(x1-x2,y1-y2);
    }

    static float angleBetween(float x1,float y1, float x2, float y2){
        float wx = x1-x2;
        float wy = y1-y2;
        float angleInRadian = std::atan2(wx,wy);
        float angleInDegree = angleInRadian*180.0F/PII;
        return -angleInDegree+90;
    }

    static unsigned long getCurrentMs() {
        unsigned long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return now;
    }

    static Image translateImage(Image image, int offsetPixelsX, int offsetPixelsY) {
        sf::Image img;
        int W = image.getSize().x;
        int H = image.getSize().y;
        img.create(W, H);
        REP(x,W) {
            REP(y,H) {
                img.setPixel(x, y, image.getPixel((x+offsetPixelsX)%W,(y+offsetPixelsY)%H));
            }
        }
        return img;
    }
};


#endif //NOMPROJET_UTILS_H
