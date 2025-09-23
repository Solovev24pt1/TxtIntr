#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class Calculator {
private:
    std::string operation;
    std::vector<double> operands;
    
    void showHelp() {
        std::cout << "Мультипликативный калькулятор (вариант 19)" << std::endl;
        std::cout << "Использование: calculator -o <операция> [операнды...]" << std::endl;
        std::cout << std::endl;
        std::cout << "Поддерживаемые операции:" << std::endl;
        std::cout << "  multiply - умножение (5-7 операндов)" << std::endl;
        std::cout << "  divide   - деление первого операнда на все остальные (5-7 операндов)" << std::endl;
        std::endl;
        std::cout << "Примеры:" << std::endl;
        std::cout << "  calculator -o multiply 2 3 4 5 6" << std::endl;
        std::cout << "  calculator -o divide 100 2 5 2 2" << std::endl;
        std::cout << std::endl;
        std::cout << "Количество операндов: от 5 до 7" << std::endl;
    }
    
    bool isValidOperation(const std::string& op) {
        return op == "multiply" || op == "divide";
    }
    
    bool isValidOperandCount(size_t count) {
        return count >= 5 && count <= 7;
    }
    
    double multiply() {
        double result = 1.0;
        for (double operand : operands) {
            result *= operand;
        }
        return result;
    }
    
    double divide() {
        if (operands.size() < 2) {
            throw std::invalid_argument("Для деления требуется хотя бы 2 операнда");
        }
        
        double result = operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            if (operands[i] == 0) {
                throw std::invalid_argument("Деление на ноль невозможно");
            }
            result /= operands[i];
        }
        return result;
    }
    
public:
    bool parseArguments(int argc, char* argv[]) {
        if (argc == 1) {
            showHelp();
            return false;
        }
        
        // Проверка на запрос справки
        std::string firstArg = argv[1];
        if (firstArg == "-h" || firstArg == "--help") {
            showHelp();
            return false;
        }
        
        // Парсинг аргументов
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            
            if (arg == "-o" || arg == "--operation") {
                if (i + 1 < argc) {
                    operation = argv[++i];
                } else {
                    std::cerr << "Ошибка: после -o должно следовать название операции" << std::endl;
                    return false;
                }
            } else {
                // Парсинг операндов
                try {
                    double operand = std::stod(arg);
                    operands.push_back(operand);
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: неверный формат операнда: " << arg << std::endl;
                    return false;
                }
            }
        }
        
        // Валидация
        if (operation.empty()) {
            std::cerr << "Ошибка: не указана операция" << std::endl;
            return false;
        }
        
        if (!isValidOperation(operation)) {
            std::cerr << "Ошибка: неизвестная операция: " << operation << std::endl;
            return false;
        }
        
        if (!isValidOperandCount(operands.size())) {
            std::cerr << "Ошибка: неверное количество операндов: " << operands.size() << std::endl;
            std::cerr << "Требуется: от 5 до 7 операндов" << std::endl;
            return false;
        }
        
        return true;
    }
    
    void execute() {
        double result;
        
        if (operation == "multiply") {
            result = multiply();
            std::cout << "Результат умножения: ";
        } else if (operation == "divide") {
            result = divide();
            std::cout << "Результат деления: ";
        }
        
        // Вывод выражения
        std::cout << operands[0];
        if (operation == "multiply") {
            for (size_t i = 1; i < operands.size(); ++i) {
                std::cout << " × " << operands[i];
            }
        } else {
            for (size_t i = 1; i < operands.size(); ++i) {
                std::cout << " ÷ " << operands[i];
            }
        }
        std::cout << " = " << std::fixed << std::setprecision(6) << result << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Calculator calc;
    
    if (!calc.parseArguments(argc, argv)) {
        return 1;
    }
    
    try {
        calc.execute();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка выполнения: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
