#include <book_manager.h>
#include <utils.hpp>

#include <algorithm>
#include <exception>

namespace zbbm
{
    book_manager::book_manager(const fs::path& filepath)
        : m_filepath{ filepath }
    {
        if (!fs::exists(filepath) || !fs::is_regular_file(filepath))
            throw std::invalid_argument{ "Invalid filepath" };
    }

    void book_manager::add(const book& book)
    {
        m_books.push_back(book);
    }

    void book_manager::remove(std::string_view isbn)
    {
        auto size = std::erase_if(m_books, [isbn](const book& book)
                                  { return book.isbn == isbn; });
            
        if (size != 1)
            throw std::invalid_argument{ "invalid book isbn" };
    }

    void book_manager::clear()
    {
        m_books.clear();
    }

    bool book_manager::save(const fs::path& filepath)
    {
        std::ofstream ofd{ filepath, std::ios::app | std::ios::binary };
        if (!ofd.good())
            return false;

        for (const auto& book : m_books)
            zbbm::detail::write(ofd, book);

        return true;
    }

    bool book_manager::save()
    {
        return save(m_filepath);
    }

    std::optional<book> book_manager::find(std::string_view isbn) const noexcept
    {
        for (const auto& book : m_books)
            if (book.isbn == isbn)
                return book;

        return std::nullopt;
    }

} // namespace zbbm

