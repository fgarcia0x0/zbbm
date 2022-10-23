#include <book_manager.h>

#include <algorithm>
#include <exception>

namespace zbbm
{
    book_manager::book_manager(const fs::path& filepath)
        : m_filepath{ filepath }
    {
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
        return false;
    }

    bool book_manager::save()
    {
        return save(m_filepath);
    }

} // namespace zbbm

