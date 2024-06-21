project(modelTest)

add_executable(
  modelTest
  modelTest.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_PATH} ${DEP_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_PATH} )
target_link_libraries(
    ${PROJECT_NAME}
  GTest::gtest_main
  ${RENDER_LIB}
  ${MATH_LIB}
)

gtest_discover_tests(${PROJECT_NAME})


