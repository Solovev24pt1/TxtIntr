#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

// Функция для вывода справки
void printHelp() {
    std::cout << "=================================================\n";
    std::cout << "       СТАТИСТИЧЕСКИЙ КАЛЬКУЛЯТОР (Вариант 20)\n";
    std::cout << "=================================================\n\n";
    std::cout << "НАЗНАЧЕНИЕ:\n";
    std::cout << "  Выполнение статистических операций над числами\n\n";
    std::cout << "СИНТАКСИС:\n";
    std::cout << "  calculator --operation <ОПЕРАЦИЯ> <ЧИСЛО1> <ЧИСЛО2> ... <ЧИСЛО8-10>\n";
    std::cout << "  calculator -o <ОПЕРАЦИЯ> <ЧИСЛО1> <ЧИСЛО2> ... <ЧИСЛО8-10>\n\n";
    std::cout << "ПАРАМЕТРЫ:\n";
    std::cout << "  -o, --operation  Задает операцию для выполнения\n";
    std::cout << "                   Допустимые значения: mean, median\n\n";
    std::cout << "  <ЧИСЛО1>...      Числовые операнды (от 8 до 10 чисел)\n\n";
    std::cout << "ПОДДЕРЖИВАЕМЫЕ ОПЕРАЦИИ:\n";
    std::cout << "  mean   - вычисление среднего арифметического\n";
    std::cout << "  median - вычисление медианы\n\n";
    std::cout << "ТРЕБОВАНИЯ К ОПЕРАНДАМ:\n";
    std::cout << "  • Количество чисел: от 8 до 10\n";
    std::cout << "  • Формат чисел: целые или дробные (через точку)\n\n";
    std::cout << "ПРИМЕРЫ ИСПОЛЬЗОВАНИЯ:\n";
    std::cout << "  calculator -o mean 1 2 3 4 5 6 7 8\n";
    std::cout << "  calculator --operation median 1.5 2.3 3.7 4.1 5.9 6.2 7.8 8.4 9.6\n";
    std::cout << "  calculator -o mean 10 20 30 40 50 60 70 80 90 100\n\n";
    std::cout << "ВЕРСИЯ: 1.0\n";
    std::cout << "ВАРИАНТ: 20 (статистический калькулятор)\n";
    std::cout << "=================================================\n";
}

// Функция для вычисления среднего арифметического
double calculateMean(const std::vector<double>& numbers) {
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    return sum / numbers.size();
}

// Функция для вычисления медианы
double calculateMedian(std::vector<double> numbers) {
    std::sort(numbers.begin(), numbers.end());
    size_t size = numbers.size();
    
    if (size % 2 == 0) {
        // Четное количество элементов
        return (numbers[size/2 - 1] + numbers[size/2]) / 2.0;
    } else {
        // Нечетное количество элементов
        return numbers[size/2];
    }
}

// Функция для проверки количества операндов
bool isValidOperandCount(size_t count) {
    return count >= 8 && count <= 10;
}

// Функция для преобразования строки в число
bool parseDouble(const std::string& str, double& result) {
    try {
        result = std::stod(str);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

int main(int argc, char* argv[]) {
    // Если нет параметров, выводим справку и выходим
    if (argc == 1) {
        printHelp();
        return 0;
    }

    // Также выводим справку если первым параметром идет --help или -h
    std::string firstArg = argv[1];
    if (firstArg == "--help" || firstArg == "-h" || firstArg == "/?") {
        printHelp();
        return 0;
    }

    std::string operation;
    std::vector<double> operands;
    bool operationSpecified = false;

    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
                operationSpecified = true;
            } else {
                std::cerr << "ОШИБКА: отсутствует значение для параметра " << arg << std::endl;
                std::cerr << "Используйте 'calculator --help' для получения справки\n";
                return 1;
            }
        } else if (arg == "--help" || arg == "-h") {
            printHelp();
            return 0;
        } else {
            // Позиционный параметр (операнд)
            double operand;
            if (parseDouble(arg, operand)) {
                operands.push_back(operand);
            } else {
                std::cerr << "ОШИБКА: неверный формат числа: " << arg << std::endl;
                std::cerr << "Используйте 'calculator --help' для получения справки\n";
                return 1;
            }
        }
    }

    // Проверка операции
    if (!operationSpecified) {
        std::cerr << "ОШИБКА: не указана операция\n";
        std::cerr << "Используйте 'calculator --help' для получения справки\n";
        return 1;
    }

    // Проверка количества операндов
    if (!isValidOperandCount(operands.size())) {
        std::cerr << "ОШИБКА: неверное количество чисел\n";
        std::cerr << "Требуется: от 8 до 10 чисел\n";
        std::cerr << "Получено: " << operands.size() << " чисел\n";
        std::cerr << "Используйте 'calculator --help' для получения справки\n";
        return 1;
    }

    // Выполнение операции
    double result;
    if (operation == "mean") {
        result = calculateMean(operands);
        std::cout << "Среднее арифметическое: " << std::fixed << std::setprecision(4) << result << std::endl;
    } else if (operation == "median") {
        result = calculateMedian(operands);
        std::cout << "Медиана: " << std::fixed << std::setprecision(4) << result << std::endl;
    } else {
        std::cerr << "ОШИБКА: неизвестная операция: " << operation << std::endl;
        std::cerr << "Допустимые операции: mean, median\n";
        std::cerr << "Используйте 'calculator --help' для получения справки\n";
        return 1;
    }

    return 0;
}
