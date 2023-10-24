#ifndef CPP4_3DVIEWER_V2_0_2_MODEL_H_
#define CPP4_3DVIEWER_V2_0_2_MODEL_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

struct Data {
  int f_count{};
  int v_count{};
  double max_coord{};
  std::vector<int> facets{};
  std::vector<double> vertexes{};
};

class ModelViewer {
 public:
  ModelViewer() = default;
  ~ModelViewer() = default;
  void Parser(const std::string &path);
  Data &GetData() { return data_; }

 private:
  Data data_;
  void ParserLine(const std::string &str, std::vector<std::string> &elements);
  void PushFacets(std::vector<std::string> &elements);
  void PrintFacets();
  void PrintVertexes();
  void Clear() noexcept;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_MODEL_H_
