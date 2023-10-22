#include "Model.h"

namespace s21 {
Parser::Parser(Data *data) : data_(data) {
  data_->far = 0.0;
  data_->near = 0.0;
  data_->v_count = 0;
  data_->e_count = 0;
  data_->max_coord = 0.0;
}

void Parser::Clear() noexcept {
  data_->far = 0.0;
  data_->near = 0.0;
  data_->v_count = 0;
  data_->e_count = 0;
  data_->max_coord = 0.0;
  data_->facets.clear();
  data_->vertexes.clear();
}

void Parser::Parse(const std::string &path) {
  Clear();
  std::ifstream file;
  file.open(path.c_str(), std::ios::in | std::ios::binary);
  if (file.is_open()) {
    std::string str;
    std::string poligon;
    std::vector<std::string> elements;

    while (std::getline(file, str)) {
      str += '\0';
      for (size_t i = 0; i < str.size(); i++) {
        if (i > 1 && str[0] == 'v' && str[1] == ' ') {
          if (str[i] != ' ' && str[i] != '\0') {
            poligon += str[i];
          } else {
            data_->vertexes.push_back(std::stod(poligon));
            poligon.clear();
          }
        }

        if (i > 1 && str[0] == 'f' && str[1] == ' ') {
          if (str[i] != ' ' && str[i] != '\0') {
            poligon += str[i];
          } else {
            elements.push_back(poligon.erase(poligon.find_first_of('/')));
            poligon.clear();
          }
        }
      }

      if (!elements.empty()) {
        std::vector<std::string>::iterator itr = elements.begin();
        while (itr != elements.end()) {
          if (itr == elements.begin()) {
            data_->facets.push_back(std::stoi(*itr) - 1);
          } else {
            data_->facets.push_back(std::stoi(*itr) - 1);
            data_->facets.push_back(std::stoi(*itr) - 1);
          }
          itr++;
        }
        data_->facets.push_back(std::stoi(elements.front()) - 1);
        elements.clear();
      }
    }
  }

  data_->v_count = data_->vertexes.size();

  // std::cout << data_->v_count;

  // std::cout << std::endl;
  // std::vector<double>::iterator itr(data_->vertexes.begin());
  // while (itr != data_->vertexes.end()) {
  //   std::cout << *itr << " ";
  //   itr++;
  // }

  // std::cout << std::endl;
  // std::vector<int>::iterator it(data_->facets.begin());
  // while (it != data_->facets.end()) {
  //   std::cout << *it << " ";
  //   it++;
  // }

  file.close();
}

}  // namespace s21