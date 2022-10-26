#include <iostream>
#include <vector>
#include <string>

#include <ui.h>

int main(int argc, char** argv)
{
    zbbm::book_manager book_manager{ "BookDatabase.zbbm" };
    zbbm::show_banner();

    for (;;)
    {
        zbbm::user_option opt = zbbm::show_options();
        zbbm::handle_option(opt, book_manager);
    }

    return {};
}