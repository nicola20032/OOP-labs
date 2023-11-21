//
// Created by Никола Пшеничный on 22.11.2022.
//

#include "Functions.h"


float vectorproizv(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first * b.second - a.second * b.first;
}

bool sortbysec(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second < b.second);
}

vector<pair<int, int>> KeilKirk(vector<pair<int, int>> A){
    sort(A.begin(), A.end(), sortbysec);
    vector<pair<int, int>> Al;
    vector<pair<int, int>> Ar;
    vector<pair<int, int>> resultL;
    vector<pair<int, int>> resultR;
    vector<pair<int, int>> result;
    int leftPointer = 0, rightPointer = 0;
    for(int i = 1; i < A.size(); i++){
        if(A[i-1].second == A[i].second){
            if(A[leftPointer].first > A[i].first)
                leftPointer = i;
            else if(A[rightPointer].first < A[i].first)
                rightPointer = i;
        }
        else{
            Al.push_back(A[leftPointer]);
            Ar.push_back(A[rightPointer]);
            leftPointer = i;
            rightPointer = i;
        }
    }
    Al.push_back(A[leftPointer]);
    Ar.push_back(A[rightPointer]);
    int i = 0;
    while(i < Al.size()){
        if(resultL.size() < 2){
            resultL.push_back(Al[i]);
            i++;
        }
        else{
            pair<int, int> a = {resultL[resultL.size() - 2].first - resultL[resultL.size() - 1].first, resultL[resultL.size() - 2].second - resultL[resultL.size() - 1].second};
            pair<int, int> b = {Al[i].first - resultL[resultL.size() - 1].first, Al[i].second - resultL[resultL.size() - 1].second};
            if(vectorproizv(a, b) > 0){
                resultL.push_back(Al[i]);
                i++;
            }
            else{
                resultL.pop_back();
            }
        }
    }
    i = 0;
    while(i < Ar.size()){
        if(resultR.size() < 2){
            resultR.push_back(Ar[i]);
            i++;
        }
        else{
            pair<int, int> a = {resultR[resultR.size() - 2].first - resultR[resultR.size() - 1].first, resultR[resultR.size() - 2].second - resultR[resultR.size() - 1].second};
            pair<int, int> b = {Ar[i].first - resultR[resultR.size() - 1].first, Ar[i].second - resultR[resultR.size() - 1].second};
            if(vectorproizv(a, b) < 0){
                resultR.push_back(Ar[i]);
                i++;
            }
            else{
                resultR.pop_back();
            }
        }
    }
    for(int i = 0; i < resultL.size(); i++){
                result.push_back(resultL[i]);
    }
    for(int i = resultR.size() - 1; i >= 0; i--){
        result.push_back(resultR[i]);
    }
    return result;

}

float distance_to_line(const pair<int, int> &a, const pair<int, int> &b, const pair<int, int> &c){
    if(a==b||a==c||b==c){
        return 0;
    }
    pair<int, int> ab = {b.first - a.first, b.second - a.second};
    pair<int, int> ac = {c.first - a.first, c.second - a.second};
    return vectorproizv(ab, ac) / sqrt(ab.first * ab.first + ab.second * ab.second);
}

