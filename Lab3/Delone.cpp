//
// Created by Никола Пшеничный on 19.12.2022.
//

#include "Delone.h"

struct Triangle {
    pair<float, float> a;
    pair<float, float> b;
    pair<float, float> c;
    pair<pair<float, float>, pair<float, float>> ab;
    pair<pair<float, float>, pair<float, float>> bc;
    pair<pair<float, float>, pair<float, float>> ca;
    Triangle(pair<float, float> a, pair<float, float> b, pair<float, float> c) {
        this->a = a;
        this->b = b;
        this->c = c;
        ab = make_pair(a, b);
        bc = make_pair(b, c);
        ca = make_pair(c, a);
    }
};
//Find center of circumcircle
pair<float, float> Orthocenter(Triangle* t) {
    pair<float, float> a = t->a;
    pair<float, float> b = t->b;
    pair<float, float> c = t->c;
    float x1 = a.first;
    float x2 = b.first;
    float x3 = c.first;
    float y1 = a.second;
    float y2 = b.second;
    float y3 = c.second;
    float y = ((x1 - x2)*(x1*x1 - x3*x3 + y1*y1 - y3*y3)/2 - (x1 - x3)*(x1*x1 - x2*x2 + y1*y1 - y2*y2)/2)/((x1 - x2)*(y1 - y3) - (x1 - x3)*(y1 - y2));
    float x = ((x1*x1 - x2*x2 + y1*y1 - y2*y2)/2 - (y1 - y2)*y)/(x1 - x2);
    return make_pair(x, y);
}

Triangle FindSuperTriangle(vector<pair<int, int>> input) {
    float minx = input[0].first, miny = input[0].second, maxx = input[0].first, maxy = input[0].second;
    for (int i = 1; i < input.size(); i++) {
        if (input[i].first < minx) minx = input[i].first;
        if (input[i].first > maxx) maxx = input[i].first;
        if (input[i].second < miny) miny = input[i].second;
        if (input[i].second > maxy) maxy = input[i].second;
    }
    float dx = maxx - minx;
    float dy = maxy - miny;
    float dmax = max(dx, dy);
    float xmid = (minx + maxx) / 2;
    float ymid = (miny + maxy) / 2;
    return Triangle(make_pair(xmid - 2 * dmax, ymid - dmax), make_pair(xmid, ymid + 2 * dmax),
                    make_pair(xmid + 2 * dmax, ymid - dmax));
}

bool IsInCircumcircle(Triangle* t, pair<float, float> p) {
    pair<float, float> center = Orthocenter(t);
    float r = sqrt(pow(center.first - t->a.first, 2) + pow(center.second - t->a.second, 2));
    float d = sqrt(pow(center.first - p.first, 2) + pow(center.second - p.second, 2));
    return d <= r;
}

bool EdgeInTriangle(Triangle t, pair<float, float> a, pair<float, float> b) {
    if(t.ab == make_pair(a, b) || t.bc == make_pair(a, b) || t.ca == make_pair(a, b)) return true;
    if(t.ab == make_pair(b, a) || t.bc == make_pair(b, a) || t.ca == make_pair(b, a)) return true;
    return false;
}

bool SameTriangle(Triangle t1, Triangle t2){
    if(t1.a == t2.a && t1.b == t2.b && t1.c == t2.c) return true;
    if(t1.a == t2.b && t1.b == t2.c && t1.c == t2.a) return true;
    if(t1.a == t2.c && t1.b == t2.a && t1.c == t2.b) return true;
    return false;
}

bool EdgeIsShared(Triangle* t1,pair<pair<float, float>, pair<float, float>> Edge){
    if(t1->ab == Edge || t1->bc == Edge || t1->ca == Edge) return true;
    if(t1->ab == make_pair(Edge.second, Edge.first) || t1->bc == make_pair(Edge.second, Edge.first) || t1->ca == make_pair(Edge.second, Edge.first)) return true;
    return false;
}

bool EdgeIsSharedArray(Triangle* t1, vector<Triangle*> t2, pair<pair<float, float>, pair<float, float>> Edge){
    for(int i = 0; i < t2.size(); i++){
        if(!SameTriangle(*t1, *t2[i])){
            if(EdgeIsShared(t2[i], Edge)) return true;
        }
    }
    return false;
}


