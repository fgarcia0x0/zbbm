#pragma once

#include <iostream>
#include <filesystem>
#include <book_manager.h>

static void print_books(const zbbm::book_manager& bm)
{
    for (const auto& book : bm.books())
    {
        std::cout << book.name << '\n';
    }
    std::cout.put('\n');
}

static void zbbm_bm_test()
{
    std::cout << "zbbm_bm_test" << '\n';

    zbbm::book book{};
    book.isbn = "4673121";
    book.author = "AuthorDefault";
    book.co_authors = {};
    book.language = "ptbr";
    book.launch_date = {};
    book.publisher = {};
    book.name = "C++ Prime";

    zbbm::book book2 = book;
    book2.isbn = "4673122";
    book2.name = "C++ With Gems";

    zbbm::book_manager bm{ "BookDatabase.zbbm" };
    bm.add(book);
    bm.add(book2);
    
    if (!bm.save())
        std::cerr << "Failed to save database" << '\n';

    print_books(bm);
    bm.remove(book2.isbn);

    print_books(bm);
    bm.remove(book.isbn);

    zbbm::book book3 = book2;
    bm.add(book3);

    auto book_opt = bm.find("4673122");
    if (book_opt.has_value())
        std::cout << book_opt.value().name << '\n';
}
