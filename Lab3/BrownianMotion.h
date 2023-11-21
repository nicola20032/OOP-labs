//
// Created by Никола Пшеничный on 20.12.2022.
//

#ifndef MAIN_CPP_BROWNIANMOTION_H
#define MAIN_CPP_BROWNIANMOTION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "Vector.h"

using namespace std;
struct particle;
struct BOX;
void CheckCollision(particle &p1, particle &p2);
void Collision(particle &p1, particle &p2);
void CheckCollisionBOX(particle &p, BOX &b);


void UserCreatesParticles(vector<particle*> &particles, int n);
void UserCreatesBOX(vector<BOX*> &boxes, int n);

void plotBrownianMotionSFML(vector<particle*> particles, BOX box);

void BMmain();
void ManySmallParticles(vector<particle*> &particles, int n, BOX box);
void FewBigParticles(vector<particle*> &particles, int n, BOX box);
void TypeOfParticles(vector<particle*> &particles, BOX box);

#endif //MAIN_CPP_BROWNIANMOTION_H
