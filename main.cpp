#include "Graphics.h"
#include "Model.h"
#include "Controller.h"

#define DEBUG_DRAW_TRUE true

using namespace sf;
using namespace std;

Controller c;
Model m("C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\input_files\\in4.txt",DEBUG_DRAW_TRUE);
Graphics g;

void draw(){
    for(pair<pii,pii> linea : m.getLines()){
        g.drawLine(linea.da_.x_, linea.da_.y_,linea.a_.x_,linea.a_.y_);
    }
    pii A = m.getStartPoint();
    pii B = m.getEndPoint();
    g.drawPoint(A.x_,A.y_,g.POINT_RADIUS,"green");
    g.drawPoint(B.x_,B.y_,g.POINT_RADIUS,"red");

    vector<pii> path = m.shortestPath();

    int off = 3;

    REP(i,path.size()-1){
        g.drawLine(path[i].x_+off,path[i].y_+off,path[i+1].x_+off,path[i+1].y_+off,i%2==0 ? "green" : "green");
    }

    g.drawLineRaw(c.lastMouseClick.x_, c.lastMouseClick.y_,c.curMousePos.x_,c.curMousePos.y_);

    //printf("total : %.10f\n",m.shortestPathTimeSec());
}

void drawOnMouseMove(pii mousePosOnClick,pii mouseCurrentPos) {
    //printf("%d %d %d %d\n",c.lastMouseClick.x_, c.lastMouseClick.y_,c.curMousePos.x_,c.curMousePos.y_);
    //printf("%d %d %d %d\n",mousePosOnClick.x_, mousePosOnClick.y_,mouseCurrentPos.x_,mouseCurrentPos.y_);
}

void onMouseLeftClick(pii firstMouseClick,pii secondMouseClick) {
    pii first = g.deMapPoint(firstMouseClick.x_,firstMouseClick.y_);
    pii second = g.deMapPoint(secondMouseClick.x_,secondMouseClick.y_);
    m.addLine(first.x_,first.y_,second.x_,second.y_);
}

void performMouseCheck(Event e){
    c.performChecks(e);
}

int main(){
    g.initWindow(600, 600,"Airport Logistic");

    m.initModel();
    m.DEBUG_DRAW=g;// DEBUG ONLY

    c.bindOnMouseLeft(onMouseLeftClick,drawOnMouseMove);

    g.bindOnInit(draw,performMouseCheck);

    return 0;
}

