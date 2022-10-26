#include <ui.h>

namespace zbbm
{
    static void ui_show_book(zbbm::book book, bool detailed = false)
    {   
        std::cout << "ISBN: " << book.isbn << " - " << book.name << '\n';

        if (detailed)
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

    static void ui_show_edit_menu(zbbm::book book)
    {
        ui_show_book(book, true);

        std::cout << "\n---------- Edit Options ----------" << "\n"
                  << "1 - Edit Book Title"                  << "\n" 
                  << "2 - Edit Book ISBN"                   << "\n" 
                  << "3 - Edit Book Publisher"              << "\n" 
                  << "4 - Edit Book Language"               << "\n" 
                  << "5 - Edit Book Launch Date"            << "\n" 
                  << "6 - Edit Book Author"                 << "\n" 
                  << "7 - Edit Book Co-Authors"             << "\n"
                  << "0 - Cancel Book Editing"              << "\n";
        
        std::cout << "\nEnter your choice: ";

        uint32_t choice;
        std::cin >> choice;

        bool edited = true;

        // TODO Book Component Validator
        switch (choice)
        {
        case 0:
            std::cout << "\n[INFO]: You exited the editing menu, nothing has been changed !"
                      << "\n";
            edited = false;
            break;
        case 1:
            std::cout << "New title: ";
            std::cin >> book.name;
            break;
        case 2:
            std::cout << "New ISBN: ";
            std::cin >> book.isbn;
            break;
        case 3:
            std::cout << "New publisher: ";
            std::cin >> book.publisher;
            break;
        case 4:
            std::cout << "New language: ";
            std::cin >> book.language;
            break;
        case 5:
            std::cout << "New launch date: ";
            std::cin >> book.launch_date;
            break;
        case 6:
            std::cout << "New author: ";
            std::cin >> book.author;
            break;
        case 7:
            int32_t has_co_authors;
            std::cout << "\nBook have co-authors ?"
                      << "\n"
                      << "Ansewer (Yes = 1, No = 0): ";
            std::cin >> has_co_authors;

            if (has_co_authors == 1)
            {
                std::string new_co_author;
                for (bool co_authors = true; co_authors;)
                {
                    std::cout << "\nCo-Author: ";
                    std::cin >> new_co_author;
                    book.co_authors.push_back(new_co_author);

                    std::cout << "\nBook have another co-author ?"
                              << "\n"
                              << "Ansewer (Yes = 1, No = 0): ";
                    std::cin >> has_co_authors;

                    if (has_co_authors != 1)
                        co_authors = false;
                }
            }
            else
            {
                book.co_authors.push_back("N/A");
            }
            break;
        default:
            std::cout << "\n[ERRO]: Invalid option !"
                      << "\n\n";
            edited = false;
            break;
        }

        if (edited)
            std::cout << "\n[INFO]: The book has been edited !"
                      << "\n\n";
        else
            std::cout << "\n[WARNING]: The book has not been changed !"
                      << "\n\n";
    }

    void ui_handle_add(book_manager& manager)
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

        manager.add(new_book);
        std::cout << "\n[INFO]: Book successfully added !" << "\n\n";
    }

    void ui_handle_remove(book_manager& manager)
    {
        std::cout << "\n---------- Remove Book ----------" << "\n";

        std::string find_isbn;
        std::cout << "Enter the book ISBN: ";
        std::cin >> find_isbn;

        std::optional<book> book = manager.find(find_isbn);

        if(book != std::nullopt)
        {
            manager.remove(find_isbn);
            std::cout << "\n[INFO]: " << book.value().name << " book has been removed !" << "\n\n";
        }
        else
            std::cout << "\n[WARNING]: Book not found !" << "\n\n";
    }

    void ui_handle_edit(book_manager& manager)
    {
        std::cout << "\n---------- Edit Book ----------" << "\n";

        std::string find_isbn;
        std::cout << "Enter the book ISBN: ";
        std::cin >> find_isbn;

        std::optional<book> book = manager.find(find_isbn);

        if(book != std::nullopt)
        {
            std::function<void (zbbm::book&)> edit_menu = ui_show_edit_menu;
            manager.edit(find_isbn, edit_menu);
        }
        else
            std::cout << "\n[WARNING]: Book not found !" << "\n\n";
    }

    void ui_handle_clear(book_manager& manager)
    {
        std::cout << "\n---------- Clear Book Register ----------" << "\n";

        if(manager.books().size() > 0)
        {
            manager.clear();
            std::cout << "\n[INFO]: The book register has been clear !" << "\n\n";
        }
        else
        {
            std::cout << "\n[WARNING]: There're not books in register, nothing will be shown" << "\n\n";
        }
    }

    void ui_handle_find(book_manager& manager)
    {
        std::cout << "\n---------- Find Book ----------" << "\n";

        std::string find_isbn;
        std::cout << "Enter the book ISBN: ";
        std::cin >> find_isbn;

        std::optional<book> book = manager.find(find_isbn);

        if(book != std::nullopt)
        {
            ui_show_book(book.value(), true);
            std::cout << "\n[INFO]: Book found !" << "\n\n";
        }
        else
            std::cout << "\n[WARNING]: Book not found !" << "\n\n";
        
    }

    void ui_handle_list(book_manager& manager)
    {
        if(!manager.books().empty())
        {
            std::cout << "\n---------- Books register start ----------" << "\n";

            for (const auto& book : manager.books())
                ui_show_book(book);

            std::cout << "---------- Books register end ----------" << "\n\n";
        }
        else    
            std::cout << "\n[WARNING]: There're not books in register, nothing will be shown" << "\n\n";
    }

    void ui_handle_save(book_manager& manager)
    {
        std::cout << "\n---------- Save books register ----------" << "\n";
        
        manager.save();
        std::cout << "\n[INFO]: The book register has been saved !" << "\n\n";
    }

    void ui_handle_update(book_manager& manager)
    {
        std::cout << "\n---------- Update books register ----------" << "\n";
        
        manager.update();
        std::cout << "\n[INFO]: The book register has been updated !" << "\n\n";
    }

    void ui_handle_exit(book_manager& manager)
    {
        std::exit(EXIT_SUCCESS);
    }
}

