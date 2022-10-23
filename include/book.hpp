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
} // namespace zbbm
