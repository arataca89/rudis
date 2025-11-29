#ifndef TOOLS_H
#define TOOLS_H

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

// Códigos ANSI para cores
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Estilos
#define BOLD    "\033[1m"

// Combinações úteis
#define PROMPT_COLOR  YELLOW BOLD
#define ERROR_COLOR   RED BOLD
#define SUCCESS_COLOR GREEN BOLD
#define INFO_COLOR    CYAN

#endif