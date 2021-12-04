
#define GL_SequnceCap 1000
#define UnsignedMax (~0ull)

typedef enum {
    KeyUp,
    KeyDown
} KeyPressMode;

LARGE_INTEGER GL_PerformanceFrequency;
HCRYPTPROV GL_CryptProv;

char GL_Sequence[GL_SequnceCap];
unsigned GL_SequnceLength;
double GL_Cycle;
double GL_CycleVariance;
double GL_HoldTime;
