
unsigned ReadConfigItemAsString( const char* itemname, const char* buf, char* itembuf, unsigned itembuf_sz ){
    
    if( !itemname || !(*itemname) || !buf || !itembuf || !itembuf_sz )
        return 0;

    const char* itempos = strstr(buf,itemname);
    if( !itempos ) return 0;

    const char* itemstart = strchr(itempos, '=');
    if( !itemstart ) return 0;
    ++itemstart; //Do not include '='

    const char* itemend = strstr( itemstart, "\r\n" );
    if( !itemend ) return 0;

    unsigned item_sz = itemend - itemstart;
    if( itembuf_sz-1 < item_sz ) return 0;

    SecureZeroMemory( itembuf, itembuf_sz );
    memcpy( itembuf, itemstart, item_sz );

    return item_sz;
}

double ReadConfigItemAsDouble( const char* itemname, const char* buf ){

    const char itembuf_sz = 0x40;
    char itembuf[itembuf_sz];

    unsigned input_sz = ReadConfigItemAsString(
        itemname, buf, itembuf, itembuf_sz
    );

    if( !input_sz ) return -1;
    return atof(itembuf);
}

void LoadConfiguration( const char* fname ){

    _Bool success;
    DWORD dummy;

    HANDLE file = CreateFile(
        fname,
        GENERIC_READ    /*access*/,
        FILE_SHARE_READ /*sharemode*/,
        0               /*default security*/,
        OPEN_EXISTING   /*open mode*/,
        FILE_ATTRIBUTE_NORMAL,
        0               /*template*/
    );

#ifdef DEBUGMODE
    if( !file || file == INVALID_HANDLE_VALUE ){
        printf("Failed to open file %s with error: %d\n", fname, GetLastError() );
    }
#endif

    LARGE_INTEGER fsize;
    success = GetFileSizeEx( file, &fsize );
#ifdef DEBUGMODE
    if( !success ){
        printf("Failed to query file size of %s with error: %d\n", fname, GetLastError() );
    }
#endif

    char* buffer = (char*) malloc(fsize.QuadPart+1);
    success = ReadFile( 
        file, buffer, 
        fsize.QuadPart,
        &dummy, 0
    );
#ifdef DEBUGMODE
    if( !success ){
        printf("Failed to read from file %s with error: %d\n", fname, GetLastError() );
    }
#endif

    for( char* c = buffer; c < buffer + fsize.QuadPart; ++c )
        *c = (char) tolower(*c);

/*-------------------------------------------------------------
 * Read sequnce from config
 */

    GL_SequnceLength = ReadConfigItemAsString(
        "sequence", buffer,
        GL_Sequence, GL_SequnceCap
    );
#ifdef DEBUGMODE
    if( !GL_SequnceLength || GL_SequnceLength >= GL_SequnceCap ){
        printf(
            "Failed to load sequence from %s with sequence length %d\n",
            fname, GL_SequnceLength
        );
    }
#endif

/*-------------------------------------------------------------
 * Read cycle from config
 */
    GL_Cycle = ReadConfigItemAsDouble("cycle",buffer);
#ifdef DEBUGMODE
    if( GL_Cycle < 0 ){
        printf("Failed to load cycle time from %s\n", fname);
    }
#endif

/*-------------------------------------------------------------
 * Read cycle variance from config
 */
    GL_CycleVariance = ReadConfigItemAsDouble("cyclevariance",buffer);
#ifdef DEBUGMODE
    if( GL_CycleVariance < 0 ){
        printf("Failed to load cycle variance from %s\n", fname);
    }
#endif

/*-------------------------------------------------------------
 * Read hold time from config
 */
    GL_HoldTime = ReadConfigItemAsDouble("holdtime",buffer);
#ifdef DEBUGMODE
    if( GL_HoldTime < 0 ){
        printf("Failed to load hold time from %s\n", fname);
    }
#endif

    CloseHandle(file);
}