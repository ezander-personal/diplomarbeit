add_executable(autocorr autocorr.cc)
target_compile_definitions(autocorr PRIVATE "-DINTERFACE")
target_link_libraries(autocorr alg)