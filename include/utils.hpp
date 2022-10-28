#pragma once 

#include <book.hpp>

#include <fstream>
#include <optional>

#define TRY_READ_VALUE(stream, field_name)     \
    if (!read_value(stream, field_name))       \
        return std::nullopt

namespace zbbm::detail
{
    template <typename T>
    static inline void write_value(std::ostream& fd, const T& value)
    {
        fd.write(reinterpret_cast<const char *>(&value), sizeof(value));
    }

    static inline void write_value(std::ostream& fd, const std::string& value)
    {
        write_value(fd, value.size());
        fd.write(value.data(), value.size());
    }

    static void write(std::ostream& fd, const book& target_book)
    {
        write_value(fd, target_book.isbn);
        write_value(fd, target_book.name);
        write_value(fd, target_book.author);

        write_value(fd, target_book.co_authors.size());
        for (const auto& coauthor : target_book.co_authors)
            write_value(fd, coauthor);

        write_value(fd, target_book.publisher);
        write_value(fd, target_book.launch_date);
        write_value(fd, target_book.language);

        fd.flush();
    }

    template <typename T>
    static inline bool read_value(std::istream& fd, T& value)
    {
        if (fd.read(reinterpret_cast<char *>(&value), sizeof(value)))
            return true;
        else
            return false;
    }

    static inline bool read_value(std::istream& fd, std::string& value)
    {
        size_t lenght = {};

        if (!fd.read(reinterpret_cast<char *>(&lenght), sizeof(lenght)))
            return false;
        
        value.resize(lenght);

        if (!fd.read(value.data(), value.size()))
            return false;

        return true;
    }

    static std::optional<book> read(std::istream& file_stream)
    {
        if (!file_stream)
            return std::nullopt;
        
        book target_book{};

        TRY_READ_VALUE(file_stream, target_book.isbn);
        TRY_READ_VALUE(file_stream, target_book.name);
        TRY_READ_VALUE(file_stream, target_book.author);

        size_t coauthors_size = {};
        TRY_READ_VALUE(file_stream, coauthors_size);

        target_book.co_authors.resize(coauthors_size);
        for (auto& coauthor : target_book.co_authors)
        {
            TRY_READ_VALUE(file_stream, coauthor);
        }

        TRY_READ_VALUE(file_stream, target_book.publisher);
        TRY_READ_VALUE(file_stream, target_book.launch_date);
        TRY_READ_VALUE(file_stream, target_book.language);

        return target_book;
    } 
}