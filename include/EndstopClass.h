class EndstopClass : public PinClass {
    private:
        int pull_mode;
        int x;
        int y;
        int z;
    public:
        EndstopClass(int x, int y, int z, int pull_mode);
        void initPin();
        void currentStatus();
};