#include "Graphics.h"
#include "Model.h"

#include <bits/stdc++.h>

#define DEBUG_DRAW_TRUE true

using namespace sf;
using namespace std;

Model m("C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\input_files\\in4.txt",DEBUG_DRAW_TRUE);
Graphics g;

void draw(){
    for(pair<pii,pii> linea : m.getLines()){
        g.drawLine(linea.da_.x_, linea.da_.y_,
                   linea.a_.x_,linea.a_.y_);
    }
    pii A = m.getStartPoint();
    pii B = m.getEndPoint();
    g.drawPoint(A.x_,A.y_,2,"green");
    g.drawPoint(B.x_,B.y_,2,"red");

    vector<pii> path = m.shortestPath();

    int off = 3;

    REP(i,path.size()-1){
        g.drawLine(path[i].x_+off,path[i].y_+off,path[i+1].x_+off,path[i+1].y_+off,i%2==0 ? "green" : "green");
    }

    printf("total : %.10f\n",m.shortestPathTimeSec());
}

int main(){
    g.initWindow(600, 600,"Airport Logistic");
    m.initModel();
    m.DEBUG_DRAW=g;// DEBUG ONLY
    g.bindOnInit(draw);

    //g.bindAfterInit(printInfos)

    return 0;
}

