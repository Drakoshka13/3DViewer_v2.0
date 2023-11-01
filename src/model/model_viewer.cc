#include "model_viewer.h"



namespace s21 {

void ModelViewer::Parser(const std::string &path) {
    Clear();
    std::ifstream file;
    file.open(path.c_str(), std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::string str;
        std::vector<std::string> elements;
        while (std::getline(file, str)) {
            str += '\0';
            ParserLine(str, elements);
            if (!elements.empty()) {
                PushFacets(elements);
            }
        }
        data_.v_count = data_.vertexes.size();
    }
    file.close();
    DoMatrix();
}

void ModelViewer::PushFacets(std::vector<std::string> &elements) {
    std::vector<std::string>::iterator itr(elements.begin());
    int f = 0;
    while (itr != elements.end()) {
        f = std::stoi(*itr);
        if(f < 0){
            f = data_.vertexes.size()/3 + f + 1;
        }
        if (itr == elements.begin()) {
            data_.facets.push_back(f-1);
            data_.f_count += 1;
        } else {
            data_.facets.push_back(f-1);
            data_.facets.push_back(f-1);
            data_.f_count += 2;
        }
        itr++;
    }
    f = std::stoi(*elements.begin());
    if(f < 0){
        f = data_.vertexes.size()/3 + f + 1;
    }
    data_.facets.push_back(f-1);
    data_.f_count += 1;
    elements.clear();
}

void ModelViewer::ParserLine(const std::string &str,
                             std::vector<std::string> &elements) {
    std::string number;
    for (size_t i = 0; i < str.size(); i++) {
        if (i > 1 && (str[0] == 'v' || str[0] == 'f') && str[1] == ' ') {
            if (str[i] != ' ' && str[i] != '\0' && str[i] != '\n') {
                number += str[i];
            } else if(!number.empty()) {
                if (str[0] == 'v') {
                    data_.vertexes.push_back(std::stod(number));
                    if (i % 3 == 0) {
                        MaxMin(data_, 0);
                    } else if (i % 3 == 1) {
                        MaxMin(data_, 1);
                    } else if (i % 3 == 2) {
                        MaxMin(data_, 2);
                    }
                } else if (str[0] == 'f') {
                    if(number.find('/') == std::string::npos){
                        elements.push_back(number);
                    }else{
                        elements.push_back(number.erase(number.find_first_of('/')));
                    }
                }
                number.clear();
            }
        }
    }
}

void ModelViewer::MaxMin(Data &data_, const size_t &i) {
    if (data_.vertexes.back() > data_.max_min_xyz[i][0]) {
        data_.max_min_xyz[i][0] = data_.vertexes.back();
    } else if (data_.vertexes.back() < data_.max_min_xyz[i][1]) {
        data_.max_min_xyz[i][1] = data_.vertexes.back();
    }
}

void ModelViewer::Clear() noexcept {
    data_.v_count = 0;
    data_.f_count = 0;
    data_.max_coord = 0.0;
    for(int i = 0; i < 3; i++){
        data_.max_min_xyz[i][0] = 0;
        data_.max_min_xyz[i][1] = 0;
    }
    data_.facets.clear();
    data_.vertexes.clear();
}

}  // namespace s21

using namespace s21;

   void ModelViewer::DoMatrix() {
        matrix_ = S21Matrix();
        matrix_.SetRows(data_.v_count);
        matrix_.SetCols(3);
        //auto it = data_.vertexes.begin();
        for (int i = 0; i <  matrix_.GetRows(); ++i) {
        for (int j = 0; j <  matrix_.GetCols(); ++j) {
            matrix_(i, j) = data_.vertexes[i * 3 + j];
        }
    }

    }


void ModelViewer::Scale(double X, double Y, double Z) {
  for (int i = 0; i < matrix_.GetRows(); i++) {
    matrix_(i, 0) *= X;
    matrix_(i, 1) *= Y;
    matrix_(i, 2) *= Z;
  }
  FromMatrix();
}



    void ModelViewer::MoveX(double a) {
        for (int i = 0; i < matrix_.GetRows(); i++) matrix_(i, 0) += a;
        FromMatrix();
    }

    void ModelViewer::MoveY(double a) {
        for (int i = 0; i < matrix_.GetRows(); i++) matrix_(i, 1)  += a;
        FromMatrix();
    }

    void ModelViewer::MoveZ(double a) {
        for (int i = 0; i < matrix_.GetRows(); i++) matrix_(i, 2)  += a;
        FromMatrix();
    }



    void ModelViewer::RotationByOX(double angle) {
        for (int i = 0; i < matrix_.GetRows(); i++) {
            double y_0 = matrix_(i, 1);
            double z_0 =matrix_(i, 2);
            matrix_(i, 1) = cos(angle) * y_0 - sin(angle) * z_0;
            matrix_(i, 2) = sin(angle) * y_0 + cos(angle) * z_0;
  }
  FromMatrix();
}

void ModelViewer::RotationByOY(double angle) {
  for (int i = 0; i < matrix_.GetRows(); i++) {
    double x_0 = matrix_(i, 0);
    double z_0 = matrix_(i, 2);
    matrix_(i, 0) = sin(angle) * z_0 + cos(angle) * x_0;
    matrix_(i, 2) = cos(angle) * z_0 - sin(angle) * x_0;
  }
}

void ModelViewer::RotationByOZ(double angle) {
  for (int i = 0; i < matrix_.GetRows(); i++) {
    double x_0 = matrix_(i, 0);
    double y_0 = matrix_(i, 1);
    matrix_(i, 0) = cos(angle) * x_0 - sin(angle) * y_0;
    matrix_(i, 1) = sin(angle) * x_0 + cos(angle) * y_0;
  }
}



    void ModelViewer::FromMatrix() {
        //auto it = data_.vertexes.begin();
        for (int i = 0; i < matrix_.GetRows(); i++) {
            for (int j = 0; j < matrix_.GetCols(); j++) {
                data_.vertexes[i * 3 + j] = matrix_(i,j);
            }
        }
    }