vector<pair<int, int>> Endru(vector<pair<int, int>> A){
    sort(A.begin(), A.end());
    vector<pair<int, int>> result;
    vector<pair<int, int>> resultT;
    vector<pair<int, int>> resultB;
    vector<pair<int, int>> Atop;
    vector<pair<int, int>> Abot;
    pair<int, int> aRight = A[0];
    pair<int, int> aLeft = A[A.size() - 1];
    Atop.push_back(aRight);
    Abot.push_back(aRight);
    for(int i = 1; i < A.size(); i++){
        if(distance_to_line(aRight, aLeft, A[i]) > 0){
            Atop.push_back(A[i]);
        }
        else{
            Abot.push_back(A[i]);
        }
    }
    Atop.push_back(aLeft);
    sort(Atop.begin(), Atop.end());
    sort(Abot.begin(), Abot.end());
    int k;
    for(int i = 0; i < Atop.size()-1; i++){
        for(int j = i+1; j < Atop.size(); j++){
            k=0;
            while(k == i || k == j){
                k++;
            }
            cout<<distance_to_line(Atop[i], Atop[j], Atop[k])<<endl;
            while (k < Atop.size() && distance_to_line(Atop[i], Atop[j], Atop[k]) < 0) {
                k++;
                while(k == i || k == j){
                    k++;
                }
                cout<<distance_to_line(Atop[i], Atop[j], Atop[k])<<endl;
            }
            if(k == Atop.size()){
                resultT.push_back(Atop[i]);

                break;
            }
        }
    }
    for(int i = 0; i < Abot.size()-1; i++){
        for(int j = i+1; j < Abot.size(); j++){
            k=0;
            while(k == i || k == j){
                k++;
            }
            cout<<distance_to_line(Abot[i], Abot[j], Abot[k])<<endl;
            while (k < Abot.size() && distance_to_line(Abot[i], Abot[j], Abot[k]) > 0) {
                k++;
                while(k == i || k == j){
                    k++;
                }
                cout<<distance_to_line(Abot[i], Abot[j], Abot[k])<<endl;
            }
            if(k == Abot.size()){
                if(i != 0){
                    resultB.push_back(Abot[i]);
                }
                break;
            }
        }
    }
    result = resultT;
    result.push_back(aLeft);
    for(int i = resultB.size() - 1; i >= 0; i--){
        result.push_back(resultB[i]);
    }
    result.push_back(aRight);
    return result;
}

pair<int, int> find_inner(vector<pair<int, int>> A){
    int TOP = A[0].second;
    int BOT = TOP;
    int RIGHT = A[0].first;
    int LEFT = RIGHT;
    for(int i = 0; i < A.size(); i++){
        if(A[i].second > TOP){
            TOP = A[i].second;
        }
        if(A[i].second < BOT){
            BOT = A[i].second;
        }
        if(A[i].first > RIGHT){
            RIGHT = A[i].first;
        }
        if(A[i].first < LEFT){
            LEFT = A[i].first;
        }
    }
    return make_pair((LEFT + RIGHT) / 2, (TOP + BOT) / 2);

}

vector<pair<int, int>> Graham(vector<pair<int, int>> A){
    pair<int, int> a0 = find_inner(A);
    sort(A.begin(), A.end(), [a0](pair<int, int> a, pair<int, int> b){
        return atan2(a.second - a0.second, a.first - a0.first) < atan2(b.second - a0.second, b.first - a0.first);
    });
    vector<pair<int, int>> result;
    int i = 0;
    while(i < A.size()){
        if(result.size() < 2){
            result.push_back(A[i]);
            i++;
        }
        else{
            pair<int, int> a = {result[result.size() - 1].first - result[result.size() - 2].first, result[result.size() - 1].second - result[result.size() - 2].second};
            pair<int, int> b = {A[i].first - result[result.size() - 1].first, A[i].second - result[result.size() - 1].second};
            if(vectorproizv(a, b) >= 0){
                result.push_back(A[i]);
                i++;
            }
            else{
                result.pop_back();
            }
        }
    }
    while(vectorproizv({result[0].first - result[result.size() - 1].first, result[0].second - result[result.size() - 1].second}, {result[1].first - result[0].first, result[1].second - result[0].second}) <= 0 || vectorproizv({result[result.size() - 1].first - result[result.size() - 2].first, result[result.size() - 1].second - result[result.size() - 2].second}, {result[0].first - result[result.size() - 1].first, result[0].second - result[result.size() - 1].second}) <= 0){
        if(vectorproizv({result[0].first - result[result.size() - 1].first, result[0].second - result[result.size() - 1].second}, {result[1].first - result[0].first, result[1].second - result[0].second}) <= 0){
            result.erase(result.begin());
        }
        else{
            result.pop_back();
        }
    }

    result.push_back(result[0]);

    return result;
}


