#include <iostream>
#include <book.hpp>
#include <vector>
#include <string>
#include "../include/utils.hpp"

int main(int argc, char** argv)
{
    std::cout << "zbbm init" << '\n';
    std::ofstream file1("Books", std::ios::binary);

    if (!file1.is_open())
        std::cerr << "Deu ruim abrir o jona vittar", exit(EXIT_FAILURE);
    
    std::vector<std::string> authors {"Bryan", "Joao"};

    zbbm::book obook
    {"4545214614",
     "Joandabe History",
     "Jonadabe David",
     authors,
     "Vittas",
     "20122001",
     "portugues"};

    zbbm::detail::write(file1, obook);

    file1.close();

    return {};
}
