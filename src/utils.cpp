#include "../include/utils.hpp"


namespace zbbm::detail
{
    void write(std::ostream& handle, const book& obook)
    {
        handle.write(obook.isbn.c_str(), obook.isbn.size());
        handle.write(obook.name.c_str(), obook.name.size());
        handle.write(obook.author.c_str(), obook.author.size());
        
        auto n_authors {obook.co_authors.size()};
        handle.write(reinterpret_cast<char *>(&n_authors), sizeof(n_authors));

        for(auto idx{ 0U }; idx < n_authors; ++idx)
            handle.write(obook.co_authors[idx].c_str(), 
                         obook.co_authors[idx].size());
            
        
        handle.write(obook.publisher.c_str(), obook.publisher.size());
        handle.write(obook.launch_date.c_str(), obook.launch_date.size());
        handle.write(obook.language.c_str(), obook.language.size());
    }
}