#ifndef CPP4_3DVIEWER_V2_0_2_MODEL_STRUCT_H_
#define CPP4_3DVIEWER_V2_0_2_MODEL_STRUCT_H_

#include <vector>

typedef struct View {
  double far;
  double near;
  int v_count;
  int e_count;
  double max_coord;
  std::vector<int> facets;
  std::vector<double> vertexes;
} Data;

enum Action { kRotX, kRotY, kRotZ, kMoveX, kMoveY, kMoveZ, kScaleP, kScaleM };

enum Coord { kX, kY, kZ };

#endif  // CPP4_3DVIEWER_V2_0_2_MODEL_STRUCT_H_