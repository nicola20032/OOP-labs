//
// Created by Никола Пшеничный on 19.12.2022.
//

#ifndef MAIN_CPP_DELONE_H
#define MAIN_CPP_DELONE_H
#include "Vector.h"
#include <vector>
#include "iostream"
#include "cmath"
#include <SFML/Graphics.hpp>

using namespace std;


struct Triangle;
vector<Triangle*> BowyerWatson(vector<pair<int, int>> input);
Triangle FindSuperTriangle(vector<pair<int, int>> input);
pair<float, float> Orthocenter(Triangle* t);
bool IsInCircumcircle(Triangle* t, pair<float, float> p);
void plotDeloneSFML(vector<Triangle*> triangles, vector<pair<int, int>> points);
void printTriangles(vector<Triangle*> triangles);



#endif //MAIN_CPP_DELONE_H
