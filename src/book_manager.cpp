#include <book_manager.h>
#include <book.hpp>
#include <utils.hpp>

#include <algorithm>
#include <exception>

namespace zbbm
{
    void book_manager::update()
    {
        if (fs::exists(m_filepath) && fs::is_regular_file(m_filepath))
        {
            clear();
            std::ifstream input{ m_filepath, std::ios::binary };

            while (input)
            {
                auto book = zbbm::detail::read(input);
                if (book.has_value())
                    m_books.insert(book.value());
            }
        }
    }

    book_manager::book_manager(const fs::path& filepath)
        : m_filepath{ filepath }
    {
        update();
    }
    
    void book_manager::add(const book& book)
    {
        m_books.insert(book);
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
        std::ofstream ofd{ filepath, std::ios::binary };
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

    auto book_manager::find_iter(std::string_view isbn) 
        -> std::set<book, std::less<>>::iterator
    {
        book_light target_book{};
        target_book.isbn = isbn;
        return m_books.find(target_book);
    }

    std::optional<book> book_manager::find(std::string_view isbn) noexcept
    {
        auto iter = find_iter(isbn);
        if (iter != m_books.end())
            return *iter;

        return std::nullopt;
    }

    void book_manager::edit(std::string_view isbn, 
                            const std::function<void(book&)>& action)
    {
        auto iter = find_iter(isbn);
        if (iter == m_books.end())
            return;

        auto node = m_books.extract(iter);
        action(node.value());
        m_books.insert(std::move(node));
    }
} // namespace zbbm

