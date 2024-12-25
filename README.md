# Tape Device Sorter

## About code

Данный проект эмулирует работу устройства хранения данных типа лента (Tape) посредством обычного файла и реализует алгоритм сортировки данных с входной ленты на выходную.

Устройства типа лента для своей работы используют бинарный файл(.bin). Но для удобства оценивания работы кода и простоты создания входных данных, была сделана обвязка ```FileUtils```, благодаря которой программа принимает на вход файлы формата .txt, конвертирует его в bin и ведёт дальнейшую работу с бинарным файлом. А в деструкторе ```TapeDevice``` происходит обратная конвертация bin файла в текстовый файл. Директория для txt файлов - ```data_txt/```, для bin файлов - ```data/```.

Для сортировки используется алгоритм внешней сортировки по причине ограниченной оперативной памяти (кол-во ОП < кол-во значений для сортировки). По умолчанию значение лимита памяти задано в ```main.cpp``` как ```size_t memorySize = 64```. Значение определяет с каким максимальны количеством элементов (типа int) одновременно может работать алгоритм сортировки.

Алгоритм внешней сортировки подразумевает использование дополнительных устройств хранения данных для записи промежуточных результатов сортировки. Поэтому данный проект в ходе своей работы создаёт, а затем сам полностью удаляет, временные устройства типа лента ```TempTapeDevice```. Директория для файлов временных устройств - ```tmp/```. 

Имеется возможность сконфигурировать задержки выполнения операций устройства типа лента (по записи/чтению элемента с ленты, перемотки ленты, и сдвига ленты на одну позицию) через файл ```config/delay.cfg``` .

Задержки в программе моделируются, т.к использование ```this_thread::sleep_for()``` фактически создаёт горазо большую задержку, чем ожидается. Учётом времени выполнения программы занимается объект класса ```TimeManager```, который использует в том числе ```std::future``` когда это необходимо для правильного учёта времени при параллельных процессах(например возврат значений сразу от нескольких устройств одновременно)

После конца выполнения программы в консоль выводится два значения: реальное время выполнения сортировки, а также смоделированное время. Есть возможность включить задержки через ```this_thread::sleep_for()```. Для этого необходимо в ```main.cpp``` объекту класса ```TimeManager``` в конструктор передать значение true ```TimeManager timeManager(true);```.

## Getting started
### 1. Configure
```
cmake -S . -B build
```

### 2. Build 
```
cmake --build build
```

### 3. Run
При запуске приложения указываются имена файлов без указания расширения - только имя! Файлы формата .txt берутся из директории data_txt/
```
./build/TapeSort <inputFilename> <outputFilename>
```

Пример запуска:
```
./build/TapeSort tape3 tape4
```

### 4. Tests
```
./build/TapeSorterTests
```

```
./build/TapeDeviceTests
```