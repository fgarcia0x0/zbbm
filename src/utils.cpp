#include <utils.hpp>

namespace zbbm::detail
{
    void write(std::ostream& handle, const book& target_book)
    {
        handle.write(target_book.isbn.c_str(), target_book.isbn.size());
        handle.write(target_book.name.c_str(), target_book.name.size());
        handle.write(target_book.author.c_str(), target_book.author.size());
        
        auto n_authors{ target_book.co_authors.size() };
        handle.write(reinterpret_cast<char *>(&n_authors), sizeof(n_authors));

        for (const auto& coauthor : target_book.co_authors)
            handle.write(coauthor.c_str(), coauthor.size());
        
        handle.write(target_book.publisher.c_str(), target_book.publisher.size());
        handle.write(target_book.launch_date.c_str(), target_book.launch_date.size());
        handle.write(target_book.language.c_str(), target_book.language.size());

        handle.flush();
    }
}