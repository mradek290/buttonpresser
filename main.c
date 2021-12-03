
#define DEBUGMODE

#ifdef DEBUGMODE
#include <stdio.h>
#endif

#include <windows.h>
#include "globals.c"
#include "auxil.c"

void Initialize(){

    _Bool success;

    success = QueryPerformanceFrequency( &GL_PerformanceFrequency );
#ifdef DEBUGMODE
    if( !success ){
        printf("Unable to query performance counter: %d\n", GetLastError() );
    }
#endif
}

char ToLower( char c ){
    return 'A' <= c && c <= 'Z' ? c + 0x20 : c;
}

void LoadConfiguration( const char* fname ){
    
}

int main( int argc, const char* argv[] ){

    Initialize();


    return 0;
}