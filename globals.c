
#define GL_SequnceCap 1000

typedef enum {
    KeyUp,
    KeyDown
} KeyPressMode;

LARGE_INTEGER GL_PerformanceFrequency;
char GL_Sequence[GL_SequnceCap];
unsigned GL_SequnceLength;
double GL_Cycle;
double GL_CycleVariance;
double GL_HoldTime;
