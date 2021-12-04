
#define DEBUGMODE

#ifdef DEBUGMODE
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include "globals.c"
#include "auxil.c"
#include "configloader.c"

void Initialize(){

    _Bool success;

    success = QueryPerformanceFrequency( &GL_PerformanceFrequency );
#ifdef DEBUGMODE
    if( !success ){
        printf("Unable to query performance counter: %d\n", GetLastError() );
    }
#endif
}





int main( int argc, const char* argv[] ){

    Initialize();
    LoadConfiguration("config.ini");

    return 0;
}