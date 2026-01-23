#pragma once

#ifdef _WIN32
    #ifdef mlp_lib_EXPORTS
        #define MLP_API __declspec(dllexport)
    #else
        #define MLP_API __declspec(dllimport)
    #endif
#else
    #define MLP_API __attribute__((visibility("default")))
#endif