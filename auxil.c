
long long TimeToTicks( double x ){

    if( x < 0 ){
        return x * GL_PerformanceFrequency.QuadPart;
    }else{
        return -x * GL_PerformanceFrequency.QuadPart;
    }
}

//-----------------------------------------------------------

HANDLE CreateTimerSimple(){
    return CreateWaitableTimer(
        0 /*default security*/,
        1 /*manual reset*/,
        0 /*name str = null*/
    );
}

//-----------------------------------------------------------

void SetTimerSimple( HANDLE tim, double dur ){

    LARGE_INTEGER li;
    li.QuadPart = TimeToTicks(dur);

    _Bool success = SetWaitableTimer( 
        tim, &li,
        0 /*Period*/,
        0 /*completion routine*/,
        0 /*completion routine args*/,
        0 /*resume=false*/
    );

#ifdef DEBUGMODE
    if( !success ){
        printf("Failed to set waitable timer with code: %d \n", GetLastError() );
    }
#endif

}

//-----------------------------------------------------------

void WaitTimerSimple( HANDLE tim ){

    DWORD success = WaitForSingleObject( tim, INFINITE );

#ifdef DEBUGMODE
    if( success != WAIT_OBJECT_0 || success == WAIT_FAILED ){
        printf("Failed to wait for timer with code: %d \n", GetLastError() );
    }
#endif

}

//-----------------------------------------------------------

void SimulateKey( char key, KeyPressMode mode ){

    INPUT keystroke;
    SecureZeroMemory( &keystroke, sizeof(keystroke) );
    keystroke.type = INPUT_KEYBOARD;
    keystroke.ki.wVk = VkKeyScan(key);
    keystroke.ki.dwFlags = mode == KeyUp ? KEYEVENTF_KEYUP : 0;

    UINT inserts = SendInput( 1, &keystroke, sizeof(keystroke) );
#ifdef DEBUGMODE
    if( inserts != 1 ){
        printf("Failed to simulate %c keystroke with error: %d\n", key, GetLastError() );
    }
#endif

}

//-----------------------------------------------------------

unsigned long long GetRandomUnsigned(){

    unsigned long long res;
    _Bool success = CryptGenRandom( GL_CryptProv, sizeof(res), (BYTE*) &res );

#ifdef DEBUGMODE
    if( !success ){
        printf("Failed to query source of entropy. Wincrypt error: %d\n", GetLastError() );
    }
#endif

    return res;
}

//-----------------------------------------------------------

double GetRandomDouble( double a, double b ){

    double lo;
    double hi;
    if( a < b ){
        lo = a;
        hi = b;
    }else{
        lo = b;
        hi = a;
    }

    double range = hi-lo;
    double rng = (range * GetRandomUnsigned() )/((double)UnsignedMax);
    return lo + rng;
}

//-----------------------------------------------------------