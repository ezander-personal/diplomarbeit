add_library(alg STATIC)

target_sources(alg PRIVATE
        Autocorr.cc
        Autocorr.h
        Corrdim.cc
        Corrdim.h
        Corrint.cc
        Corrint.h
        Corrslp.cc
        Corrslp.h
        Create.cc
        Create.h
        Cuts.cc
        Cuts.h
        Discrete.cc
        Discrete.h
        Evl.cc
        Evl.h
        Filter.cc
        Filter.h
        Fourier.cc
        Fourier.h
        Fuell.cc
        Fuell.h
        Histo.cc
        Histo.h
        Linear.cc
        Linear.h
        Ma.cc
        Ma.h
        Makets.cc
        Makets.h
        Median.cc
        Median.h
        Mutual.cc
        Mutual.h
        Neural.cc
        Neural.h
        Noise.cc
        Noise.h
        Packdim.cc
        Packdim.h
        Poinc.cc
        Poinc.h
        Rects.cc
        Rects.h
        Recurr.cc
        Recurr.h
        Stat.cc
        Stat.h
        Subtrend.cc
        Subtrend.h
        Surrogate.cc
        Surrogate.h
        Svd.cc
        Svd.h
        Takdim.cc
        Takdim.h
        Takslp.cc
        Takslp.h
        Voss.cc
        Voss.h
)

target_include_directories(alg PUBLIC ".")

target_link_libraries(alg util nr)

target_compile_definitions(alg PRIVATE ALGORITHM)