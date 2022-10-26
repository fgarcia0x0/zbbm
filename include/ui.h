#pragma once

#include <book_manager.h>
#include <banner.hpp>

#include <iostream>
#include <string_view>
#include <array>
#include <optional>

namespace zbbm
{
    enum class user_option
    {
        add,
        remove,
        edit,
        clear,
        find,
        list,
        save,
        update,
        exit
    };

    static inline auto get_line(std::string_view message, 
                                std::istream& input) -> std::optional<std::string>
    {
        std::cout << message;
        std::string line;

        if (!std::getline(input, line) || line.empty())
            return std::nullopt;

        return line;
    }

    void ui_handle_add(book_manager& manager);

    void ui_handle_remove(book_manager& manager);

    void ui_handle_edit(book_manager& manager);

    void ui_handle_clear(book_manager& manager);

    void ui_handle_find(book_manager& manager);

    void ui_handle_list(book_manager& manager);

    void ui_handle_save(book_manager& manager);

    void ui_handle_update(book_manager& manager);

    void ui_handle_exit(book_manager& manager);

    static void show_banner()
    {
        std::cout << banner::banner_options[1u];
        std::cout << "\t\t\t[Ze Bigode's Book Manager]" << "\n\n";
    }

    static inline user_option show_options()
    {
        std::cout << "[1] - Add Book on Book Register"              << "\n" 
                  << "[2] - Remove Book from Book Register"         << "\n"
                  << "[3] - Find Book on Book Register"             << "\n"
                  << "[4] - Edit Book from Book Register"           << "\n"
                  << "[5] - List All Books on Book Register"        << "\n"
                  << "[6] - Clear Book Register"                    << "\n"
                  << "[7] - Save Book Register"                     << "\n"
                  << "[8] - Update Book Register"                   << "\n"
                  << "[0] - Exit Ze Bigodes Book Manager"           << "\n";

        std::cout << "\n[+] Enter your choice: ";

        std::uint32_t opt{};
        if (!(std::cin >> opt) || opt > 8u)
        {
            std::cerr << "[-] invalid user input" << '\n';
            std::exit(EXIT_FAILURE);
        }

        return static_cast<user_option>(opt);
    }

    static constexpr inline void handle_option(user_option option, book_manager& manager)
    {
        constexpr std::array callbacks = 
        {
            ui_handle_exit,
            ui_handle_add,
            ui_handle_remove,
            ui_handle_find,
            ui_handle_edit,
            ui_handle_list,
            ui_handle_clear,
            ui_handle_save,
            ui_handle_update
        };

        callbacks[static_cast<unsigned>(option)](manager);
    }
}