#include <gtest/gtest.h>
#include "Render/Model.h"
#include <iostream>
TEST(ModelTest, ReadString)
{
    Model model("obj/head/african_head.obj");
}
TEST(ModelTest, RangeFLOAT)
{
    std::cout << std::numeric_limits<float>::max() << std::endl;
    std::cout << FLT_MAX << std::endl;
    std::cout << std::numeric_limits<float>::min() << std::endl;
    std::cout << FLT_MIN << std::endl;
}