vector<pair<int, int>> set_above_line(vector<pair<int, int>> A, pair<int, int> a, pair<int, int> b){
    vector<pair<int, int>> result;
    for(int i = 0; i < A.size(); i++){
        if(distance_to_line(a, b, A[i]) > 0){
            result.push_back(A[i]);
        }
    }
    return result;
}

vector<pair<int, int>> set_below_line(vector<pair<int, int>> A, pair<int, int> a, pair<int, int> b){
    vector<pair<int, int>> result;
    for(int i = 0; i < A.size(); i++){
        if(distance_to_line(a, b, A[i]) < 0){
            result.push_back(A[i]);
        }
    }
    return result;
}


pair<int, int> find_dno(vector<pair<int, int>> A, pair<int, int> a, pair<int, int> b){
    pair<int, int> dno = a;
    for(int i = 0; i < A.size(); i++){
        if(distance_to_line(a, b, dno) >= distance_to_line(a, b, A[i])){
            dno = A[i];
        }
    }
    return dno;
}

pair<int, int> find_nebo(vector<pair<int, int>> A, pair<int, int> a, pair<int, int> b){
    pair<int, int> nebo = a;
    for(int i = 0; i < A.size(); i++){
        if(distance_to_line(a, b, nebo) <= distance_to_line(a, b, A[i])){
            nebo = A[i];
        }
    }
    return nebo;
}
/*
vector<pair<int, int>> FRA(vector<pair<int, int>> A){
    vector<pair<int, int>> A0 = A;
    vector<pair<int, int>> result;
    sort(A0.begin(), A0.end());
    pair<int, int> atop = find_nebo(A0, A[0], A[A.size()-1]);
    pair<int, int> abot = find_dno(A0, A[0], A[A.size()-1]);
    if(A[0] != abot && A[0] != atop){
        result.push_back(A[0]);
    }
    if(A[A.size()-1] != abot && A[A.size()-1] != atop){
        result.push_back(A[0]);
    }
    result.push_back(abot);
    result.push_back(atop);
    FRARecursionT(A, result, A[0], atop);
    FRARecursionT(A, result, atop, A[A.size()-1]);
    FRARecursionB(A, result, A[0], abot);
    FRARecursionB(A, result, abot, A[A.size()-1]);
    pair<int, int> a0 = find_inner(A);
    sort(result.begin(), result.end(), [a0](pair<int, int> a, pair<int, int> b){
        return atan2(a.second - a0.second, a.first - a0.first) < atan2(b.second - a0.second, b.first - a0.first);
    });
    result.push_back(result[0]);
    cout<<"resut"<<endl;
    for(int i = 0; i < result.size(); i++){
        cout<<result[i].first<<" "<<result[i].second<<endl;
    }
    return result;

}

void FRARecursionT(vector<pair<int, int>> A, vector<pair<int, int>> &result, pair<int, int> a, pair<int, int> b){
    pair<int, int> ares = find_nebo(A, a, b);
    cout<<"YA TUT TOP1"<<endl;
    cout<<"ares ="<<ares.first<<" "<<ares.second<<endl;
    cout<<"a = "<<a.first<< " "<< a.second<<endl;
    vector<pair<int, int>> Atop1 = set_above_line(A, a, ares);
    vector<pair<int, int>> Atop2 = set_above_line(A, ares, b);
    result.push_back(ares);
    if(Atop1.size() > 0){
        FRARecursionT(Atop1, result, a, ares);
    }
    if(Atop2.size() > 0){
        FRARecursionT(Atop2, result, ares, b);
    }
}

void FRARecursionB(vector<pair<int, int>> A, vector<pair<int, int>> &result, pair<int, int> a, pair<int, int> b){
    pair<int, int> ares = find_dno(A, a, b);
    cout<<"YA TUT BOT1"<<endl;
    cout<<"ares ="<<ares.first<<" "<<ares.second<<endl;
    cout<<"a = "<<a.first<< " "<< a.second<<endl;
    vector<pair<int, int>> Abot1 = set_below_line(A, a, ares);
    vector<pair<int, int>> Abot2 = set_below_line(A, ares, b);
    result.push_back(ares);
    if(Abot1.size() > 0){
        FRARecursionB(Abot1, result, a, ares);
    }
    if(Abot2.size() > 0){
        FRARecursionB(Abot2, result, ares, b);
    }
}
*/

