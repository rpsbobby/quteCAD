include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.10.0 # Use the latest stable release
)

FetchContent_MakeAvailable(catch2)

add_executable(runTests
    geometry/test_line.cpp
)
target_link_libraries(runTests PRIVATE geometry Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(runTests)