#include <iostream>
#include <filesystem>
#include <book_manager.h>
#include <gtest/gtest.h>

static void edit_book(zbbm::book& book)
{
    book.author   = "Zeca Pagodes";
    book.isbn     = "123456789101";
    book.language = "en-us";
}

TEST(BookManagerTest, AddTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};
    
    book.author = "AuthorTest";
    book.co_authors = { "CoAuthor1", "CoAuthor2" };
    book.isbn = "994957872341";
    book.language = "pt-br";
    book.launch_date = "20/11/2022";
    book.name = "BookName";
    book.publisher = "PublisherName";
    
    book_manager.add(book);

    auto result = book_manager.find("994957872341");
    EXPECT_TRUE(result != std::nullopt);
    EXPECT_EQ(result.value(), book);
};

TEST(BookManagerTest, EditTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book mem_book;

    std::string target_isbn = "994957872341";

    auto result = book_manager.find(target_isbn);
    mem_book = result.value();

    if(result.has_value())
        book_manager.edit("994957872341", edit_book);

    EXPECT_TRUE(result != std::nullopt);
    EXPECT_TRUE(result.value() != mem_book);
};

TEST(BookManagerTest, RemoveTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    std::optional<zbbm::book> book;
    std::string target_isbn = "994957872341";

    book = book_manager.find(target_isbn);

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
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, FindTest)
{
    //EXPECT_EQ(1000, cubic(10));
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

};

TEST(BookManagerTest, SaveInPathTest)
{

};

TEST(BookManagerTest, UpdateTest)
{
    
};