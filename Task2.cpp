#include <iostream> // консоль - cout
#include <thread>   // задержка - this_thread, chrono
#include <conio.h>  // _kbhit()

enum class Operand {NOT, PLUS, MINUS, ANSWER, EXIT};

class Counter
{
private:
    int count;

public:
    Counter()
    {
        setCount(1);
    }
    Counter(int num)
    {
        setCount(num);
    }
    void increase() { ++count; }
    void decrease() { --count; }
    void setCount(int num) { count = num; }
    int getCount() { return count; }
};

bool yesOrNo(); // 1 - да; 0 - нет
Operand oper();
int userInput(const std::string); // будет запрашивать у пользователя ввод данных

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");   // задаём русский текст
    system("chcp 1251");            // настраиваем кодировку консоли
    std::system("cls");

    std::cout << "Задача 2. Счётчик\n";
    std::cout << "-----------------\n";
    
    Counter counter;
    
    if (yesOrNo())
    {
        counter.setCount(userInput("Введите начальное значение счётчика: "));
    }
    
    bool contin = true;
    do
    {
        switch (oper())
        {
        case Operand::PLUS:
            counter.increase();
            std::cout << "+";
            break;

        case Operand::MINUS:
            counter.decrease();
            std::cout << "-";
            break;

        case Operand::ANSWER:
            std::cout << "= " <<  counter.getCount();
            break;

        case Operand::EXIT:
            contin = false;
            std::cout << "До свидания!";
            break;

        default:
            break;
        }
        std::cout << std::endl;
    } while (contin);

    return 0;
}

// ждет нажатия клавиши, после чего
// возвращает "true" если нажато - "ENTER, y, Y, д, Д"
// и "false" если - "ESC, n, N, н, Н"
bool yesOrNo()
{
    using namespace std;

    bool answer_no, answer_yes;
    bool pressKey = false; // если "true", то нажали что то нужное
    cout << "Вы хотите указать начальное значение счётчика?\n";
    do
    {
        if (_kbhit())  // если клавиша была нажата
        {
            int input = _getch(); // смотрим, что нажато
            //cout << input << " ";
            answer_no = input == 27 || input == 110 || input == 78 ||
                input == 237 || input == 205; // ESC, n, N, н, Н
            answer_yes = input == 13 || input == 121 || input == 89 ||
                input == 228 || input == 196; // ENTER, y, Y, д, Д
            pressKey = answer_no || answer_yes;
            if (!pressKey) cout << "Да или нет?\n";
        }
    } while (!pressKey);

    return answer_yes;
}

// ждет ввода комманды, возвращает введенную комманду
Operand oper()
{
    using namespace std;

    Operand op = Operand::NOT;
    cout << "Введите команду ('+', '-', '=' или 'x'): ";
    do
    {
        if (_kbhit())  // если клавиша была нажата
        {
            switch (_getch())
            {
            case 43:    // +
                op = Operand::PLUS;
                break;

            case 45:    // -
                op = Operand::MINUS;
                break;

            case 13:    // Enter
            case 61:    // =
                op = Operand::ANSWER;
                break;

            case 27:    // ESC
            case 88:    // X
            case 120:   // x
            case 215:   // Ч
            case 247:   // ч
                op = Operand::EXIT;
                break;

            default:
                op = Operand::NOT;
                break;
            }
        }
    } while (op == Operand::NOT);

    return op;
}

// будет запрашивать у пользователя ввод данных
// пока не будут введены верные данные.
// В случае успеха, вернет int.
// При ошибке ввода, сбросит и очистит cin
// и снова попросит ввести данные
int userInput(const std::string userText)
{
    double uData = 0;
    bool err = true;

    do
    {
        std::cout << userText; std::cin >> uData;

        if (err = std::cin.fail()) std::cin.clear(); // ошибка ввода
        int ch; // поиск и очистка лишних введенных символов
        while ((ch = std::cin.get()) != '\n' && ch != EOF);
    } while (err);

    return uData;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
