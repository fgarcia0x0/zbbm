#pragma once

#include <book.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <optional>
#include <set>
#include <functional>
#include <filesystem>

namespace fs = std::filesystem;

namespace zbbm
{
    /**
     * @brief Classe responsável por gerenciar os livros
     * 
     */
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
         * @brief 
         * 
         */
        void update();

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
         * @brief Busca um deteminado livro e retorna seu iterator
         * 
         * @param isbn isbn do livro a ser buscado
         * @return iterator do livro caso esteja no book_manager
         */
        [[nodiscard]]
        auto find_iter(std::string_view isbn) -> std::set<book, std::less<>>::iterator;

        /**
         * @brief Busca um livro apartir do seu ISBN
         * 
         * @param isbn o isbn do livro
         * @return std::optional<book> 
         */
        [[nodiscard]]
        std::optional<book> find(std::string_view isbn) noexcept;

        /**
         * @brief Edita um determinado livro no qual o isbn referencia 
         * 
         * @param isbn o isbn do livro
         * @param action callback aplicado ao livro procurado
         */
        void edit(std::string_view isbn, const std::function<void(book&)>& action);

    private:
        std::set<book, std::less<>> m_books;
        fs::path m_filepath;
    };
} // namespace zbbm
