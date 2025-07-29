add_library(minilibg++ STATIC
        iomanip.h)

target_sources(minilibg++ PRIVATE
        ACG.cc
        ACG.h
        GetOpt.cc
        GetOpt.h
        Normal.cc
        Normal.h
        RNG.cc
        RNG.h
        Random.cc
        Random.h
        String.cc
        String.h
        Uniform.cc
        Uniform.h
        fstream.h
        iostream.h
        new.h
)

target_include_directories(minilibg++ PUBLIC ".")
