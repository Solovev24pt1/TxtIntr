# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = calculator
SOURCE = calculator.cpp

# Цель по умолчанию
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Очистка
clean:
	rm -f $(TARGET) *.o

# Установка
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Помощь
help:
	@echo "Доступные цели:"
	@echo "  all     - сборка программы (по умолчанию)"
	@echo "  clean   - удаление скомпилированных файлов"
	@echo "  install - установка программы"
	@echo "  help    - эта справка"

.PHONY: all clean install help
