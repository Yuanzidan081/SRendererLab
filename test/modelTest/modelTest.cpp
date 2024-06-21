#include <gtest/gtest.h>
#include "Render/Model.h"
#include "Render/Texture2D.h"
#include <iostream>

/* #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h" */
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
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

TEST(ModelTest, STBIMAGE)
{
    // test jpg

    std::string inputPath = "res/11.jpg";
    int iw, ih, n;
    Texture2D texture1(inputPath);
    std::cout << texture1;
    Texture2D texture2("res/11.jpg");
    std::cout << texture2;
    Texture2D texture3("res/container.jpg");
    std::cout << texture3;

    // test tga
    Texture2D texture4("res/african_head_diffuse.tga");
    std::cout << texture4;

    // test png
    Texture2D texture5("res/lowPolyTree.png");
    std::cout << texture5;
    Texture2D texture6("res/awesomeface.png");
    std::cout << texture6;

    Texture2D texture7("res/container2.png");
    std::cout << texture7;
    Texture2D texture8("res/container2_specular.png");
    std::cout << texture8;
}
