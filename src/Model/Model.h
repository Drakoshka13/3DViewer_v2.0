#ifndef CPP4_3DVIEWER_V2_0_2_MODEL_H_
#define CPP4_3DVIEWER_V2_0_2_MODEL_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Action { kRotX, kRotY, kRotZ, kMoveX, kMoveY, kMoveZ, kScaleP, kScaleM };

enum Coord { kX, kY, kZ };

struct Data {
  double far;
  double near;
  int v_count;
  int e_count;
  double max_coord;
  std::vector<int> facets;
  std::vector<double> vertexes;
};

namespace s21 {
class Parser {
 public:
  Parser(){};
  Parser(Data *data);
  ~Parser() = default;

  void Clear() noexcept;
  void SetPerspectiveData() noexcept;
  void ProcessLine(std::string line);
  void ParseFacet(std::string &line);
  void ParseVertex(std::string &line);
  void Parse(const std::string &path);
  void DelNum(std::string &line) const;
  void DelSpace(std::string &line) const;

 private:
  Data *data_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_MODEL_H_