#if !defined( SYS_DEDH )
#define SYS_DEDH
#ifdef _WIN32
#pragma once
#endif

long Sys_LoadLibrary( char *lib );
void Sys_FreeLibrary( long library );
void *Sys_GetProcAddress( long library, const char *name );
void Sys_Sleep( int msec );
void Sys_Printf(char *fmt, ...);
void Sys_ErrorMessage( int level, const char *msg );

#endif // SYS_DEDH