vector<pair<int, int>> QuickHull(vector<pair<int, int>> A){
    vector<pair<int, int>> result;
    int number = 0;
    vector<pair<int, int>> A0 = A;
    for(int i = 0; i < A0.size(); i++){
        if(A0[i].first > A0[number].first){
            number = i;
        }
        if(A0[i].first == A0[number].first && A0[i].second < A0[number].second){
            number = i;
        }
    }
    result.push_back(A0[number]);
    number = 0;
    for(int i = 0; i < A0.size(); i++){
        if(A0[i].first < A0[number].first){
            number = i;
        }
        if(A0[i].first == A0[number].first && A0[i].second < A0[number].second){
            number = i;
        }
    }
    result.push_back(A0[number]);
    vector<pair<int, int>> S1;
    vector<pair<int, int>> S2;
    for(int i =0; i<A0.size(); i++){
        if(A0[i] != result[0] && A0[i] != result[1]){
            if(orientation(result[0], result[1], A0[i]) == 1){
                S1.push_back(A0[i]);
            }
            else if(orientation(result[1], result[0], A0[i]) == 1){
                S2.push_back(A0[i]);
            }
        }
    }
    FindHull(S1, result[0], result[1], result);
    FindHull(S2, result[1], result[0], result);
    pair<int, int> a0 = find_inner(A);
    sort(result.begin(), result.end(), [a0](pair<int, int> a, pair<int, int> b){
        return atan2(a.second - a0.second, a.first - a0.first) < atan2(b.second - a0.second, b.first - a0.first);
    });
    result.push_back(result[0]);
    return result;


}

void FindHull(vector<pair<int, int>> S, pair<int, int> a, pair<int, int> b, vector<pair<int, int>> &result){
    if(S.size() < 1){
        return;
    }
    int number = 0;
    for(int i = 0; i < S.size(); i++){
        if(distance_to_line(b, a, S[i]) > distance_to_line(b, a, S[number])){
            number = i;
        }
    }
    result.push_back(S[number]);
    vector<pair<int, int>> S1;
    vector<pair<int, int>> S2;
    for(int i = 0; i < S.size(); i++){
        if(S[i] != S[number]){
            if(orientation(a, S[number], S[i]) == 1){
                S1.push_back(S[i]);
            }
            else if(orientation(S[number], b, S[i]) == 1){
                S2.push_back(S[i]);
            }
        }
    }
    FindHull(S1, a, S[number], result);
    FindHull(S2, S[number], b, result);
}

int orientation(pair<int, int> a, pair<int, int> b, pair<int, int> c){
    int val = (b.second - a.second) * (c.first - b.first) - (b.first - a.first) * (c.second - b.second);
    if(val == 0){
        return 0;
    }
    if(val > 0){
        return 1;
    }
    else{
        return -1;
    }
}

vector<pair<int, int>> Fortune(vector<pair<int, int>> A){

}

vector<pair<int, int>> randomVector(int n){
    vector<pair<int, int>> result;
    for(int i = 0; i < n; i++){
        result.push_back(make_pair(rand()%900, rand()%900));
    }
    return result;
}

void plotHullSFML(vector<pair<int, int>> input, vector<pair<int, int>> hull) {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < input.size(); i++) {
            sf::CircleShape point(5.f);
            point.setFillColor(sf::Color::Red);
            point.setPosition(input[i].first, input[i].second);
            window.draw(point);
        }
        sf::VertexArray lines2(sf::LinesStrip, hull.size());
        for(int i = 0; i < hull.size(); i++){
            lines2[i].position = sf::Vector2f(hull[i].first, hull[i].second);
            lines2[i].color = sf::Color::Green;
        }
        window.draw(lines2);
        window.display();
        }
    }