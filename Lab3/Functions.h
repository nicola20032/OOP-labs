//
// Created by Никола Пшеничный on 22.11.2022.
//

#ifndef LAB3_FUNCTIONS_H
#define LAB3_FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool sortbysec(const pair<int,int> &a, const pair<int,int> &b);
float vectorproizv(const pair<int, int> &a, const pair<int, int> &b);
float distance_to_line(const pair<int, int> &a, const pair<int, int> &b, const pair<int, int> &c);
vector<pair<int, int>> KeilKirk(vector<pair<int, int>> A);
vector<pair<int, int>> Endru(vector<pair<int, int>> A);
vector<pair<int, int>> Graham(vector<pair<int, int>> A);
pair<int, int> find_inner(vector<pair<int, int>> A);
vector<pair<int, int>> QuickHull(vector<pair<int, int>> A);
void FindHull(vector<pair<int, int>> S, pair<int, int> a, pair<int, int> b, vector<pair<int, int>> &result);
int orientation(pair<int, int> a, pair<int, int> b, pair<int, int> c);
vector<pair<int, int>> Fortune(vector<pair<int, int>> A);
vector<pair<int, int>> randomVector(int n);

void plotHullSFML(vector<pair<int, int>> input, vector<pair<int, int>> hull);




#endif //LAB3_FUNCTIONS_H
