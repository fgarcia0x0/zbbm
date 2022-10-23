#pragma once

#include <book.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <string_view>

#include <filesystem>

namespace zbbm
{
    namespace fs = std::filesystem;

    class book_manager
    {
    public:
        book_manager(const fs::path& filepath);

        /**
         * @brief adiciona um livro ao book_manager
         * 
         * @param book o livro a ser adicionado
         */
        void add(const book& book);

        /**
         * @brief remove um livro do book_manager
         * 
         * @param isbn O isbn do livro a ser removido
         */
        void remove(std::string_view isbn);

        /**
         * @brief Deleta todos os livros do book_manager
         * 
         */
        void clear();

        /**
         * @brief Salva os livros do book_manager no caminho especificado por 'filepath'
         * 
         * @param filepath o caminho do arquivo
         * @return true se conseguiu salvar o arquivo
         * @return false se falhou ao salvar o arquivo
         */
        bool save(const fs::path& filepath);

        /**
         * @brief Salva os livros do book_manager no caminho especificado no construtor 
         * 
         * @return true se conseguiu salvar o arquivo
         * @return false se falhou ao salvar o arquivo
         */
        bool save();

        const auto& books() const
        {
            return m_books;
        }

    private:
        std::vector<book> m_books;
        fs::path m_filepath;
    };
} // namespace zbbm
