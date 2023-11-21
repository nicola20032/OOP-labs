//
// Created by Никола Пшеничный on 09.12.2022.
//

#ifndef MAIN_CPP_VECTOR_H
#define MAIN_CPP_VECTOR_H


class Vector {
public:
    double x;
    double y;
    Vector(double x = 0.0, double y = 0.0);

    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);
    Vector& operator+=(const Vector& other);
    Vector& operator*=(double k);

    Vector createNormal() const;
    double getLength() const;
    double distance(const Vector& other) const;
    double dot(const Vector& other) const;
    double vectorProduct(const Vector& other) const;

    Vector operator+(const Vector& other) const;

    Vector operator*(const double& scalar) const;
};


#endif //MAIN_CPP_VECTOR_H
