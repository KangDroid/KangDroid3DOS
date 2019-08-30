class EndstopClass : public PinClass {
    private:
        int pull_mode;
    public:
        EndstopClass(int pull_mode);
        void initPin();
};