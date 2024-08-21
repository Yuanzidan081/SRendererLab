cmake_minimum_required(VERSION 3.20)
project(SRendererLab VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
# endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
# 添加这个指令来设置文件编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -GL -fp:fast")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -ffast-math")
endif()

if (Win32)
    add_compile_options("$<$<CONFIG:>: /utf-8>")
endif()

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib) # 指定库的输出路径
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src) # 指定源文件的输出路径
set(BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)  # 指定可执行文件的输出路径
set(DEP_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dep) # 第三方库的路径
set(DEP_PATH ${DEP_BASE_PATH}/stb)

set(MATH_LIB libmath)
set(RENDER_LIB librender)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})



# 添加库的依赖
#set(DEP_ALL_PATH ${DEP_STB_LIB_PATH})
add_subdirectory(dep)

set(BUILD_SRENDERERLAB ON)
if (BUILD_SRENDERERLAB)
    add_subdirectory(src)
endif()




#  ---------------------------- GoogleTest配置 ------------------------------- 
# Build GoogleTest dependencies.
set(BUILD_GoogleTest ON)
# 填充期间的日志输出可能非常冗长，使得配置阶段非常嘈杂。此缓存选项（ON默认情况下）隐藏所有填充输出，除非遇到错误。如果遇到挂起下载的问题，
# 暂时关闭此选项可能有助于诊断导致问题的内容群体。
set(FETCHCONTENT_QUIET OFF)
# 避免每次下载编译及其所有依赖
get_filename_component(_deps "./_deps" REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}/build")
# 在大多数情况下，保存的详细信息没有指定与用于内部子构建、最终源和构建区域的目录相关的任何选项。通常最好将这些决定留给FetchContent 模块来代表项目处理。
# 缓存变量控制收集所有内容填充目录的FETCHCONTENT_BASE_DIR 点，但在大多数情况下，开发人员不需要更改它。
# 默认位置是${PROJECT_SOURCE_DIR}/build/_deps，但如果开发人员更改此值，他们应该致力于保持路径短且刚好低于构建树的顶层，以避免在 Windows 上遇到路径长度问题。
set(FETCHCONTENT_BASE_DIR ${_deps})
if (BUILD_GoogleTest)
    # https://google.github.io/googletest/quickstart-cmake.html
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL "${PROJECT_SOURCE_DIR}/dep/googletest-5376968f6948923e2411081fd9372e71a59d8e77.zip"
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test/mathTest)
endif()



