add_executable(
  modelTest
  modelTest.cpp
)
target_include_directories(modelTest PRIVATE ${SRC_PATH})
target_link_directories(modelTest PRIVATE ${LIB_PATH})
target_link_libraries(
  modelTest
  GTest::gtest_main
  ${RENDER_LIB}
  ${MATH_LIB}
)

gtest_discover_tests(modelTest)


