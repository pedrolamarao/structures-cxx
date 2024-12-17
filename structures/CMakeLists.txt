cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_library(structures)

file(GLOB_RECURSE main_cxx_sources CONFIGURE_DEPENDS "src/main/cxx/*")
file(GLOB_RECURSE main_ixx_sources CONFIGURE_DEPENDS "src/main/ixx/*")

target_sources(structures
    PUBLIC FILE_SET modules TYPE CXX_MODULES FILES
    ${main_ixx_sources}
    PRIVATE
    ${main_cxx_sources}
)

add_executable(structures-test)

file(GLOB_RECURSE test_cxx_sources CONFIGURE_DEPENDS "src/test/cxx/*")
file(GLOB_RECURSE test_ixx_sources CONFIGURE_DEPENDS "src/test/ixx/*")

target_sources(structures-test
        PRIVATE FILE_SET modules TYPE CXX_MODULES FILES
        ${test_ixx_sources}
        PRIVATE
        ${test_cxx_sources}
)

target_link_libraries(structures-test structures GTest::gmock)
