#include <iostream>
#include <string>
#include <vector>

class film {   // Определение класса film
public:
    int numintop;
    std::string name;
    // Конструктор класса film, инициализирующий поля numintop и name
    film(int num, const std::string& n) : numintop(num), name(n) {}
};

class HashTable {
private:    // Вложенная структура HashNode для хранения данных в хэш-таблице
    struct HashNode {
        film* data;
        bool isDeleted;
        HashNode() : data(nullptr), isDeleted(false) {}
    };

    std::vector<HashNode> table;
    int capacity;
    int size;

    //хэш-функция для целых чисел
    int hashFunction(int key) {
        return key % capacity;
    }
    //хэш-функция для строк
    int hashFunction(const std::string& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % capacity;
    }

public:  
    HashTable(int cap) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    ~HashTable() { // Деструктор класса HashTable, освобождающий память под объекты film
        for (auto& node : table) {
            delete node.data;
        }
    }
    // Метод для вставки нового объекта film в хэш-таблицу
    void insert(film* f) {
        if (size >= capacity / 2) {
            std::cout << "HashTable is full!" << std::endl;
            return;
        }

        int index = hashFunction(f->numintop);
        int i = 0;

        while (table[index].data != nullptr && !table[index].isDeleted) {
            index = (index + i * i) % capacity; // Квадратичное пробирование
            i++;
        }

        table[index].data = f;
        table[index].isDeleted = false;
        size++;
    }
    // Метод для поиска объекта film по ключу
    film* search(int key) {
        int index = hashFunction(key);
        int i = 0;

        while (table[index].data != nullptr) {
            if (!table[index].isDeleted && table[index].data->numintop == key) {
                return table[index].data;
            }
            index = (index + i * i) % capacity; // Квадратичное пробирование
            i++;
        }
        return nullptr; // Элемент не найден
    }

    // Метод для удаления объекта film по ключу

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        // Цикл для поиска объекта film в таблице и его удаления
        while (table[index].data != nullptr) {
            if (!table[index].isDeleted && table[index].data->numintop == key) {
                table[index].isDeleted = true;
                size--;
                return;
            }
            index = (index + i * i) % capacity; // Квадратичное пробирование
            i++;
        }
    }
    // Метод для отображения содержимого хэш-таблицы
    void display() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].data != nullptr && !table[i].isDeleted) {
                std::cout << "Index " << i << ": " << table[i].data->numintop << ", " << table[i].data->name << std::endl;
            }
            else {
                std::cout << "Index " << i << ": [empty]" << std::endl;
            }
        }
    }
};

int main() {
    HashTable ht(10);

    ht.insert(new film(1, "Film A"));
    ht.insert(new film(2, "Film B"));
    ht.insert(new film(3, "Film C"));

    ht.display();

    film* f = ht.search(2);
    if (f) {
        std::cout << "Found: " << f->name << std::endl;
    }
    else {
        std::cout << "Not found." << std::endl;
    }

    ht.remove(2);
    ht.display();

    return 0;
}
