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
            if(str[0] == 'v' && str[0] == ' '){
                data_.arr_v_count++;
            }
            ParserLine(str, elements);
            if (!elements.empty()) {
                PushFacets(elements);
            }

        }
        data_.v_count = data_.vertexes.size();
    }
    file.close();
}

void ModelViewer::PushFacets(std::vector<std::string> &elements) {
    std::vector<std::string>::iterator itr(elements.begin());
    while (itr != elements.end()) {



        if (itr == elements.begin()) {
            int f = std::stoi(*itr);
            if(f < 0){
                f = data_.vertexes.size()/3 + f + 1;
            }
            data_.facets.push_back(f-1);
            data_.f_count += 1;
        } else {
            int f = std::stoi(*itr);
            if(f < 0){
                f = data_.vertexes.size()/3 + f + 1;
            }
            data_.facets.push_back(f-1);
            data_.facets.push_back(f-1);
            data_.f_count += 2;
        }
        itr++;
    }

    int f = std::stoi(*elements.begin());
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
            }

            else if(!number.empty()) {
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

void ModelViewer::PrintFacets() {
    std::vector<unsigned int>::iterator it(data_.facets.begin());
    while (it != data_.facets.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

void ModelViewer::PrintVertexes() {
    std::vector<float>::iterator itr(data_.vertexes.begin());
    while (itr != data_.vertexes.end()) {
        std::cout << *itr << " ";
        itr++;
    }
    std::cout << std::endl;
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
