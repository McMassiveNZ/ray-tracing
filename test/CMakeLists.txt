include(${CMAKE_SCRIPTS_DIR}/googletest.cmake)

add_executable(
  ray-tracing-test
  test_main.cpp
)

target_link_libraries(
  ray-tracing-test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(ray-tracing-test)
