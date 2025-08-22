#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

// Функция для чтения слов из файла
vector<string> loadWords(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return words;
    }

    string word;
    while (file >> word) {
        // Убираем лишние символы и приводим к нижнему регистру
        word.erase(remove_if(word.begin(), word.end(), [](char c) {
            return !isalpha(c);
            }), word.end());

        if (!word.empty()) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

// Функция отображения виселицы
void displayHangman(int wrongGuesses) {
    cout << "\n";
    switch (wrongGuesses) {
    case 0:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 1:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 2:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << "  |   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 3:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 4:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 5:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << " /    |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    case 6:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << " / \\  |\n";
        cout << "      |\n";
        cout << "=========\n";
        break;
    }
}

// Отображение слова
void displayWord(const vector<char>& guessedWord) {
    cout << "Слово: ";
    for (char c : guessedWord) {
        cout << c << " ";
    }
    cout << "\n\n";
}

int main() {
    setlocale(LC_ALL, "Russian"); // Поддержка кириллицы
    system("title Hangman");     // Устанавливаем заголовок окна консоли

    const string filename = "words.txt";
    vector<string> words = loadWords(filename);

    if (words.empty()) {
        cout << "Не удалось загрузить слова. Проверьте файл " << filename << endl;
        return 1;
    }

    char playAgain = 'д';

    do {
        system("cls"); // Очищаем экран перед новой игрой

        srand(static_cast<unsigned int>(time(0)));
        string secretWord = words[rand() % words.size()];
        vector<char> guessedWord(secretWord.length(), '_');
        vector<bool> used(26, false);
        int wrongGuesses = 0;
        const int maxWrong = 6;

        cout << "Добро пожаловать в игру 'Виселица'!\n";
        cout << "Угадайте слово по буквам. У вас есть " << maxWrong << " попыток.\n\n";

        while (wrongGuesses < maxWrong && find(guessedWord.begin(), guessedWord.end(), '_') != guessedWord.end()) {
            displayHangman(wrongGuesses);
            displayWord(guessedWord);

            cout << "Введите букву: ";
            char input;
            cin >> input;

            input = tolower(input);

            if (!isalpha(input)) {
                cout << "Пожалуйста, введите букву.\n\n";
                continue;
            }

            if (used[input - 'a']) {
                cout << "Вы уже вводили эту букву.\a\n\n";
                continue;
            }

            used[input - 'a'] = true;

            bool found = false;
            for (int i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == input) {
                    guessedWord[i] = input;
                    found = true;
                }
            }

            if (!found) {
                cout << "Нет такой буквы!\n";
                wrongGuesses++;
            }
            else {
                cout << "Есть такая буква!\n";
            }

            cout << "\n";
        }

        // Конец игры
        displayHangman(wrongGuesses);
        if (wrongGuesses >= maxWrong) {
            cout << "Вы проиграли! Загаданное слово было: " << secretWord << endl;
        }
        else {
            cout << "Поздравляем! Вы угадали слово: " << secretWord << endl;
        }

        cout << "\nХотите сыграть ещё раз? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'д' || playAgain == 'Д' || playAgain == 'y' || playAgain == 'Y');

    cout << "Спасибо за игру! До встречи!\n";
    system("pause");
    return 0;
}