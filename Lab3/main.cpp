#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Functions.h"
#include "Vector.h"
#include <bits/stdc++.h>
#include "Delone.h"
#include "BrownianMotion.h"

using namespace sf;

int main()
{


    vector<pair<int, int>> Test = randomVector(15);
/*    for(int i = 0; i < Test.size(); i++)
    {
        cout<<"{"<<Test[i].first<<", "<<Test[i].second<<"}, ";
    }*/
    //vector<Triangle*> D = BowyerWatson(Test);
    //plotDeloneSFML(D, Test);
    //vector<pair<int, int>> A = QuickHull(Test);
    //plotHullSFML(Test, A);
    BMmain();



    return 0;
}
