#pragma once 

#include <iostream>
#include <book_manager.h>

namespace zbbm::interface
{
    static void display_user_interface()
    {
        std::cout << "==================== Ze Bigode's Book Manager ====================" << "\n";

        std::cout << "\n---------- Management Options ----------" << "\n"
                  << "1 - Add Book on Book Register"              << "\n" 
                  << "2 - Remove Book from Book Register"         << "\n"
                  << "3 - Find Book on Book Register"             << "\n"
                  << "4 - Edit Book from Book Register"           << "\n"
                  << "5 - List All Book's on Book Register"       << "\n"
                  << "6 - Clear Book Register"                    << "\n"
                  << "7 - Save Book Register"                     << "\n"
                  << "0 - Exit Ze Bigodes Book Manager"           << "\n"
                  << "---------- Management Options ----------"   << "\n";

        std::cout << "\nEnter your choice: " << "\n";
    }
}