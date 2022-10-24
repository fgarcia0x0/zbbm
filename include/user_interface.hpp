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

    void option_handler(bool *running)
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
                  << "5 - List All Book's on Book Register"       << "\n"
                  << "6 - Clear Book Register"                    << "\n"
                  << "7 - Save Book Register"                     << "\n"
                  << "0 - Exit Ze Bigodes Book Manager"           << "\n"
                  << "---------- Management Options ----------"   << "\n";

        std::cout << "\nEnter your choice: ";
    }

    static void display_user_interface()
    {
        for( bool running = true; running; )
        {
            zbbm::interface::show_menu_interface();
            zbbm::interface::option_handler(&running);
        }
    }
}