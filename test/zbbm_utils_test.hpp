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

    std::ifstream rfile("Books.bin", std::ios::binary);
       if (!rfile.is_open())
        std::cerr << "Deu ruim abrir o jona vittar", exit(EXIT_FAILURE);

    std::optional<zbbm::book> rbook = zbbm::detail::read(rfile);

    std::cout << "Nome do Livro : "               << rbook->name        << std::endl;
    std::cout << "ISBN do Livro : "               << rbook->isbn        << std::endl; 
    std::cout << "Author do Livro : "             << rbook->author      << std::endl;
    //std::cout << ""
    std::cout << "Editora do Livro : "            << rbook->publisher   << std::endl;
    std::cout << "Data de Lançamento do Livro : " << rbook->launch_date << std::endl;
    std::cout << "Idioma do Livro : "             << rbook->language    << std::endl;

    rfile.close();
}