#include "main.h"

Coord::Coord() {
    this->coord_x = -1;
    this->coord_y = -1;
    this->coord_z = -1;
}
void Coord::setX(float x) {
    this->coord_x = x;
}
void Coord::setY(float y) {
    this->coord_y = y;
}
void Coord::setZ(float z) {
    this->coord_z = z;
}

float Coord::retX() {
    return this->coord_x;
}
float Coord::retY() {
    return this->coord_y;
}
float Coord::retZ() {
    return this->coord_z;
}