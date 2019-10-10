class Timer {
    public:
        static void sleep_kangdroid(unsigned int usleep);
        static unsigned int TIMER_GetSysTick();
        static void TIMER_Init();
        static void TIMER_Del();
};
