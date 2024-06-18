#include <iostream>
#include <windows.h>
#include <string>

typedef bool (*CheckCharactersFunc)(const char*, const char*);

int main() {
    // Ввод строки и символов
    std::string inputString, characters;
    std::cout << "Enter a string: ";
    std::getline(std::cin, inputString);
    std::cout << "Enter characters to find: ";
    std::getline(std::cin, characters);

    // Загрузка библиотеки
    HMODULE hLib = LoadLibrary(TEXT("StringCheckDLL.dll"));
    if (!hLib) {
        std::cerr << "Could not load the DLL." << std::endl;
        return 1;
    }

    // Получение адреса функции
    CheckCharactersFunc checkCharacters = (CheckCharactersFunc)GetProcAddress(hLib, "CheckCharacters");
    if (!checkCharacters) {
        std::cerr << "Could not find the function in the DLL." << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Вызов функции
    bool result = checkCharacters(inputString.c_str(), characters.c_str());
    std::cout << "All characters found: " << (result ? "True" : "False") << std::endl;

    // Освобождение библиотеки
    FreeLibrary(hLib);

    return 0;
}