//BOYER-WATSON ALGORITHM
vector<Triangle*> BowyerWatson(vector<pair<int, int>> input){
    vector<Triangle*> triangles;
    Triangle super = FindSuperTriangle(input);
    cout<<"SUPER TRIANGE"<<endl;
    cout<<super.a.first<<" "<<super.a.second<<endl;
    cout<<super.b.first<<" "<<super.b.second<<endl;
    cout<<super.c.first<<" "<<super.c.second<<endl;
    cout<<"======================"<<endl;
    triangles.push_back(&super);
    for(int i = 0; i < input.size(); i++){
        vector<Triangle*> badTriangles = {};
        for(int j = 0; j < triangles.size(); j++){
            if(IsInCircumcircle(triangles[j], input[i])){
                badTriangles.push_back(triangles[j]);
            }
        }
        vector<pair<pair<float, float>, pair<float, float>>> polygon = {};
        for(int j = 0; j < badTriangles.size(); j++){
            if(!EdgeIsSharedArray(badTriangles[j], badTriangles, badTriangles[j]->ab)){
                polygon.push_back(badTriangles[j]->ab);
            }
            if(!EdgeIsSharedArray(badTriangles[j], badTriangles, badTriangles[j]->bc)){
                polygon.push_back(badTriangles[j]->bc);
            }
            if(!EdgeIsSharedArray(badTriangles[j], badTriangles, badTriangles[j]->ca)){
                polygon.push_back(badTriangles[j]->ca);
            }
        }
        for(int j = 0; j < badTriangles.size(); j++){
            for(int k = 0; k < triangles.size(); k++){
                if(SameTriangle(*badTriangles[j], *triangles[k])){
                    triangles.erase(triangles.begin() + k);
                    k = triangles.size();
                }
            }
        }
        for(int j = 0; j < polygon.size(); j++){
            Triangle* t = new Triangle(polygon[j].first, polygon[j].second, input[i]);
            triangles.push_back(t);
            cout<<"TRIANGLE"<<endl;
            cout<<t->a.first<<" "<<t->a.second<<endl;
            cout<<t->b.first<<" "<<t->b.second<<endl;
            cout<<t->c.first<<" "<<t->c.second<<endl;
            cout<<"======================"<<endl;
        }
    }
    for(int i = 0; i < triangles.size(); i++) {
        if (triangles[i]->a == super.a || triangles[i]->a == super.b || triangles[i]->a == super.c) {
            triangles.erase(triangles.begin() + i);
            i--;
        } else if (triangles[i]->b == super.a || triangles[i]->b == super.b || triangles[i]->b == super.c) {
            triangles.erase(triangles.begin() + i);
            i--;
        } else if (triangles[i]->c == super.a || triangles[i]->c == super.b || triangles[i]->c == super.c) {
            triangles.erase(triangles.begin() + i);
            i--;
        }
    }

    printTriangles(triangles);
    return triangles;
}

void printTriangles(vector<Triangle*> triangles) {
    for (int i = 0; i < triangles.size(); i++) {
        cout << "Triangle " << i << ": " << endl;
        cout << "a: " << triangles[i]->a.first << " " << triangles[i]->a.second << endl;
        cout << "b: " << triangles[i]->b.first << " " << triangles[i]->b.second << endl;
        cout << "c: " << triangles[i]->c.first << " " << triangles[i]->c.second << endl;
        cout << "ab: " << triangles[i]->ab.first.first << " " << triangles[i]->ab.first.second << " " << triangles[i]->ab.second.first << " " << triangles[i]->ab.second.second << endl;
        cout << "bc: " << triangles[i]->bc.first.first << " " << triangles[i]->bc.first.second << " " << triangles[i]->bc.second.first << " " << triangles[i]->bc.second.second << endl;
        cout << "ca: " << triangles[i]->ca.first.first << " " << triangles[i]->ca.first.second << " " << triangles[i]->ca.second.first << " " << triangles[i]->ca.second.second << endl;
    }
}







void plotDeloneSFML(vector<Triangle*> triangles, vector<pair<int, int>> points){
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < points.size(); i++) {
            sf::CircleShape point(2.f);
            point.setFillColor(sf::Color::Red);
            point.setPosition(points[i].first, points[i].second);
            window.draw(point);
        }
        for (int i = 0; i < triangles.size(); i++) {
            for(int j = 0; j < 3; j++){
                sf::VertexArray lines3(sf::Lines, 2);
                if(j == 0){
                    lines3[0].position = sf::Vector2f(triangles[i]->a.first, triangles[i]->a.second);
                    lines3[1].position = sf::Vector2f(triangles[i]->b.first, triangles[i]->b.second);
                }
                else if(j == 1){
                    lines3[0].position = sf::Vector2f(triangles[i]->b.first, triangles[i]->b.second);
                    lines3[1].position = sf::Vector2f(triangles[i]->c.first, triangles[i]->c.second);
                }
                else if(j == 2){
                    lines3[0].position = sf::Vector2f(triangles[i]->c.first, triangles[i]->c.second);
                    lines3[1].position = sf::Vector2f(triangles[i]->a.first, triangles[i]->a.second);
                }
                lines3[0].color = sf::Color::Blue;
                lines3[1].color = sf::Color::Blue;
                window.draw(lines3);
            }
        }
        window.display();
    }
}
