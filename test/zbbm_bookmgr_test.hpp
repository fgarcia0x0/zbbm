#pragma once

#include <iostream>
#include <filesystem>
#include <book_manager.h>
#include <gtest/gtest.h>

TEST(BookManagerTest, AddTest)
{
    zbbm::book_manager book_manager{ "BookDatabaseTest.zbbm" };
    zbbm::book book{};
    
    book.author = "AuthorTest";
    book.co_authors = { "CoAuthor1", "CoAuthor2" };
    book.isbn = "994957872341";
    book.language = "ptbr";
    book.launch_date = "20/11/2022";
    book.name = "BookName";
    book.publisher = "PublisherName";
    
    book_manager.add(book);

    auto result = book_manager.find("994957872341");

    EXPECT_TRUE(result != std::nullopt);
    
    EXPECT_EQ(result.value(), book);
    EXPECT_EQ(result.value().author, "AuthorTest");
    EXPECT_EQ(result.value().co_authors[0], "CoAuthor1");
    EXPECT_EQ(result.value().co_authors[1], "CoAuthor2");
    EXPECT_EQ(result.value().language, "ptbr");
    EXPECT_EQ(result.value().launch_date, "20/11/2022");
    EXPECT_EQ(result.value().name, "BookName");
    EXPECT_EQ(result.value().publisher, "PublisherName");
};

TEST(BookManagerTest, EditTest)
{
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, RemoveTest)
{
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, ListTest)
{
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, FindTest)
{
    //EXPECT_EQ(1000, cubic(10));
};

TEST(BookManagerTest, FindTest)
{
    //EXPECT_EQ(1000, cubic(10));
};