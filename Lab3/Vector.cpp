//
// Created by Никола Пшеничный on 09.12.2022.
//

#include "Vector.h"
#include <cmath>

Vector::Vector(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector Vector::operator+(const Vector& other) const {
    return {this->x + other.x, this->y + other.y};
}

Vector Vector::operator*(const double& scalar) const{
    return {this->x * scalar, this->y * scalar};
}

Vector Vector::operator-(const Vector &other) const {
    return Vector(this->x - other.x, this->y - other.y);
}

Vector &Vector::operator-=(const Vector &other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector &Vector::operator+=(const Vector &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector &Vector::operator*=(double k) {
    this->x *= k;
    this->y *= k;
    return *this;
}

Vector Vector::createNormal() const {
    return Vector(-this->y, this->x);
}

double Vector::getLength() const {
    return sqrt(this->x * this->x + this->y * this->y);
}

double Vector::distance(const Vector &other) const {
    return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
}

double Vector::dot(const Vector &other) const {
    return this->x * other.x + this->y * other.y;
}

double Vector::vectorProduct(const Vector &other) const {
    return this->x * other.y - this->y * other.x;
}