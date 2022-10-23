#pragma once

#include <utils.hpp>
#include <book.hpp>

#include <fstream>
#include <iostream>

static void zbb_utils_test()
{
    std::ofstream file("Books.bin", std::ios::binary);

    if (!file.is_open())
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

    zbbm::detail::write(file, obook);
    file.close();
}