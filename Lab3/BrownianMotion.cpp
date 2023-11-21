//
// Created by Никола Пшеничный on 20.12.2022.
//

#include "BrownianMotion.h"

struct particle{
    float x;
    float y;
    float r;
    float vx;
    float vy;
    float m;
    sf::CircleShape shape;
    particle(float x, float y, float r, float vx, float vy, sf::Color color){
        this->x = x;
        this->y = y;
        this->r = r;
        this->vx = vx;
        this->vy = vy;
        this->m = 4*M_PI*r*r*r/3;
        this->shape = sf::CircleShape(r);
        this->shape.setFillColor(color);
        this->shape.setPosition(x, y);
    }
};

struct BOX{
    float XO;
    float YO;
    float X1;
    float Y1;
    BOX(float XO, float YO, float X1, float Y1){
        this->XO = XO;
        this->YO = YO;
        this->X1 = X1;
        this->Y1 = Y1;
    }
};

//Collision between two particles
void Collision(particle &p1, particle &p2){
    //Calculate the unit normal vector
    Vector normal = Vector(p1.x - p2.x, p1.y - p2.y);
    normal = normal * (1/normal.getLength());

    //Calculate the unit tangent vector
    Vector tangent = normal.createNormal();
    tangent = tangent * (1/tangent.getLength());

    //Project the velocity of the particles onto the normal and tangent vectors
    float v1n = normal.dot(Vector(p1.vx, p1.vy));
    float v1t = tangent.dot(Vector(p1.vx, p1.vy));
    float v2n = normal.dot(Vector(p2.vx, p2.vy));
    float v2t = tangent.dot(Vector(p2.vx, p2.vy));

    //Calculate the new normal velocities
    float v1nTag = (v1n * (p1.m - p2.m) + 2 * p2.m * v2n) / (p1.m + p2.m);
    float v2nTag = (v2n * (p2.m - p1.m) + 2 * p1.m * v1n) / (p1.m + p2.m);

    //Convert the scalar normal and tangential velocities into vectors
    Vector v1nTagVector = normal * v1nTag;
    Vector v1tVector = tangent * v1t;
    Vector v2nTagVector = normal * v2nTag;
    Vector v2tVector = tangent * v2t;

    //Calculate the new velocity vectors
    Vector v1Tag = v1nTagVector + v1tVector;
    Vector v2Tag = v2nTagVector + v2tVector;

    //Update the particles velocities
    p1.vx = v1Tag.x;
    p1.vy = v1Tag.y;
    p2.vx = v2Tag.x;
    p2.vy = v2Tag.y;

}

//Collision between two particles
void CheckCollision(particle &p1, particle &p2) {
    float d = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    if(d <= p1.r + p2.r){
        Collision(p1, p2);
    }
}


void CheckCollisionBOX(particle &p, BOX &b){
    if (p.x + 2*p.r > b.X1){
        p.vx = -p.vx;
    }
    if (p.x < b.XO){
        p.vx = -p.vx;
    }
    if (p.y + 2*p.r > b.Y1){
        p.vy = -p.vy;
    }
    if (p.y < b.YO){
        p.vy = -p.vy;
    }
}

void UserCreatesParticles(vector<particle*> &particles, int n){
    for (int i = 0; i < n; i++){
        float x, y, r, vx, vy;
        string color;
        cout << "Enter x, y, r, vx, vy" << endl;
        cin >> x >> y >> r >> vx >> vy;
        cout << "Enter color" << endl;
        cin>>color;
        sf::Color color1;
        if (color == "red")color1 = sf::Color::Red;
        if (color == "blue")color1 = sf::Color::Blue;
        if (color == "green")color1 = sf::Color::Green;
        if (color == "yellow") color1 = sf::Color::Yellow;
        particles.push_back(new particle(x, y, r, vx, vy, color1));
    }
}

void UserCreatesBOX(BOX &BOX){
    float XO, YO, X1, Y1;
    cout << "Enter XO, YO, X1, Y1" << endl;
    cin >> XO >> YO >> X1 >> Y1;
    BOX.X1 = X1;
    BOX.XO = XO;
    BOX.Y1 = Y1;
    BOX.YO = YO;
}

void plotBrownianMotionSFML(vector<particle*> particles, BOX box){
    sf::RenderWindow window(sf::VideoMode(box.X1 - box.XO, box.Y1 - box.YO), "Brownian Motion");
    window.setFramerateLimit(60);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < particles.size(); i++){
            for (int j = 0; j < particles.size(); j++){
                if(i != j){
                    CheckCollision(*particles[i], *particles[j]);
                }
            }
            CheckCollisionBOX(*particles[i], box);
            particles[i]->x += particles[i]->vx;
            particles[i]->y += particles[i]->vy;
            particles[i]->shape.setPosition(particles[i]->x, particles[i]->y);
            window.draw(particles[i]->shape);
        }
        window.display();
    }
}

void BMmain(){
    vector<particle*> particles;
    BOX box(0, 0, 800, 600);

    UserCreatesBOX(box);
    TypeOfParticles(particles, box);
    plotBrownianMotionSFML(particles, box);

}

void ManySmallParticles(vector<particle*> &particles, int n, BOX box){
    int R = 10;
    for (int i = 0; i < n; i++){
        float x = box.XO + R + rand() % int((box.X1 - box.XO - 2 * R));
        float y = box.YO + R + rand() % int((box.Y1 - box.YO - 2 * R));
        float vx = -1 + rand() % 3;
        float vy = -1 + rand() % 3;
        int r = 1 + rand() % 8;
        particles.push_back(new particle(x, y, r, vx, vy, sf::Color(rand() % 255, rand() % 255, rand() % 255)));
    }
}

void FewBigParticles(vector<particle*> &particles, int n, BOX box){
    int R = 50;
    for (int i = 0; i < n; i++){
        float x = box.XO + R + rand() % int((box.X1 - box.XO - 2 * R));
        float y = box.YO + R + rand() % int((box.Y1 - box.YO - 2 * R));
        float vx = -1 + rand() % 3;
        float vy = -1 + rand() % 3;
        int r = R/2 + rand() % 25;
        particles.push_back(new particle(x, y, r, vx, vy, sf::Color(rand() % 255, rand() % 255, rand() % 255)));
    }
}

void TypeOfParticles(vector<particle*> &particles, BOX box){
    cout<<"Enter type of particles"<<endl;
    cout<<"1. Many small particles"<<endl;
    cout<<"2. Few big particles"<<endl;
    cout<<"3. User creates particles"<<endl;
    int type;
    cin>>type;
    if(type == 1){
        int n = 100+rand()%100;
        ManySmallParticles(particles, n, box);
    }
    if(type == 2){
        int n = 1+rand()%8;
        FewBigParticles(particles, n, box);
    }
    if(type == 3){
        int n;
        cout<<"Enter number of particles"<<endl;
        cin>>n;
        UserCreatesParticles(particles, n);
    }


}