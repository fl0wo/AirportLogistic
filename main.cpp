#include "Graphics.h"
#include "Model.h"
#include "Controller.h"

#define DEBUG_DRAW_TRUE false

using namespace sf;
using namespace std;

Controller c;
Model m("C:\\Users\\flo\\Downloads\\CLionSFML-master\\CLionSFML-master\\input_files\\in4.txt",DEBUG_DRAW_TRUE);
Graphics g;

void draw(){
    for(pair<pii,pii> linea : m.getLines()){
        g.drawTransporter(linea.da_.x_, linea.da_.y_,linea.a_.x_,linea.a_.y_);
    }
    pii A = m.getStartPoint();
    pii B = m.getEndPoint();
    g.drawPoint(A.x_,A.y_,g.POINT_RADIUS,"green");
    g.drawPoint(B.x_,B.y_,g.POINT_RADIUS,"red");

    vector<pii> path = m.shortestPath();

    int off = 3;

    g.drawTransporterRaw(c.lastMouseClick.x_, c.lastMouseClick.y_,c.curMousePos.x_,c.curMousePos.y_);

    REP(i,path.size()-1){
        g.drawLine(path[i].x_+off,path[i].y_+off,path[i+1].x_+off,path[i+1].y_+off,i%2==0 ? "green" : "green");
    }
    //printf("total : %.10f\n",m.shortestPathTimeSec());
}


void onMouseLeftClick(pii firstMouseClick,pii secondMouseClick) {
    pii first = g.deMapPoint(firstMouseClick.x_,firstMouseClick.y_);
    pii second = g.deMapPoint(secondMouseClick.x_,secondMouseClick.y_);
    m.addLine(first.x_,first.y_,second.x_,second.y_);
}

void performMouseCheck(Event e){
    c.performChecks(e);
}

void drawOnMouseMove(pii mousePosOnClick,pii mouseCurrentPos) {
}

int main(){
    g.initWindow(600, 600,"Airport Logistic");

    m.initModel();
    m.DEBUG_DRAW=g;// DEBUG ONLY

    c.bindOnMouseLeft(onMouseLeftClick,drawOnMouseMove);

    g.bindOnInit(draw,performMouseCheck);

    return 0;
}


int main2(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Image img;
    img.create(20, 20);
    for (auto i = 0; i < 20; ++i) {
        for (auto j = 0; j < 20; ++j) {
            img.setPixel(i, j, sf::Color(255 * i / 20, 255 * j / 20, 255 * i / 20 * j / 20));
        }
    }

    sf::Texture texture;
    texture.loadFromImage(img);
    texture.setRepeated(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect({ 0, 0, 800, 600 });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return EXIT_SUCCESS;
}

