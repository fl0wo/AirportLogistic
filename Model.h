//
// Created by flo on 10/19/2021.
//

#ifndef NOMPROJET_MODEL_H
#define NOMPROJET_MODEL_H

#include<bits/stdc++.h>
#include "Graphics.h"
#include "Point.h"
#include "Node.h"

using namespace std;

class Model {

    const double TRANSPORTER_SPEED = 2.0;
    const char* INPUT_FILE_NAME;
    bool debugDrawEnabled;

    struct Edge{
        double time;
    };

    Point A,B;
    vector<Node> tras;
    Edge g[MAXN][MAXN];

    int inc_id=0;
    int L;

    void connectEdges(){

        g[A.id][B.id] = {A.distanceFromPoint(B)}; // walk
        g[A.id][A.id] = {0}; // A is already connected to him self

        // connect all lines together
        for (Node l : tras) {
            g[A.id][l.getId()] = {reduceToNode(A).distanceFromNode(l)}; // walk
            for(Node other : tras)
                if (l.getId() != other.getId())
                    g[l.getId()][other.getId()] = {l.distanceFromNode(other)}; // change transport

            g[l.getId()][B.id] = {l.distanceFromNode(reduceToNode(B))}; // walk
        }
    }

    void initLines(){
        tras.clear();
        cin>>L;
        inc_id=0;
        REP(i,L){
            Point da,a;
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
                cout << i << " -> " << j << "," <<  g[i][j].time << endl;
        }
    }

    void clearAll() {
        coda.clear();
        pi.clear();
        d.clear();
        b.clear();
        //tras.clear();
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


    set <pair <double,int> > coda;
    vector <double> d;
    vector <bool> b;
    vector <int> pi;
    double totalTime=0.0;

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


                pair<Point,Point> latestJoint = tras[x].pathToNode(tras[i]);
                pair<Point,Point> jointBeforeLatest = tras[pi[x]].pathToNode(tras[x]);

                DEBUG_DRAW.drawLine(latestJoint.first.x + 2, latestJoint.first.y + 2
                        ,jointBeforeLatest.second.x+2,
                            jointBeforeLatest.second.y+2,
                                    "red");

                double zed = g[x][i].time +
                             distanceBetween(
                                latestJoint.first.x,latestJoint.first.y,
                                jointBeforeLatest.second.x,jointBeforeLatest.second.y) / TRANSPORTER_SPEED;

                // relax
                relax(x,i,d[x]+zed);
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
        vector<Point> points;

        while(cur!=A.id) {
            pair<Point,Point> connector = tras[cur].pathToNode(tras[pi[cur]]);
            cur=pi[cur];
            points.emplace_back(connector.first);
            points.emplace_back(connector.second);
        }

        cout<<"(";
        totalTime = 0;
        REP(i,points.size()-1) {
            double mem = points[i].distanceFromPoint(points[i+1]) / ((i%2!=0) ? TRANSPORTER_SPEED :1.0);
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

#endif //NOMPROJET_MODEL_H
