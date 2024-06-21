project(mathTest)
add_executable(
  ${PROJECT_NAME}
  mathTest.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_PATH})
target_link_libraries(
    ${PROJECT_NAME}
  GTest::gtest_main
  ${MATH_LIB}
)

gtest_discover_tests(${PROJECT_NAME})


