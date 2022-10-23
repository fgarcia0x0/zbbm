#pragma once

#include <string>
#include <vector>

/*
    utils.hpp => namespace zbbm::detail
        => write(ostream&, const book&)
        => std::optional<book> read(std::istream&)

    class book_manager{}
        -> book_manager(fstream book_data)
        -> add(book)(Essencial)
        -> remove(book)(Essencial)
        -> editar()
        -> clear()(Essencial)
        -> save()
        -> save(ostream&)
*/

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
} // namespace zbbm
