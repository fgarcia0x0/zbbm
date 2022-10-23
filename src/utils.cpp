#include "../include/utils.hpp"


namespace zbbm::detail
{
    void write(std::ostream& handle, const book& obook)
    {
        handle << obook.isbn;
        handle << obook.name;
        handle << obook.author;
        
        auto n_authors {obook.co_authors.size()};
        handle << n_authors;

        for(auto idx{ 0U }; idx < n_authors; ++idx)
            handle << obook.co_authors[idx];
        
        handle << obook.publisher;
        handle << obook.launch_date;
        handle << obook.language;
    }
}