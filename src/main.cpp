#include <iostream>
#include <book.hpp>
#include <vector>
#include <string>

#include <user_interface.hpp>

int main(int argc, char** argv)
{
    zbbm::book_manager book_manager{ "BookDatabase.zbbm" };

    zbbm::interface::display_user_interface(book_manager);
    return {};
}
