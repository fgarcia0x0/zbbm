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

    void add_book(zbbm::book_manager& book_manager)
    {
        zbbm::book new_book;

        std::cout << "\n---------- Add Book ----------" << "\n";

        // TODO Make a book info validator
        std::cout << "Title: ";
        std::cin >> new_book.name;

        std::cout << "ISBN: ";
        std::cin >> new_book.isbn;

        std::cout << "Publisher: ";
        std::cin >> new_book.publisher;

        std::cout << "Language: ";
        std::cin >> new_book.language;

        std::cout << "Launch Date: ";
        std::cin >> new_book.launch_date;

        std::cout << "Author: ";
        std::cin >> new_book.author;

        int32_t has_co_authors;
        std::cout << "\nBook have co-authors ?" << "\n"
                  << "Ansewer (Yes = 1, No = 0): ";
        std::cin >> has_co_authors;

        if(has_co_authors == 1)
        {
            std::string new_co_author;
            for(bool co_authors = true; co_authors;)
            {
                std::cout << "\nCo-Author: ";
                std::cin >> new_co_author;
                new_book.co_authors.push_back(new_co_author);

                std::cout << "\nBook have another co-author ?" << "\n"
                          << "Ansewer (Yes = 1, No = 0): ";
                std::cin >> has_co_authors;

                if(has_co_authors != 1)
                    co_authors = false;
            }
        }
        else
        {
            new_book.co_authors.push_back("N/A");
        }

        book_manager.add(new_book);
        std::cout << "\n[INFO]: Book successfully added !" << "\n\n";
    }

    void show_book(zbbm::book book, bool detailed = false)
    {
        std::cout << "ISBN: " << book.isbn << " - " << book.name << '\n';

        if(detailed)
        {
            std::cout << "Book Details:"                          << "\n";
            std::cout << "\t- Language: "     << book.language    << "\n"
                      << "\t- Publisher: "    << book.publisher   << "\n"
                      << "\t- Launch Date: "  << book.launch_date << "\n"
                      << "\t- Author: "       << book.author      << "\n";
            
            std::string co_authors = {};
            for(std::string co_author : book.co_authors)
                co_authors.append(co_author + " ");

            std::cout << "\t- Co-Authors: " << co_authors << "\n";
        }
    }

    void list_book_register(zbbm::book_manager& book_manager)
    {
        if(!book_manager.books().empty())
        {
            std::cout << "\n---------- Books on Register ----------" << "\n";

            for (const auto& book : book_manager.books())
                show_book(book);

            std::cout << "---------- Books on Register ----------" << "\n\n";
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
                add_book(book_manager);
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