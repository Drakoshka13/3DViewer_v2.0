#include <gtest/gtest.h>

#include "../controller/controller_viewer.h"
#include "../model/model_viewer.h"

TEST(viewer_tests, test_1) {
  s21::ModelViewer a;
  s21::ControllerViewer b(&a);
  b.Parser("google_tests/cube.obj");

  EXPECT_DOUBLE_EQ(b.GetData().v_count, 24);
  EXPECT_DOUBLE_EQ(b.GetData().f_count, 72);

  float test_v[] = {1.0, -1.0,     -1.0, 1.0,  -1.0, 1.0,  -1.0,      -1.0,
                    1.0, -1.0,     -1.0, -1.0, 1.0,  1.0,  -0.999999, 0.999999,
                    1.0, 1.000001, -1.0, 1.0,  1.0,  -1.0, 1.0,       -1.0};
  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < 24; i++) {
    EXPECT_DOUBLE_EQ(b.GetData().vertexes[i], test_v[i]);
  }

  for (int j = 0; j < 72; j++) {
    EXPECT_DOUBLE_EQ(b.GetData().facets[j], test_f[j]);
  }
}

TEST(viewer_tests, test_2) {
  s21::ModelViewer a;
  s21::ControllerViewer b(&a);
  b.Parser("google_tests/cube.obj");

  EXPECT_DOUBLE_EQ(b.GetData().v_count, 24);
  EXPECT_DOUBLE_EQ(b.GetData().f_count, 72);

  float test_v[] = {1.0, -1.0,     -1.0, 1.0,  -1.0, 1.0,  -1.0,      -1.0,
                    1.0, -1.0,     -1.0, -1.0, 1.0,  1.0,  -0.999999, 0.999999,
                    1.0, 1.000001, -1.0, 1.0,  1.0,  -1.0, 1.0,       -1.0};
  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < 24; i++) {
    EXPECT_DOUBLE_EQ(b.GetData().vertexes[i], test_v[i]);
  }

  for (int j = 0; j < 72; j++) {
    EXPECT_DOUBLE_EQ(b.GetData().facets[j], test_f[j]);
  }
}

// TEST(viewer_tests, MoveX) {
//   s21::ModelViewer a;
//   s21::ControllerViewer b(&a);
//   b.Parser("google_tests/cube.obj");

//   s21::Object obj;
//   s21::Transform transform(&obj);
//   obj.pushVetrexesPoint(1.0, 2.0, 3.0);
//   obj.pushVetrexesPoint(-1.0, -2.0, -3.0);
//   transform.moveX(2.0);
//   const auto& vertexes = obj.getPoints()->vertexes_;
//   EXPECT_DOUBLE_EQ(vertexes[0], 3.0);
//   EXPECT_DOUBLE_EQ(vertexes[1], 2.0);
//   EXPECT_DOUBLE_EQ(vertexes[2], 3.0);
//   EXPECT_DOUBLE_EQ(vertexes[3], 1.0);
//   EXPECT_DOUBLE_EQ(vertexes[4], -2.0);
//   EXPECT_DOUBLE_EQ(vertexes[5], -3.0);
// }

