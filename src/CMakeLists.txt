# Add this directory as an include path, so source files can include files
# relative to this directory
set_property(DIRECTORY APPEND PROPERTY INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(wordler
    main.x.cpp)

install(TARGETS wordler
    RUNTIME DESTINATION bin)

add_executable(wordler_tests
    Solver.t.cpp
    Wordle.t.cpp)
target_link_libraries(wordler_tests
    gtest
    gtest_main)
gtest_discover_tests(wordler_tests)

add_executable(wordler_benchmarks
    Solver.b.cpp
    Wordle.b.cpp)
target_link_libraries(wordler_benchmarks
    benchmark::benchmark
    benchmark::benchmark_main)
