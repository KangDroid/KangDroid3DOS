class Coord {
    private:
        int coord_x;
        int coord_y;
        int coord_z;

    public:
        Coord();
        void setX(int x);
        void setY(int y);
        void setZ(int z);
        int retX();
        int retY();
        int retZ();
};