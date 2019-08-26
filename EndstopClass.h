class EndstopClass {
    private:
        int * es_pin;
        int mode;
        int pull_mode;
    public:
        EndstopClass(int es_pin[], int mode, int pull_mode);
        ~EndstopClass();
        void initPin();
};