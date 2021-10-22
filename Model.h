//
// Created by flo on 10/19/2021.
//

#ifndef NOMPROJET_MODEL_H
#define NOMPROJET_MODEL_H

#include<bits/stdc++.h>
#include <math.h>
#include "Graphics.h"

#define MAXN 1000
#define INF 1000000
#define x_ first
#define y_ second
#define da_ first
#define a_ second
#define mp make_pair
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(i,n) FOR(i,0,n-1)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;

static const char *const INPUT_FILE_NAME = "C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\in.txt";

class Model {

    static int abs(int a){return a < 0 ? -a : a;}
    static double min4(double p1, double p2, double p3, double p4){return min(p1, min(p2, min(p3, p4)));}

    struct point{
        double x;
        double y;
        int id=-1;

        point(){
            this->x=0;
            this->y=0;
        }

        point(double x1, double y1){
            this->x=x1;
            this->y=y1;
        }

        double distanceFromPoint(point b){
            return hypot(x-b.x,y-b.y);
        }

        point closestPointToLine(point a, point b) {

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


        double distanceFromLine(point a, point b) {
            return distanceFromPoint(closestPointToLine(a,b));
        }

        double distanceFromInfiniteLine(point a, point b) {
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

        bool equals(point p) {
            return x==p.x && y==p.y;
        }

        point followBy(double distance, point a, point b) {

            double vx = b.x - a.x;
            double vy = b.y - a.y;

            double mag = sqrt(vx*vx + vy*vy);

            vx /= mag;
            vy /= mag;

            double px = a.x + vx * (distance);
            double py = a.y + vy * (distance);

            return {px,py};
        }

        point followByWithBounds(double distance, point a, point b) {
            double mag = hypot(b.x - a.x,b.y - a.y);
            if (distance>=mag) return b;
            if (distance<0) return a;
            return followBy(distance,a,b);
        }

    };

    struct node{
        point da;
        point a;

        int mult=1;

        node(){
            this->da=point();
            this->a=point();
            this->mult=1;
        }

        node(point da, point a){
            this->da=da;
            this->a=a;
            this->mult=1;
        }

        double lunghezza(){
            return hypot(da.x - a.x, da.y - a.y);
        }

        double distanceFromNode(node b){
            double p1 = da.distanceFromLine(b.da,b.a);
            double p2 = a.distanceFromLine(b.da,b.a);
            double p3 = b.da.distanceFromLine(da,a);
            double p4 = b.a.distanceFromLine(da,a);
            return min4(p1,p2,p3,p4);
        }

        pair<point,point> pathToNode(node b){
            point p1 = da.closestPointToLine(b.da, b.a);
            point p2 = a.closestPointToLine(b.da, b.a);
            point p3 = b.da.closestPointToLine(da, a);
            point p4 = b.a.closestPointToLine(da, a);

            double p1L = da.distanceFromLine(b.da,b.a);
            double p2L = a.distanceFromLine(b.da,b.a);
            double p3L = b.da.distanceFromLine(da,a);
            double p4L = b.a.distanceFromLine(da,a);

            double minCat = min4(p1L,p2L,p3L,p4L);

            if (minCat == p1L){
                return mp(da,
                          p1);//.followByWithBounds(-calcCat1(da.distanceFromInfiniteLine(b.da,b.a)),b.da,b.a));

            }else if (minCat == p2L){
                return mp(a,//.followByWithBounds(+calcCat1(p2.distanceFromInfiniteLine(da,a)),a,da),
                          p2);

            }else if (minCat == p3L){
                return mp(p3,//.followByWithBounds(calcCat1(p3.distanceFromInfiniteLine(da,a)),da,a),
                        b.da);
            }else if (minCat == p4L){
                return mp(p4,b.a);
            }
        }

        double calcCat1(double cat2){
            return ((2*cat2)/sqrt(3))/2; // unbelievable
        }

        int getId(){
            return da.id;
        }

        bool isPoint() {
            return da.equals(a);
        }

        bool equals(node b) {
            return da.equals(b.da) && a.equals(b.a);
        }
    };

    struct edge{
        int id;
        double time;
    };

    point A,B;
    vector<node> tras;
    edge g[MAXN][MAXN];

    int inc_id=0;
    int L;

    void connectEdges(){

        g[A.id][B.id] = {B.id,A.distanceFromPoint(B)}; // walk
        g[A.id][A.id] = {A.id,0}; // A is already connected to him self

        // connect all lines together
        for (node l : tras) {
            g[A.id][l.getId()] = {l.getId(),reduceToNode(A).distanceFromNode(l)}; // walk
            for(node other : tras)
                if (l.getId() != other.getId())
                    g[l.getId()][other.getId()] = {other.getId(), l.distanceFromNode(other)}; // change transport

            g[l.getId()][B.id] = {B.id,l.distanceFromNode(reduceToNode(B))}; // walk
        }
    }

    void initLines(){
        tras.clear();
        cin>>L;
        inc_id=0;
        REP(i,L){
            point da,a;
            cin>>da.x>>da.y>>a.x>>a.y;
            da.id = inc_id++;
            tras.push_back({da,a});
        }
        A.id=inc_id++;
        B.id=inc_id++;

        //tras.push_back(reduceToNode(A));
        //tras.push_back(reduceToNode(B));

    }

    void initStartAndEnd(){
        cin>>A.x>>A.y>>B.x>>B.y;
    }

    void printGraph(){
        REP(i,L+1){
            REP(j,L+1)
                cout << i << " -> " << g[i][j].id << "," <<  g[i][j].time << endl;
        }
    }

    int testDistancePointFromLine(){
        point v = {0, 0};
        node x;
        x.da = {-1,3};
        x.a = {3,3};
        cout << v.distanceFromLine(x.da,x.a);
    }

    int testDistanceTwoLines(){
        node a = {{0, 0}, {1, 1} };
        node b = {{2, 2}, {3, 3} };
        cout << a.distanceFromNode(b);
    }

    void clearAll() {
        coda.clear();
        pi.clear();
        d.clear();
        b.clear();
        //tras.clear();
    }

public:


    int initModel(){
        freopen(INPUT_FILE_NAME, "r", stdin);
        clearAll();
        initStartAndEnd();
        initLines();
        connectEdges();
        printGraph();
        return 0;
    }

    pii getStartPoint(){
        return puntoToPii(A);
    }

    pii getEndPoint(){
        return puntoToPii(B);
    }

    pii puntoToPii(point p){
        return mp(p.x,p.y);
    }

    vector<pair<pii,pii>> getLines(){
        vector<pair<pii,pii>> lines;
        REP(i,L)
            lines.push_back(mp(
                    puntoToPii(tras[i].da),
                    puntoToPii(tras[i].a)));
        return lines;
    }

    node reduceToNode(point p) {
        return {p, p};
    }

    set <pair <double,int> > coda;
    vector <double> d;
    vector <bool> b;
    vector <int> pi;
    double totalTime=0.0;

    void init_ss(int s){
        d[s] = 0;
        b[s] = true;
        pi[s] = s;
        coda.insert(mp(0,s));
    }

    void relax(int da,int verso, double peso){
        if(d[verso]>peso){
            if(b[verso]) coda.erase(coda.find(make_pair(d[verso],verso)));
            else b[verso]=true;
            d[verso]=peso;
            pi[verso]=da;
            coda.insert(make_pair(d[verso],verso));
        }
    }


    int indexOf(vector<edge> vector, int x) {
        REP(i,vector.size())
            if(vector[i].id==x)
                return i;
        return -1;
    }

    char np(int y) {
        return ((char)(y==B.id ? 'B' : ((y==A.id ? 'A' : (y+'0')))));
    }

    Graphics gg;

    double distanceBetween(double x1, double y1, double x2, double y2) {
        return hypot(x1-x2,y1-y2);
    }

    double dij() {
        coda.clear();
        pi.clear();
        d.clear();
        b.clear();

        d.resize(MAXN,INT32_MAX);
        b.resize(MAXN,false);
        pi.resize(MAXN,-1);

        init_ss(A.id);

        cout << "B.id -> " << B.id << endl;
        cout << "A.id -> " << A.id << endl;

        int x,y;
        double z;

        while(!coda.empty()){
            auto it=coda.begin();
            x = (*it).second;
            coda.erase(it);

            // single source single destination ?
            if(x==B.id){
                return d[B.id];

                int track = x;
                cout<<np(track);
                double total_real = 0;
                while(track!=A.id){

                    pair<point,point> ppp = tras[pi[track]].pathToNode(tras[track]);
                    pair<point,point> ppp2 = tras[pi[pi[track]]].pathToNode(tras[pi[track]]);

                    double t = g[pi[track]][track].time;
                    double zed = distanceBetween(
                            ppp.first.x,ppp.first.y
                            ,ppp2.second.x,ppp2.second.y) /2.0;

                        gg.drawLine(ppp.first.x+2,ppp.first.y+2
                                ,ppp2.second.x+2,
                                    ppp2.second.y+2,
                                    "red");

                    cout << " <- ["<<t<<"] " << np(pi[track]) << " " << zed << " ";
                    total_real+= t + zed;
                    track = pi[track];
                }
                cout << endl <<" total_real " << total_real << endl;

                return d[B.id];
            }

            REP (i,L+2) {
                if (i==x || i==A.id) continue;

                z = g[x][i].time;

                pair<point,point> doveMiStacco = tras[x].pathToNode(tras[i]);
                pair<point,point> doveMiSonoStaccato = tras[pi[x]].pathToNode(tras[x]);

                gg.drawLine(doveMiStacco.first.x+2,doveMiStacco.first.y+2
                        ,doveMiSonoStaccato.second.x+2,
                            doveMiSonoStaccato.second.y+2,
                            "red");

                double zed = distanceBetween(
                        doveMiStacco.first.x,doveMiStacco.first.y,
                        doveMiSonoStaccato.second.x,doveMiSonoStaccato.second.y
                        ) /2.0;
                z+=zed;

                 //relax
                relax(x,i,d[x]+z);
            }
        }

        return d[B.id];
    }

    vector<pii> shortestPath() {
        double walk_lenght = dij();

        cout<<endl<< "total2 :" <<walk_lenght<<"\n";

        tras.push_back(reduceToNode(A));
        tras.push_back(reduceToNode(B));
        int cur=B.id;
        vector<point> points;

        while(cur!=A.id) {
            pair<point,point> connector = tras[cur].pathToNode(tras[pi[cur]]);
            cur=pi[cur];
            points.emplace_back(connector.first);
            points.emplace_back(connector.second);
        }

        cout<<"(";
        totalTime = 0;
        REP(i,points.size()-1) {
            double mem = points[i].distanceFromPoint(points[i+1]) / ((i%2!=0) ? 2.0:1.0);
            cout << mem << " , ";
            totalTime += mem ;
        }
        cout<<")\n";

        vector<pii> path;
        REP(i,points.size()) path.push_back(puntoToPii(points[i]));
        return path;
    }

    double shortestPathTimeSec() {
        return totalTime;
    }
};

/*
     int track = x;
                cout<<np(track);
                double total_real = 0;
                while(track!=A.id){

                    pair<point,point> ppp = tras[pi[track]].pathToNode(tras[track]);
                    pair<point,point> ppp2 = tras[pi[pi[track]]].pathToNode(tras[pi[track]]);

                    double t = g[pi[track]][track].time;
                    double zed = distanceBetween(
                            ppp.first.x,ppp.first.y
                            ,ppp2.second.x,ppp2.second.y) /2.0;

                    if (x!=A.id)
                        gg.drawLine(ppp.first.x+2,ppp.first.y+2
                                ,ppp2.second.x+2,
                                    ppp2.second.y+2,
                                    "red");

                    //cout << " <- ["<<t<<"] " << np(pi[track]) << " " << zed << " ";
                    //total_real+= t + zed;
                    track = pi[track];
                }
                /cout << endl <<" total_real " << total_real << endl;
 */

#endif //NOMPROJET_MODEL_H
