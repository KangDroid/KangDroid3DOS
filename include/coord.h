class Coord {
    private:
        float coord_x;
        float coord_y;
        float coord_z;

    public:
        Coord();
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float retX();
        float retY();
        float retZ();
};