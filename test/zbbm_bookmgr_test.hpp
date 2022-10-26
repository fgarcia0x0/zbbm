#pragma once

#include <iostream>
#include <filesystem>
#include <book_manager.h>

static void print_books(const zbbm::book_manager& bm);
static void bookmgr_add_test(const fs::path& filepath, const zbbm::book& book);

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
    book.co_authors = { "Bryan", "Gerliandro" };

    zbbm::book book2 = book;
    book2.isbn = "4673127";
    book2.name = "Large-Scale C++";

    zbbm::book_manager bm{ "BookDatabase.zbbm" };
    bm.clear();
    bm.save();

    bookmgr_add_test("BookDatabase.zbbm", book);
    //bookmgr_add_test("BookDatabase.zbbm", book2);

    bm.update();
    print_books(bm);
}

static void print_books(const zbbm::book_manager& bm)
{
    for (const auto& book : bm.books())
    {
        std::cout << book.name << '\n';
    }
}

static void bookmgr_add_test(const fs::path& filepath, const zbbm::book& book)
{
    zbbm::book_manager bm{ filepath };
    bm.add(book);
    
    if (!bm.save())
        std::cerr << "Failed to save database" << '\n';
}
