
#define DEBUGMODE

#ifdef DEBUGMODE
#include <stdio.h>
#endif

#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <wincrypt.h>

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

    success = CryptAcquireContext(
        &GL_CryptProv,
        0 /*default container name*/,
        0 /*default provider name*/,
        PROV_RSA_AES, CRYPT_NEWKEYSET
    );

    if( !success ){

        DWORD code = GetLastError();
        if( code != NTE_EXISTS ){
        #ifdef DEBUGMODE
            printf("Cannot acquire source of entropy. Wincrypt error: %d\n", code );
        #endif
        }

        success = CryptAcquireContext(
            &GL_CryptProv,
            0 /*default container name*/,
            0 /*default provider name*/,
            PROV_RSA_AES,
            0 /*default flags*/
        );

        #ifdef DEBUGMODE
        if( !success ){
            code = GetLastError();
            printf("Cannot acquire source of entropy. Wincrypt error: %d\n", code );
        }
        #endif
    }

}

int main( int argc, const char* argv[] ){

    Initialize();
    LoadConfiguration("config.ini");


    return 0;
}