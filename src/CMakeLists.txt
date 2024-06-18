#  ---------------------------- QT配置 ------------------------------- 
# set(CMAKE_PREFIX_PATH "E:/Qt/5.12.12/msvc2017_64/")
# set(QT5_DIR "E:/Qt/5.12.12/msvc2017_64/lib/cmake/Qt5/")
set(CMAKE_AUTOMOC ON) # 自动生成信号槽代码
set(CMAKE_AUTORCC ON) # 自动生成资源文件代码
set(CMAKE_AUTOUIC ON) # 自动把ui转换为C++代码
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(MATH_DIR ${SRC_PATH}/Math)
set(UI_DIR ${SRC_PATH}/UI)
set(CORE_DIR ${SRC_PATH}/Core)
set(RENDER_DIR ${SRC_PATH}/Render)
set(ALGORITHM_DIR ${SRC_PATH}/Algorithm)

file(GLOB MATH_FILES "${MATH_DIR}/*.cpp" "${MATH_DIR}/*.h")
file(GLOB UI_FILES "${UI_DIR}/*.cpp" "${UI_DIR}/*.h" "${UI_DIR}/*.ui") 
file(GLOB CORE_FILES "${CORE_DIR}/*.cpp" "${CORE_DIR}/*.h")
file(GLOB RENDER_FILES "${RENDER_DIR}/*.cpp" "${RENDER_DIR}/*.h")
file(GLOB ALGORITHM_FILES "${ALGORITHM_DIR}/*.cpp" "${ALGORITHM_DIR}/*.h")


set(SRC_FILES
main.cpp
${UI_FILES}
${MATH_FILES}
${CORE_FILES}
${RENDER_FILES}
${ALGORITHM_FILES}
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PRIVATE 
${SRC_PATH} ${MATH_DIR} ${UI_DIR} ${CORE_DIR} ${RENDER_DIR} ${ALGORITHM_DIR})

add_library(${MATH_LIB} STATIC ${MATH_FILES})
target_include_directories(${MATH_LIB} PRIVATE ${MATH_DIR})
add_library(${RENDER_LIB} STATIC "${RENDER_DIR}/Model.cpp" "${RENDER_DIR}/Model.h" ${MATH_FILES})
target_include_directories(${RENDER_LIB} PRIVATE ${RENDER_DIR} ${MATH_DIR} ${SRC_PATH} ${ALGORITHM_DIR})