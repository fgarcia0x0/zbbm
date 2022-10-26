#include <ui.h>

namespace zbbm
{
    static void ui_show_book(const zbbm::book& book, size_t book_index = SIZE_MAX)
    {   
        if (book_index != SIZE_MAX)
            std::cout << "[Book #" << std::to_string(book_index) << "]:" << std::endl;
        else
            std::cout << "[Book Details]" << '\n';

        std::cout << "\t- Name: "           << book.name             << '\n'
                  << "\t- ISBN: "           << book.isbn             << '\n'
                  << "\t- Language: "       << book.language         << '\n'
                  << "\t- Publisher: "      << book.publisher        << '\n'
                  << "\t- Launch Date: "    << book.launch_date      << '\n'
                  << "\t- Author: "         << book.author           << std::endl;

        std::cout << "\t- CoAuthors: " << ((book.co_authors.empty()) ? "N/A\n" : "\n");
        for (const auto& coauthor : book.co_authors)
            std::cout << "\t   - " << coauthor << '\n';

        std::cout.put('\n');
    }

    static void ui_show_edit_menu(zbbm::book& book)
    {
        ui_show_book(book);

        std::cout << "\n---------- [Edit Options] ----------" << "\n"
                  << "[1] - Edit Book Title"                  << "\n" 
                  << "[2] - Edit Book ISBN"                   << "\n" 
                  << "[3] - Edit Book Publisher"              << "\n" 
                  << "[4] - Edit Book Language"               << "\n" 
                  << "[5] - Edit Book Launch Date"            << "\n" 
                  << "[6] - Edit Book Author"                 << "\n" 
                  << "[7] - Edit Book Co-Authors"             << "\n"
                  << "[0] - Cancel Book Editing"              << "\n";
        
        std::cout << "\n[+] Enter your choice: ";

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
        zbbm::book new_book{};

        std::cout << "\n---------- Add Book ----------" << "\n";

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
                  << "Answer (Yes = 1, No = 0): ";
        std::cin >> has_co_authors;

        if (has_co_authors == 1)
        {
            std::string new_co_author;
            for (bool co_authors = true; co_authors;)
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
        std::cout << "[+] Enter the book ISBN: ";
        std::cin >> find_isbn;

        std::optional<book> book = manager.find(find_isbn);

        if (book.has_value())
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

        if (book.has_value())
            manager.edit(find_isbn, ui_show_edit_menu);
        else
            std::cout << "\n[WARNING]: Book not found !" << "\n\n";
    }

    void ui_handle_clear(book_manager& manager)
    {
        std::cout << "\n---------- Clear Book Register ----------" << "\n";

        if (manager.books().size() > 0)
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
        std::cout << "[+] Enter the book ISBN: ";
        std::cin >> find_isbn;

        std::optional<book> book = manager.find(find_isbn);

        if (book.has_value())
        {
            std::cout.put('\n');
            ui_show_book(book.value());
            std::cout << "[INFO]: Book found !" << "\n\n";
        }
        else
            std::cout << "[WARNING]: Book not found !" << "\n\n";
        
    }

    void ui_handle_list(book_manager& manager)
    {
        if(!manager.books().empty())
        {
            std::cout << "\n---------- Books register start ----------" << "\n";

            size_t book_index {};
            for (const auto& book : manager.books())
                ui_show_book(book, ++book_index);

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

