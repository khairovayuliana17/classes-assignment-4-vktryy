#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "diary.h"
#include <sstream>

TEST_CASE("Конструктор и деструктор", "[Diary]") {
    Diary diary("password123");
    REQUIRE(diary.read() == "");
}

TEST_CASE("Проверка пароля", "[Diary]") {
    Diary diary("secret");

    SECTION("Неправильный пароль") {
        REQUIRE_FALSE(diary.unlock("wrongpass"));
        REQUIRE(diary.read() == "");
    }

    SECTION("Правильный пароль") {
        REQUIRE(diary.unlock("secret"));
        REQUIRE(diary.read() == "");
    }
}

TEST_CASE("Запись и чтение", "[Diary]") {
    Diary diary("12345");

    SECTION("Попытка записи в закрытый дневник") {
        diary.write("Текст 1");
        REQUIRE(diary.read() == "");
    }

    SECTION("Запись и чтение в открытом дневнике") {
        diary.unlock("12345");
        diary.write("Текст 1\n");
        diary.write("Текст 2\n");
        REQUIRE(diary.read() == "Текст 1\nТекст 2\n");
    }
}

TEST_CASE("Закрытие дневника", "[Diary]") {
    Diary diary("qwerty");
    diary.unlock("qwerty");
    diary.write("Секретная запись\n");
    diary.lock();
    REQUIRE(diary.read() == "");
}

TEST_CASE("Очистка данных при уничтожении", "[Diary]") {
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    {
        Diary diary("pass123");
        diary.unlock("pass123");
        diary.write("Важные данные\n");
    }

    std::cout.rdbuf(old_cout);
    REQUIRE(output.str().find("Дневник уничтожен, данные очищены") != std::string::npos);
}

TEST_CASE("Сообщения об ошибках", "[Diary]") {
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    SECTION("Неверный пароль") {
        Diary diary("secret");
        diary.unlock("wrong");
        REQUIRE(output.str().find("Неверный пароль") != std::string::npos);
    }

    SECTION("Попытка записи в закрытый дневник") {
        Diary diary("123");
        diary.write("Текст");
        REQUIRE(output.str().find("Ошибка: дневник закрыт!") != std::string::npos);
    }

    SECTION("Попытка чтения закрытого дневника") {
        Diary diary("123");
        diary.read();
        REQUIRE(output.str().find("Ошибка: дневник закрыт!") != std::string::npos);
    }

    std::cout.rdbuf(old_cout);
}

TEST_CASE("Корректные операции", "[Diary]") {
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    SECTION("Успешное открытие и запись") {
        Diary diary("pass");
        diary.unlock("pass");
        diary.write("Запись");
        REQUIRE(output.str().empty());
    }

    std::cout.rdbuf(old_cout);
}

TEST_CASE("Деструктор выводит сообщение", "[Diary]") {
    std::ostringstream output;
    std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());

    {
        Diary diary("pass");
        diary.unlock("pass");
    }

    REQUIRE(output.str().find("Дневник уничтожен, данные очищены") != std::string::npos);
    std::cout.rdbuf(old_cout);
}
