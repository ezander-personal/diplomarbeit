add_library(nr STATIC)

target_sources(nr PRIVATE
        src/determ.cc
        src/four1.cc
        src/tqli.cc
        src/tred2.cc
        src/ludcmp.cc
        src/nr.cc
        src/nrutil.cc
        include/complex.h
        include/matrixtempl.h
        include/nrutil.h
        include/oldvecmat.h
        include/vectortempl.h
)

target_include_directories(nr PUBLIC "include")
