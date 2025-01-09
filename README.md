# Tables Manager

## About code

Данный проект представляет собой систему учёта времени и выручки компьютерного клуба.

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
```
.\TableManager.exe <fileName>
```

Example:
```
.\TableManager.exe day1.txt
```


## Running Tests


### 1. Build the tests
```
cmake --build . --target tests
```

### 2. Run all tests
```
ctest
```

### 3. Run specific tests
```
ctest -R <testName>
```

Tests:
```
EventManagerTests
```

```
ClientManagerTests
```

```
TableManagerTests
```