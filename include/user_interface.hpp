#pragma once 

#include <iostream>
#include <book_manager.h>

namespace zbbm::interface
{
    enum InterfaceOption 
    {
        EXIT,
        ADD,
        REMOVE,
        FIND,
        EDIT,
        LIST,
        CLEAR,
        SAVE
    };

    void list_book_register(zbbm::book_manager& book_manager)
    {
        if(!book_manager.books().empty())
        {
            std::cout << "\n---------- Book Register ----------" << "\n";

            for (const auto& book : book_manager.books())
            {
                std::cout << "ISBN: " << book.isbn << " - " << book.name << '\n';
            }

            std::cout << "---------- Book Register ----------" << "\n\n";
        }
        else    
            std::cout << "\n[WARNING]: There're not books in register, nothing will be shown" << "\n";
    }

    void option_handler(zbbm::book_manager& book_manager, bool *running)
    {
        int32_t choice;
        std::cin >> choice;

        switch (choice)
        {
            case EXIT:
                *running = false;
                std::cout << "\n[INFO]: You exited the system, come back soon !" << "\n";
                break;
            case ADD:
                break;
            case REMOVE:
                break;
            case FIND:
                break;
            case EDIT:
                break;
            case LIST:
                list_book_register(book_manager);
                break;
            case CLEAR:
                break;
            case SAVE:
                break;
        
            default:
                std::cout << "\n[ERRO]: Invalid option, try again !" << "\n\n";
                break;
        }
    }

    void show_menu_interface()
    {
        std::cout << "==================== Ze Bigode's Book Manager ====================" << "\n";

        std::cout << "\n---------- Management Options ----------" << "\n"
                  << "1 - Add Book on Book Register"              << "\n" 
                  << "2 - Remove Book from Book Register"         << "\n"
                  << "3 - Find Book on Book Register"             << "\n"
                  << "4 - Edit Book from Book Register"           << "\n"
                  << "5 - List All Books on Book Register"       << "\n"
                  << "6 - Clear Book Register"                    << "\n"
                  << "7 - Save Book Register"                     << "\n"
                  << "0 - Exit Ze Bigodes Book Manager"           << "\n"
                  << "---------- Management Options ----------"   << "\n";

        std::cout << "\nEnter your choice: ";
    }

    static void display_user_interface(zbbm::book_manager& book_manager)
    {
        for( bool running = true; running; )
        {
            zbbm::interface::show_menu_interface();
            zbbm::interface::option_handler(book_manager, &running);
        }
    }
}