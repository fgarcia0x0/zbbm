#include <iostream>
#include <filesystem>
#include <book_manager.h>
#include <gtest/gtest.h>
#include <vector>

static void edit_book(zbbm::book& book)
{
    book.author   = "AuthorTest2";
    book.name     = "BookName2";
    book.language = "en-us";
}

TEST(BookManagerTest, AddTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};

    book.author         = "AuthorTest";
    book.co_authors     = { "CoAuthor1", "CoAuthor2" };
    book.isbn           = "994957872341";
    book.language       = "pt-br";
    book.launch_date    = "20/11/2022";
    book.name           = "BookName";
    book.publisher      = "PublisherName";
    
    book_manager.add(book);

    auto result = book_manager.find("994957872341");
    EXPECT_TRUE(result != std::nullopt);
    EXPECT_EQ(result.value(), book);
};

TEST(BookManagerTest, EditTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };

    zbbm::book mem_book{};
    mem_book.isbn = "987";
    mem_book.author = "Test";
    book_manager.add(mem_book);

    book_manager.edit("987", edit_book);
    auto result = book_manager.find("987");

    EXPECT_TRUE(result.has_value());
    EXPECT_TRUE(result.value().author == "AuthorTest2");
};

TEST(BookManagerTest, RemoveTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    std::string target_isbn = "994957872341";

    std::optional<zbbm::book> book = book_manager.find(target_isbn);

    if (book.has_value())
    {
        book_manager.remove(target_isbn);
    }

    bool result = false;

    if (book.has_value())
    {
        book_manager.remove(target_isbn);
    }

    book = book_manager.find(target_isbn);

    if(!book.has_value())
    {
        result = true;
    }

    EXPECT_TRUE(result == true);
};

TEST(BookManagerTest, ListTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTestList.zbbm" };
    constexpr const uint8_t n_books {10u};
    std::vector<zbbm::book> books(n_books);

    for(uint8_t idx{}; idx < n_books; ++idx)
    {
        books[idx].author         = std::string("AuthorTest");
        books[idx].co_authors     = { "CoAuthor1", "CoAuthor2" };
        books[idx].isbn           = std::string("451400") + std::to_string(idx);
        books[idx].language       = "ptbr";
        books[idx].launch_date    = "20/11/2022";
        books[idx].name           = "BookName";
        books[idx].publisher      = "PublisherName";
    }
    
    for(const auto& book : books)
        book_manager.add(book);


    for (uint8_t idx {}; idx < books.size(); ++idx)
    {
        auto result = book_manager.find(books[idx].isbn);
        EXPECT_TRUE(result != std::nullopt);
        EXPECT_EQ(result.value(), books[idx]);
    }
};

TEST(BookManagerTest, UpdateTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};
    
    bool result = false;
    
    book.author = "AuthorTest3";
    book.co_authors = { "CoAuthor1", "CoAuthor2" };
    book.isbn = "110987654321";
    book.language = "en-us";
    book.launch_date = "3/11/2022";
    book.name = "BookName3";
    book.publisher = "PublisherName3";

    book_manager.add(book);

    book_manager.save();

    book_manager.clear();

    book_manager.update();

    std::optional<zbbm::book> verify_book = book_manager.find("110987654321");

    if(verify_book.has_value())
        result = true;

    EXPECT_TRUE(result == true);
};

TEST(BookManagerTest, FindIterTest)
{
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, ClearTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    bool result = false;

    book_manager.clear();

    if(book_manager.books().empty())
        result = true;

    EXPECT_TRUE(result == true);
};

TEST(BookManagerTest, SaveTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};
    bool result = false;
    
    book.author = "AuthorTest2";
    book.co_authors = { "CoAuthor1", "CoAuthor2" };
    book.isbn = "110987654321";
    book.language = "pt-br";
    book.launch_date = "2/11/2022";
    book.name = "BookName2";
    book.publisher = "PublisherName2";
    
    book_manager.add(book);

    book_manager.save();

    book_manager.clear();

    book_manager.update();

    std::optional<zbbm::book> verify_book = book_manager.find("110987654321");

    if(verify_book.has_value())
        result = true;

    EXPECT_TRUE(result == true);
};

TEST(BookManagerTest, SaveInPathTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};
    bool result = false;
    
    book.author = "AuthorTest4";
    book.co_authors = { "CoAuthor1", "CoAuthor2" };
    book.isbn = "110987654543";
    book.language = "pt-br";
    book.launch_date = "2/11/2022";
    book.name = "BookName2";
    book.publisher = "PublisherName2";
    
    book_manager.add(book);

    book_manager.save( "NewBookDatabase.zbbm" );

    zbbm::book_manager new_book_manager{ "NewBookDatabase.zbbm" };

    std::optional<zbbm::book> verify_book = new_book_manager.find("110987654543");

    if(verify_book.has_value())
        result = true;

    EXPECT_TRUE(result == true);
};

TEST(BookManagerTest, FindTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTestfind.zbbm" };
    zbbm::book book_test_1{};
    zbbm::book book_test_2{};
    
    book_test_1.author      = "AuthorTest1";
    book_test_1.co_authors  = { "CoAuthor1", "CoAuthor2" };
    book_test_1.isbn        = "994957872341";
    book_test_1.language    = "ptbr";
    book_test_1.launch_date = "20/11/2022";
    book_test_1.name        = "BookTest1Name";
    book_test_1.publisher   = "PublisherName";

    book_test_2.author      = "AuthorTest2";
    book_test_2.co_authors  = { "CoAuthor1", "CoAuthor2" };
    book_test_2.isbn        = "99486775425";
    book_test_2.language    = "En";
    book_test_2.launch_date = "23/11/2002";
    book_test_2.name        = "BookTest2Name";
    book_test_2.publisher   = "PublisherName2";
    
    book_manager.add(book_test_1);
    book_manager.add(book_test_2);

    auto result = book_manager.find("994957872341");
    EXPECT_TRUE(result != std::nullopt);
    EXPECT_FALSE(result.value().isbn == book_test_2.isbn);

    result = book_manager.find(book_test_2.isbn);
    EXPECT_TRUE(result != std::nullopt);
    EXPECT_EQ(result.value(), book_test_2);
};