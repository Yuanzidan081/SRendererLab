#include <gtest/gtest.h>
#include "Render/Model.h"

TEST(ModelTest, ReadString)
{
    Model model("obj/head/african_head.obj");
    for (int i = 0; i < 5; ++i)
    {
        std::vector<int> f = model.GetFaces(i);
        std::cout << "f: " << f[0] << " " << f[1] << " " << f[2] << std::endl;
        for (int j = 0; j < 3; ++j)
        {
            Vec3f v1 = model.GetVetices(f[j] % 3);
            Vec3f v2 = model.GetVetices((f[j] + 1) % 3);

            int x1 = (v1.x + 1.0f) * 200.0f / 2.0f;
            int y1 = (v1.y + 1.0f) * 200.0f / 2.0f;
            int x2 = (v2.x + 1.0f) * 200.0f / 2.0f;
            int y2 = (v2.y + 1.0f) * 200.0f / 2.0f;
            std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
            // DrawLine(x1, y1, x2, y2, color);
        }
    }
}
