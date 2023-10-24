#ifndef CPP4_3DVIEWER_V2_0_2_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_2_CONTROLLER_H_

#include "../model/model_viewer.h"

namespace s21 {

class ControllerViewer {
 public:
  ControllerViewer(ModelViewer *model) : model_(model){}
  ~ControllerViewer() = default;
  void Parser(const std::string &path) { model_->Parser(path); }
  Data &GetData() { return model_->GetData(); }

 private:
  ModelViewer *model_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_2_CONTROLLER_H_
