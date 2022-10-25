#pragma once

#include <string>
#include <vector>

namespace zbbm
{
    struct book
    {
        std::string isbn;
        std::string name;
        std::string author;
        std::vector<std::string> co_authors;
        std::string publisher;
        std::string launch_date;
        std::string language;
    };

    struct book_light
    {
        std::string isbn;
    };

    inline bool operator<(const book& book, const book_light& book_light)
    {
        return book.isbn < book_light.isbn;
    }

    inline bool operator<(const book_light& book_light, const book& book)
    {
        return book_light.isbn < book.isbn;
    }

    inline bool operator<(const book& book1, const book& book2)
    {
        return book1.isbn < book2.isbn;
    }

} // namespace zbbm
