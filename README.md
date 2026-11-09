# Алгоритмы и структуры данных — CLion

C++17, CMake 3.14+, Google Test 1.14.0, cpplint.
Исходный шаблон преподавателя и настройка подмодуля находятся в `main`.
Библиотека Vector, тесты и настройки CLion находятся в `dev`.
Исходная инструкция преподавателя сохранена в README_TEACHER.md.

## Скачать проект

Клонируйте репозиторий и переключитесь на ветку с библиотекой Vector:

```bash
git clone https://github.com/chardi60666/Algorithms-and-Data-Structures.git ADS
cd ADS
git switch dev
git submodule sync
git submodule update --init --recursive
```

Используйте `git clone`: ZIP с GitHub не содержит исходники подмодулей.
Google Test закреплён на версии 1.14.0, совместимой и с C++14 исходного шаблона.
В `third_party/gtest` после загрузки должен находиться `CMakeLists.txt`.

## Открыть в CLion на Windows

1. Установите Git, если команда `git --version` не работает.
2. Сохраните проект, например, в `C:\Users\ВАШЕ_ИМЯ\source\github\ADS`.
3. В CLion выберите **File → Open** и папку с корневым `CMakeLists.txt`.
4. В **Settings → Build, Execution, Deployment → Toolchains** выберите
   доступный MinGW (в современных версиях CLion доступен встроенный).
   Убедитесь, что C и C++ compiler, CMake и Ninja обнаружены.
5. В разделе **CMake** выберите этот toolchain, генератор Ninja,
   добавьте CMake option `-DBTEST=ON`, примените настройки.
6. Выполните **Tools → CMake → Reload CMake Project**, затем
   **Build → Build Project**.
7. В списке конфигураций запуска выберите `Application` и нажмите Run.
   Приложение выводит пример деления, ожидаемое сообщение о делении на ноль
   и `Vector: 10 20 30 40`.
8. Выберите `AllTests` и нажмите Run: должны пройти все 19 тестов.

Файл `.sln` для CLion не нужен. Новые библиотеки подключайте через CMakeLists,
как `lib_vector`, а не через создание проекта Visual Studio.

## Сборка из терминала

При доступных в PATH CMake, Ninja и компиляторе:

```bash
cmake -S . -B build -G Ninja -DBTEST=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

В Windows приложение: `build\main\Application.exe`.
В Linux/macOS: `./build/main/Application`.
В Windows также доступен `scripts/build_clion.bat`.
Если терминал не находит Ninja/CMake, используйте сборку через меню CLion:
она использует пути из настроек IDE. У CLion каталог сборки обычно
`cmake-build-debug`, а у команд выше — `build`; это разные сборки.
При смене генератора создайте новый каталог сборки.

## Структура

- `lib_easy_example`: статическая библиотека EasyExample из шаблона.
- `lib_vector`: статическая библиотека Vector; шаблонные классы находятся
  в заголовках, `tvector.cpp` создаёт единицу компиляции библиотеки.
- `TMemData`: владеет массивом, поддерживает глубокое копирование и перемещение.
- `TVector`: размер, ёмкость, доступ, добавление/удаление с конца,
  reserve, shrink_to_fit, clear, копирование и перемещение.
- `TVector<T>::Iterator` и `ConstIterator`: вложенные итераторы произвольного
  доступа; работают range-for и std::sort.
- `tests`: AllTests, 19 тестов библиотеки Vector, памяти и EasyExample.

Это учебная реализация: память выделяется через `new T[n]`, поэтому элементы
должны допускать создание по умолчанию и копирующее присваивание.
`clear` и `pop_back` меняют логический размер; объекты в выделенном массиве
живут до освобождения или перераспределения памяти. Это отличается от
управления временем жизни элементов в std::vector.

## Проверки стиля и GitHub Actions

```bash
python -m pip install cpplint==2.0.2
cpplint --recursive lib_easy_example lib_vector main tests
```

Workflow проверяет стиль, собирает проект и запускает тесты на Linux и Windows.
Внешний код Google Test и каталоги сборки в cpplint не включаются.
Результат удалённых проверок смотрите во вкладке Actions после push.

## Дальнейшая работа

```bash
git switch dev
git add .
git commit -m "описание изменений"
git push -u origin dev
```

Не коммитьте `.idea`, `build` и `cmake-build-*`.
