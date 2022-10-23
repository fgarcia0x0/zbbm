#pragma once

#include <book.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <optional>

#include <filesystem>

namespace zbbm
{
    namespace fs = std::filesystem;

    class book_manager
    {
    public:
        /**
         * @brief Construct a new book manager object
         * 
         * @param filepath o caminho do arquivo do database
         */
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

        /**
         * @brief Adquire a lista de livros
         * 
         * @return a lista de livros
         */
        [[nodiscard]]
        const auto& books() const
        {
            return m_books;
        }

        /**
         * @brief Busca um livro apartir do seu ISBN
         * 
         * @param isbn o isbn do livro
         * @return std::optional<book> 
         */
        [[nodiscard]]
        std::optional<book> find(std::string_view isbn) const noexcept;

        book& operator[](size_t index)
        {
            return m_books[index];
        }

        const book& operator[](size_t index) const
        {
            return m_books[index];
        }

    private:
        std::vector<book> m_books;
        fs::path m_filepath;
    };
} // namespace zbbm
