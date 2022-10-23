#pragma once 

#include <iostream>
#include <fstream>
#include <optional>
#include <book.hpp>

#define HANDLE_EXPR_LENGHT(var, attr, handle_file)\
        var = target_book.attr.size();\
        handle_file.write(reinterpret_cast<char *>(&var), sizeof(var));\
        handle_file.write(target_book.attr.c_str(), target_book.attr.size());

namespace zbbm::detail
{
    static inline void write(std::ostream& handle, const book& target_book)
    {
        size_t lenght_str {0u};

        HANDLE_EXPR_LENGHT(lenght_str, isbn, handle)
        HANDLE_EXPR_LENGHT(lenght_str, name, handle)
        HANDLE_EXPR_LENGHT(lenght_str, author, handle)
        
        auto n_authors{ target_book.co_authors.size() };
        handle.write(reinterpret_cast<char *>(&n_authors), sizeof(n_authors));

        for (const auto& coauthor : target_book.co_authors)
        {
            lenght_str = coauthor.size();
            handle.write(reinterpret_cast<char *>(&lenght_str), sizeof(lenght_str));
            handle.write(coauthor.c_str(), coauthor.size());
        }
        
        HANDLE_EXPR_LENGHT(lenght_str, publisher, handle)
        HANDLE_EXPR_LENGHT(lenght_str, launch_date, handle)
        HANDLE_EXPR_LENGHT(lenght_str, language, handle)

        handle.flush();
    }

    static inline void read_str(std::istream& file_stream, std::string& str)
    {
        size_t len_str {0U};
        
        file_stream.read(reinterpret_cast<char *>(&str), sizeof(len_str));
        str.resize(len_str);
        file_stream.read(str.data(), len_str);
    }

    static inline std::optional<book> read(std::istream& file_stream)
    {
        book obook {};
        
        read_str(file_stream , obook.isbn);
        read_str(file_stream , obook.name);
        read_str(file_stream , obook.author);

        size_t n_authors {0};
        file_stream.read(reinterpret_cast<char *>(&n_authors), sizeof(n_authors));
        
        for(size_t idx {}; idx < n_authors; ++idx)
            read_str(file_stream , obook.co_authors[idx]);

        read_str(file_stream , obook.publisher);
        read_str(file_stream , obook.launch_date);
        read_str(file_stream , obook.language);

        return obook;
    } 
}