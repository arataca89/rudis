#ifndef COMMON_H
#define COMMON_H

// Detecta o sistema operacional
#ifdef _WIN32
    #define OS "windows"
#elif __linux__
    #define OS "linux"
#elif __APPLE__
    #define OS "macos"
#else
    #define OS "os unknown"
#endif

#define STR_SIZE 256

#define VERSION "0.1.0"

#endif