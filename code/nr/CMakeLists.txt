add_library(nr STATIC)

target_sources(nr PRIVATE
        src/determ.cc
        src/fit.cc
        src/four1.cc
        src/fourn.cc
        src/gammln.cc
        src/gammq.cc
        src/gcf.cc
        src/gser.cc
        src/ludcmp.cc
        src/nr.cc
        src/nrutil.cc
        src/realft.cc
        src/tqli.cc
        src/tred2.cc
        include/complex.h
        include/matrixtempl.h
        include/nrutil.h
        include/oldvecmat.h
        include/vectortempl.h
)

target_include_directories(nr PUBLIC "include")
