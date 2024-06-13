add_executable(
  mathTest
  mathTest.cpp
)
target_include_directories(mathTest PRIVATE ${SRC_PATH})
target_link_directories(mathTest PRIVATE ${LIB_PATH})
target_link_libraries(
  mathTest
  GTest::gtest_main
  ${MATH_LIB}
)

gtest_discover_tests(mathTest)


