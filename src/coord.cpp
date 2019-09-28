#include "main.h"

Coord::Coord() {
    this->coord_x = -1;
    this->coord_y = -1;
    this->coord_z = -1;
}
void Coord::setX(int x) {
    this->coord_x = x;
}
void Coord::setY(int y) {
    this->coord_y = y;
}
void Coord::setZ(int z) {
    this->coord_z = z;
}

int Coord::retX() {
    return this->coord_x;
}
int Coord::retY() {
    return this->coord_y;
}
int Coord::retZ() {
    return this->coord_z;
}