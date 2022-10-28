#include <ui.h>

namespace zbbm
{
    static inline void exit_with_error(std::string_view message)
    {
        std::cerr << "[-] " << message << '\n';
        std::exit(EXIT_FAILURE);
    }

    static inline std::string read_isbn(std::string_view message)
    {
        std::string target_isbn;
        std::cout << message;

        if (!(std::cin >> target_isbn))
            exit_with_error("invalid input");

        for (const char& ch : target_isbn)
        {
            if (!std::isdigit(uint8_t(ch)) && (ch != '-'))
                exit_with_error("invalid isbn");
        }

        return target_isbn;
    }

    static inline void handle_coauthors(book& new_book)
    {
        std::optional<std::string> new_coauthor{};
        uint32_t has_coauthor{};

        std::cout << "\nBook have co-authors ?" << "\n"
                  << "Answer (Yes = 1, No = 0): ";

        if (!(std::cin >> has_coauthor) || has_coauthor > 1u)
            exit_with_error("invalid input");

        if (!has_coauthor)
            return;

        std::cin.ignore(sizeof(char));

        for (;;)
        {
            new_coauthor = get_line("[+] Co-Author: ", std::cin);
            if (!new_coauthor)
                exit_with_error("invalid coauthor value");

            new_book.co_authors.push_back(std::move(new_coauthor.value()));

            std::cout << "\nBook have another co-author ?" << "\n"
                      << "Ansewer (Yes = 1, No = 0): ";

            if (!(std::cin >> has_coauthor) || has_coauthor > 1u)
                exit_with_error("invalid input");

            std::cin.ignore(sizeof(char));

            if (!has_coauthor)
                break;
        }
    }

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

    static inline void show_coauthors(const std::vector<std::string>& coauthors)
    {
        std::cout << "\t- CoAuthors: " << ((coauthors.empty()) ? "N/A\n" : "\n");
        const auto size_co = coauthors.size();

        for (size_t idx {}; idx < size_co; ++idx)
            std::cout << "\t   [" << idx + 1 << "] - " << coauthors[idx] << '\n';
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
        uint32_t choice = {0};

        if (!(std::cin >> choice))
            exit_with_error("invalid input");

        // ignorar '\n'
        std::cin.ignore(sizeof(char));

        bool edited = true;
        size_t coauthor_id {};

        std::optional<std::string> result{};

        switch (choice)
        {
        case 0:
            std::cout << "\n[INFO]: You exited the editing menu, nothing has been changed !" << "\n";
            edited = false;
            break;
        case 1:
            result = get_line("New title: ", std::cin);
            if (!result)
                exit_with_error("invalid title name");
            book.name = result.value();
            break;
        case 2:
            book.isbn = read_isbn("New ISBN: ");
            break;
        case 3:
            result = get_line("New publisher: ", std::cin);
            if (!result)
                exit_with_error("invalid publisher value");
            book.publisher = result.value();
            break;
        case 4:
            result = get_line("New language: ", std::cin);
            if (!result)
                exit_with_error("invalid language value");
                
            book.language = result.value();
            break;
        case 5:
            result = get_line("New launch date: ", std::cin);
            if (!result)
                exit_with_error("invalid launch date");
                
            book.launch_date = result.value();
            break;
        case 6:
            result = get_line("New author: ", std::cin);
            if (!result)
                exit_with_error("invalid author");
                
            book.author = result.value();
            break;       
        case 7:
            show_coauthors(book.co_authors);
            
            std::cout << "[+] Enter the number of the co-author you want to edit"
                      << " (enter 0 to cancel): ";
            
            if (!(std::cin >> coauthor_id))
            {
               exit_with_error("invalid input");
            }
            else if((coauthor_id) == 0)
            {
                edited = false;
                break;
            }
            else if(coauthor_id > book.co_authors.size())
            {
                exit_with_error("Invalid coauthor id!!!");
            }

            std::cin.ignore(sizeof(char));

            result = get_line("[+] New coauthor: ", std::cin);
            if (!result)
                exit_with_error("invalid coauthor value");

            book.co_authors[coauthor_id - 1] = result.value();

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
        std::cin.ignore(sizeof(char));

        auto get_field = [](std::string_view message, 
                            std::string_view error_message,
                            std::string& field) 
        {
            auto result = get_line(message, std::cin);
            if (!result)
                exit_with_error(error_message);
            field = result.value();
        };

        std::cout << "\n---------- Add Book ----------" << "\n";

        get_field("Title: ", "invalid title name", new_book.name);

        new_book.isbn = read_isbn("ISBN: ");
        std::cin.ignore(sizeof(char));

        get_field("Publisher: ", "invalid publisher name", new_book.publisher);
        get_field("Language: ", "invalid language name", new_book.language);
        get_field("Launch Date: ", "invalid launch date name", new_book.launch_date);
        get_field("Author: ", "invalid author name", new_book.author);

        handle_coauthors(new_book);

        manager.add(new_book);
        std::cout << "\n[INFO]: Book successfully added !" << "\n\n";
    }

    void ui_handle_remove(book_manager& manager)
    {
        std::cout << "\n---------- Remove Book ----------\n";

        std::string target_isbn = read_isbn("[+] Enter the book ISBN: ");
        std::optional<book> book = manager.find(target_isbn);

        if (book.has_value())
        {
            manager.remove(target_isbn);
            std::cout << "\n[INFO]: " << book.value().name << " book has been removed !" << "\n\n";
        }
        else
            std::cout << "\n[WARNING]: Book not found !" << "\n\n";
    }

    void ui_handle_edit(book_manager& manager)
    {
        std::cout << "\n---------- Edit Book ----------" << "\n";

        std::string target_isbn = read_isbn("[+] Enter the book ISBN: ");
        std::optional<book> book = manager.find(target_isbn);

        if (book.has_value())
            manager.edit(target_isbn, ui_show_edit_menu);
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

        std::string target_isbn = read_isbn("[+] Enter the book ISBN: ");
        std::optional<book> book = manager.find(target_isbn);

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
        if (!manager.books().empty())
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
        
        if (manager.save())
            std::cout << "\n[INFO]: The book register has been saved !" << "\n\n";
        else
            std::cout << "\n[WARN]: Cannot save the book register!" << "\n\n";
        
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

