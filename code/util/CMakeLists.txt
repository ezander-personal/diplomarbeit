add_library(util STATIC)

target_link_libraries(util minilibg++ nr)

target_sources(util PRIVATE
        ExtGetOpt.cc
        ExtGetOpt.h
        Functions.cc
        Functions.h
        General.cc
        General.h
        Gpfile.cc
        Gpfile.h
        Runge.cc
        Runge.h
        Statistical.cc
        Statistical.h
        Vector.cc
        Vector.h
)

target_include_directories(util PUBLIC ".")
