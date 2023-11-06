#include <gtest/gtest.h>

#include "../controller/controller_viewer.h"
#include "../model/model_viewer.h"

TEST(viewer_tests, test_1) {
  s21::ModelViewer a;
  s21::ControllerViewer b(&a);
  b.Parser("google_tests/cube.txt");

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
  b.Parser("google_tests/cube.txt");

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

TEST(viewer_tests, MoveX) {
  s21::ModelViewer a;
  s21::ControllerViewer b(&a);
  b.Parser("google_tests/cube.txt");
  b.ChangeX(1);
  b.ChangeY(2);
  b.ChangeZ(3);
}

TEST(viewer_tests, MoveY) {
  s21::ModelViewer a;
  s21::ControllerViewer b(&a);
  b.Parser("google_tests/cube.txt");
  b.RotateOX(1);
  b.RotateOY(2);
  b.RotateOZ(3);
}


TEST(Move, Test1) {
  double X = 2.5;
  double Y = -1;
  double Z = 100;
  s21::ModelViewer a;
  a.GetData().vertexes = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  std::vector<float> result = {3.5, 1, 103, 2.5, 3, 102, 7.5, 1, 101};
  a.MoveX(X);
  a.MoveY(Y);
  a.MoveZ(Z);
  EXPECT_TRUE(a.GetData().vertexes == result);
}

TEST(Rotate, Test1) {
  double X = M_PI_2;
  float Y = -M_PI;
  double Z = 2 * M_PI;
  s21::ModelViewer a;
  a.GetData().vertexes = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  std::vector<float> result = {-1, -3, -2, 0, -2, -4, -5, -1, -2};
  a.RotationByOX(X);
  a.RotationByOY(Y);
  a.RotationByOZ(Z);
  for (auto i = 0; i < 9; ++i) {
    EXPECT_NEAR(a.GetData().vertexes[i], result[i], 1E-6);
  }
}

TEST(Scale, Test1) {
  double X = 2;
  double Y = 0.5;
  double Z = 10;
  s21::ModelViewer a;
  a.GetData().vertexes = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  std::vector<float> result = {2, 1, 30, 0, 2, 20, 10, 1, 10};
  a.Scale(X, Y, Z);
  EXPECT_TRUE(a.GetData().vertexes == result);
}


