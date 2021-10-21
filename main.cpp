#include "Graphics.h"
#include "Model.h"

using namespace sf;

Model m;
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

    REP(i,path.size()-1){
        g.drawLine(path[i].x_,path[i].y_,path[i+1].x_,path[i+1].y_,i%2==0 ? "magenta" : "green");
    }

    printf("total : %.10f\n",m.shortestPathTimeSec());
}

int main(){

    m.initModel();

    g.initWindow(600, 600,"Airport Logistic");


    g.bindOnInit(draw);
    //g.bindAfterInit(printInfos)

    return 0;
}

