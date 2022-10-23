#pragma once 

#include <iostream>
#include <fstream>
#include "book.hpp"

namespace zbbm::detail
{
    void write(std::ostream&, const book&);
}