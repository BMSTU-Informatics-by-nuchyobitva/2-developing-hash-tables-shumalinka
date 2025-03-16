# Лабораторная работа 2
30 вариант - 2 - **Открытая адресация: квадратичное пробирование**
# Отчет
Реализована хэш-таблица с использованием открытой адресации и квадратичного пробирования на основе класса film, создан класс HashTable, который включает в себя методы для вставки, поиска, удаления и вывода элементов. 


1. **Класс film**: Содержит два поля — numintop (номер фильма в топе) и name (название фильма).

```
class film {   // Определение класса film
public:
    int numintop;
    std::string name;
    // Конструктор класса film, инициализирующий поля numintop и name
    film(int num, const std::string& n) : numintop(num), name(n) {}
};
```

2. **Класс HashTable**:

```
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
```
 Поля:

- struct HashNode: Вложенная структура для хранения данных о фильме и флага удаления.

- film* data: Указатель на объект film.

- bool isDeleted: Флаг, указывающий, был ли узел удален.

- std::vector<HashNode> table: Вектор для хранения узлов хэш-таблицы.

- int capacity: Вместимость хэш-таблицы.

- int size: Текущий размер хэш-таблицы.

3. **Метод insert**: Вставляет новый элемент в таблицу, используя квадратичное пробирование для обработки коллизий.
   
```
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
```

5. **Метод search**: Ищет элемент по ключу.
   
```
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
```

7. **Метод remove**: Удаляет элемент из таблицы, устанавливая флаг isDeleted.

```
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
```

8. **Метод display**: Выводит содержимое хэш-таблицы.

```
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
```

9. В функции **main()** создается объект хэш-таблицы, в нее добавляются несколько фильмов, выполняется поиск одного из них и демонстрируется удаление. После каждой операции содержимое таблицы выводится на экран.

```
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
```

**скрин из симулятора**
</br>![симулятор](image.png)
