//
// Created by flo on 10/22/2021.
//

#ifndef NOMPROJET_UTILS_H
#define NOMPROJET_UTILS_H

#define MAXN 1000
#define x_ first
#define y_ second
#define da_ first
#define a_ second
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(i,n) FOR(i,0,n-1)

using namespace std;

typedef pair<int,int> pii;

struct Utils{
    static int abs(int a) { return a < 0 ? -a : a; }
    static double min4(double a, double b, double c, double d) { return min(a, min(b, min(c, d))); }

    static double calcCat1(double cat2) { return ((2 * cat2) / sqrt(3)) / 2; }

    static double calcIpot(double cat1) { return cat1 * 2; }


};


#endif //NOMPROJET_UTILS_H
