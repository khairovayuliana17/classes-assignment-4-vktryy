

#include "diary.h"

// your code here

// Конструктор
Diary::Diary(const std::string& initialPassword) :
    password(initialPassword), content(""), isOpen(false) {}

// Деструктор
Diary::~Diary() {
    if (isOpen) {
        content.clear();
        std::cout << "Дневник уничтожен, данные очищены" << std::endl;
    }
}

// Проверка пароля и открытие дневника
bool Diary::unlock(const std::string& inputPassword) {
    if (inputPassword == password) {
        isOpen = true;
        return true;
    } else {
        std::cout << "Неверный пароль" << std::endl;
        return false;
    }
}

// Добавление записей
void Diary::write(const std::string& text) {
    if (isOpen) {
        content += text;
    } else {
        std::cout << "Ошибка: дневник закрыт!" << std::endl;
    }
}

// Закрытие дневника
void Diary::lock() { isOpen = false; }

// Чтение
std::string Diary::read() {
    if (isOpen) {
        return content;
    } else {
        std::cout << "Ошибка: дневник закрыт!" << std::endl;
        return "";
    }
}
