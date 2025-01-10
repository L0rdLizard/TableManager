# Tables Manager

## About code

Тестовое задание в Yadro Telecom.
Данный проект представляет собой систему учёта времени и выручки компьютерного клуба.

Условие задачи: https://github.com/L0rdLizard/TableManager/tree/main/docs

Лог программы всегда пишется в консоль, а также при успешном выполнении программы записывается в директорию output в качестве txt файла с припиской "_report", как отчёт за день.

## Getting started
### 1. Clone the repository
```
git clone https://github.com/L0rdLizard/TableManager.git
cd TableManager
```

### 2. Create a build directory
```
mkdir build
cd build
```

### 3. Configure
```
cmake ..
```

### 4. Build 
```
cmake --build .
```

### 5. Run
Файлы берутся исключительно из директории input в формате txt.

```
.\TableManager.exe <fileName>
```

Example:
```
.\TableManager.exe day1.txt
```


## Running Tests

### 1. Run all tests
```
ctest
```

### 2. Run with additional info
```
ctest --verbose
```

### 3. Run specific tests
```
ctest -R <testName>
```

Tests:
```
EventManagerTest
```

```
ClientManagerTest
```

```
TableManagerTest
```
