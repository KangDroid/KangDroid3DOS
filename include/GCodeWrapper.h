class GCodeWrapper {
    public:
        static void G28();
        static void M119();
        static void G1(int feedrate = 32, int x = 0, int y = 0, int z = 0);
        static void M18();
        static void M114();
};