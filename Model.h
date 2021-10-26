//
// Created by flo on 10/19/2021.
//

#ifndef NOMPROJET_MODEL_H
#define NOMPROJET_MODEL_H

#include "Graphics.h"
#include "Point.h"
#include "Node.h"
#include<bits/stdc++.h>

using namespace std;

class Model {

    const double TRANSPORTER_SPEED = 2.0;
    const char* INPUT_FILE_NAME;
    bool debugDrawEnabled;
    Point A,B;
    vector<Node> tras;
    int L;

    struct Edge{
        double time;
    };

    struct Triangle{
        Point a;
        Point b;
        Point c;

        void printDistances() {
            cout << a.distanceFromPoint(b) << " " << b.distanceFromPoint(c) << " ";
        }
    };

    Edge g[MAXN][MAXN];

    set <pair <double,int> > coda;
    vector <double> d;
    vector <bool> b;
    vector <int> pi;

    void connectEdges(){

        g[A.id][B.id] = {A.distanceFromPoint(B)}; // walk
        // connect all lines together
        for (Node l : tras) {
            //g[A.id][l.getId()] = {reduceToNode(A).distanceFromNode(l)}; // walk
            for(Node other : tras)
                if (l.getId() != other.getId())
                    g[l.getId()][other.getId()] = {l.distanceFromNode(other)}; // change transport

            //g[l.getId()][B.id] = {l.distanceFromNode(reduceToNode(B))}; // walk
        }
    }

    void initLines(){
        tras.clear();
        cin>>L;
        int inc_id=0;
        REP(i,L){
            Point da,a;
            cin>>da.x>>da.y>>a.x>>a.y;
            da.id = inc_id++;
            tras.push_back({da,a});
        }
        A.id=inc_id++;
        B.id=inc_id++;

        tras.push_back(reduceToNode(A));
        tras.push_back(reduceToNode(B));
    }

    void initStartAndEnd(){
        cin>>A.x>>A.y>>B.x>>B.y;
    }

    void printGraph(){
        REP(i,L+1){
            REP(j,L+1)
                cout << i << " -> " << j << "," <<  g[i][j].time << endl;
        }
    }

    void clearAll() {
        coda.clear();
        pi.clear();
        d.clear();
        b.clear();
    }

public:

    Model(const char *const fileName){
        this->INPUT_FILE_NAME=fileName;
        this->debugDrawEnabled = false;
    }

    Model(const char *const fileName,bool debugDrawEnabled){
        this->INPUT_FILE_NAME=fileName;
        this->debugDrawEnabled = debugDrawEnabled;
    }

    Graphics DEBUG_DRAW;

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

    pii puntoToPii(Point p){
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

    Node reduceToNode(Point p) {
        return {p, p};
    }

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

    char np(int y) {
        return ((char)(y==B.id ? 'B' : ((y==A.id ? 'A' : (y+'0')))));
    }

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

        while(!coda.empty()){
            auto it=coda.begin();
            int x = (*it).second;
            coda.erase(it);

            // single source single destination ?
            if(x==B.id) return d[B.id];

            REP (i,L+2) {
                if (i==x || i==A.id) continue;

                Triangle arch = calcArch(x,i);

                Point from = arch.a;
                Point to = arch.b;
                Point lastTouch = arch.c;

                //DEBUG_DRAW.drawLine(to.x + 2, to.y + 2 ,from.x+2,from.y+2,"red");

                //if(x==A.id)
                //if (to.liesOn(from,to)) DEBUG_DRAW.drawLine(to.x + 2,to.y + 2,lastTouch.x + 2, lastTouch.y + 2,"yellow");

                double hypot = to.distanceFromPoint(lastTouch);

                double zed = hypot + distanceBetween(from.x,from.y,to.x,to.y) / TRANSPORTER_SPEED;
                // relax
                relax(x,i,d[x]+zed);
            }
        }

        return d[B.id];
    }

    Triangle calcArch(int from, int to) {

        pair<Point,Point> latestJoint = tras[from].pathToNode(tras[to]);
        pair<Point,Point> jointBeforeLatest = tras[pi[from]].pathToNode(tras[from]);

        Point tFrom = jointBeforeLatest.second;
        Point tTo = latestJoint.first;
        Point lastTouch = latestJoint.second;

        Point intersect = lastTouch.closestPointToInfiniteLine(tFrom, tTo);

        double cat1 = Utils::calcCat1(lastTouch.distanceFromInfiniteLine(tFrom, tTo));

        double distanceOnTransporter = intersect.distanceFromPoint(tFrom) - cat1;

        Point t_to2 = tFrom.followByWithInnerBounds(distanceOnTransporter, tFrom,tTo);

        if(false)
        if (from == A.id){
            //Point oIntersect = A.closestPointToInfiniteLine(tras[to].da, tras[to].a); // ?????? him instead lastTouch?
            double cat3 = Utils::calcCat1(A.distanceFromInfiniteLine(tras[to].da, tras[to].a));
            Point lastTouch2 = lastTouch.followByWithInnerBounds(cat3,tras[to].da, tras[to].a);
            //DEBUG_DRAW.drawPoint(lastTouch2.x,lastTouch2.y,2,"blue");

            return {tFrom, t_to2, lastTouch2};
        }
        return {tFrom, t_to2, lastTouch};
    }

    vector<pii> shortestPath() {
        double walk_lenght = dij();

        int cur=B.id;
        vector<Point> points;
        //cout<<"(";
        while(cur!=A.id) {
            //pair<Point,Point> connector = tras[cur].pathToNode(tras[pi[cur]]);
            Triangle connector = calcArch(pi[cur],cur);
            cur=pi[cur];
            points.emplace_back(connector.c);
            points.emplace_back(connector.b);

            //connector.printDistances();
        }
        //cout << ")\n";

        vector<pii> path;
        REP(i,points.size()) path.push_back(puntoToPii(points[i]));
        return path;
    }

    double shortestPathTimeSec() {
        return d[B.id];
    }

    void addLine(int x1, int y1, int x2, int y2) {
     //   Point da = {x1,y1};
     //   Point a = {x2,y2};
     //   tras.push_back({x1,y1,x2,y2});
    }

    pii deMapCoord(int x, int y) {
        return {x,y};
    }
};

/*
 *
 * // ULTIMO TRASPORTATORE PRESO
                // DEBUG_DRAW.drawLine(to.x + 2, to.y + 2 ,from.x+2,from.y+2,"red");
                // ULTIMO TRATTO A PIEDI
                // if (to.liesOn(from,to)) DEBUG_DRAW.drawLine(to.x + 2,to.y + 2,lastTouch.x + 2, lastTouch.y + 2,"yellow");

                 // else zed = g[x][i].time + distanceBetween(t_from.x,t_from.y,t_to.x,t_to.y) / TRANSPORTER_SPEED;


         cout<<"(";
        double totalTime = 0;
        REP(i,points.size()-1) {
            double mem = points[i].distanceFromPoint(points[i+1]) / ((i%2!=0) ? TRANSPORTER_SPEED :1.0);
            cout << mem << " , ";
            totalTime += mem ;
        }
        cout<<")\n";

 */

#endif //NOMPROJET_MODEL_H
