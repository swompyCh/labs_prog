# Указываем минимальную версию CMake, необходимую для сборки проекта
cmake_minimum_required(VERSION 3.10)

# Устанавливаем версию патча и формируем полную версию проекта
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

# Определяем проект с именем "helloworld" и устанавливаем его версию
project(helloworld VERSION ${PROJECT_VERSION})

# Находим библиотеку Boost, необходимую для тестирования
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Конфигурируем файл версии, который будет использоваться в коде
configure_file(version.h.in version.h)

# Добавляем исполняемый файл helloworld_cli из исходного файла main.cpp
add_executable(helloworld_cli main.cpp)

# Создаем библиотеку helloworld из исходного файла lib.cpp
add_library(helloworld lib.cpp)

# Добавляем исполняемый файл test_version для тестирования
add_executable(test_version test_version.cpp)

# Устанавливаем свойства для целевых файлов, включая стандарт C++
set_target_properties(helloworld_cli helloworld test_version PROPERTIES
    CXX_STANDARD 14  # Указываем стандарт C++14 для компиляции
    CXX_STANDARD_REQUIRED ON  # Обязательно использовать указанный стандарт
)

# Указываем директории для включения заголовочных файлов для библиотеки helloworld
target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"  # Добавляем директорию сборки как частную директорию включения
)

# Устанавливаем свойства для тестового исполняемого файла test_version
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK  # Определяем BOOST_TEST_DYN_LINK для динамической линковки Boost Test
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}  # Указываем директорию включения для заголовков Boost
)

# Связываем библиотеку helloworld с исполняемым файлом helloworld_cli
target_link_libraries(helloworld_cli PRIVATE
    helloworld
)

# Связываем библиотеки с исполняемым файлом test_version
target_link_libraries(test_version
    ${Boost_LIBRARIES}  # Подключаем библиотеки Boost
    helloworld  # Также подключаем библиотеку helloworld
)

# Проверяем, используется ли компилятор Microsoft Visual Studio (MSVC)
if (MSVC)
    # Устанавливаем параметры компиляции для helloworld_cli при использовании MSVC
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    # Устанавливаем параметры компиляции для helloworld_cli при использовании других компиляторов
    target_compile_options(helloworld_cli PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(helloworld PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()  # Конец условия проверки компилятора

# Определяем установку исполняемого файла helloworld_cli в директорию bin
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

# Настраиваем генератор пакетов CPack на создание DEB пакетов (для Linux)
set(CPACK_GENERATOR DEB)

# Устанавливаем версию пакета CPack из переменных PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR и PROJECT_VERSION_PATCH
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# Указываем контактный email для пакета CPack
set(CPACK_PACKAGE_CONTACT example@example.com)

# Включаем поддержку CPack в проекте для создания пакетов
include(CPack)

# Включаем поддержку тестирования в проекте
enable_testing()

# Регистрируем тест test_version, который будет запускаться при выполнении тестов проекта
add_test(test_version test_version)