class GCodeWrapper {
    public:
        static void G28();
        static void M119();
        static void G1(float feedrate = 32, float x = 0, float y = 0, float z = 0);
        static void M18();
        static void M114();
};