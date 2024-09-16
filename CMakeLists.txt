cmake_minimum_required(VERSION 3.10)  # Указывает минимальную версию CMake, необходимую для сборки проекта.

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")  # Устанавливает номер патча (PATCH_VERSION) в 1 и сохраняет его в кэше как внутреннюю переменную.
set(PROJECT_VESRION 0.0.${PATCH_VERSION})  # Устанавливает версию проекта (PROJECT_VERSION) в формате 0.0.PATCH_VERSION.

project(helloworld VERSION ${PROJECT_VESRION})  # Определяет проект с именем "helloworld" и устанавливает его версию.

find_package(Boost COMPONENTS unit_test_framework REQUIRED)  # Находит библиотеку Boost, требующую компонент unit_test_framework (для тестирования).

configure_file(version.h.in version.h)  # Конфигурирует файл version.h на основе шаблона version.h.in.

add_executable(helloworld_cli main.cpp)  # Создает исполняемый файл helloworld_cli из исходного файла main.cpp.
add_library(helloworld lib.cpp)  # Создает библиотеку helloworld из исходного файла lib.cpp.
add_executable(test_version test_version.cpp)  # Создает исполняемый файл test_version из исходного файла test_version.cpp.

set_target_properties(helloworld_cli helloworld test_version PROPERTIES  # Устанавливает свойства для целевых файлов helloworld_cli, helloworld и test_version.
    CXX_STANDARD 14  # Указывает стандарт C++14 для компиляции.
    CXX_STANDARD_REQUIRED ON  # Указывает, что стандарт C++14 является обязательным.
)

target_include_directories(helloworld  # Указывает директории для включения заголовочных файлов для библиотеки helloworld.
    PRIVATE "${CMAKE_BINARY_DIR}"  # Добавляет директорию сборки (CMAKE_BINARY_DIR) как частную директорию включения.
)

set_target_properties(test_version PROPERTIES  # Устанавливает свойства для цели test_version.
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK  # Определяет BOOST_TEST_DYN_LINK для динамической линковки Boost Test.
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}  # Указывает директорию включения для заголовков Boost.
)

target_link_libraries(helloworld_cli PRIVATE  # Связывает библиотеку helloworld с исполняемым файлом helloworld_cli.
    helloworld
)

target_link_libraries(test_version  # Связывает библиотеки с исполняемым файлом test_version.
    ${Boost_LIBRARIES}  # Подключает библиотеки Boost.
    helloworld  # Также подключает библиотеку helloworld.
)

if (MSVC)  # Проверяет, используется ли компилятор Microsoft Visual Studio (MSVC).
    target_compile_options(helloworld_cli PRIVATE  # Устанавливает параметры компиляции для helloworld_cli.
        /W4  # Включает уровень предупреждений W4 (высокий уровень предупреждений).
    )
    target_compile_options(helloworld PRIVATE  # Устанавливает параметры компиляции для библиотеки helloworld.
        /W4
    )
    target_compile_options(test_version PRIVATE  # Устанавливает параметры компиляции для тестового исполняемого файла test_version.
        /W4
    )
else ()  # Если не используется MSVC, выполняет следующие действия:
    target_compile_options(helloworld_cli PRIVATE  # Устанавливает параметры компиляции для helloworld_cli.
        -Wall -Wextra -pedantic -Werror  # Включает предупреждения: все (-Wall), дополнительные (-Wextra), строгие (-pedantic), и ошибки (-Werror).
    )
    target_compile_options(helloworld PRIVATE  # Устанавливает параметры компиляции для библиотеки helloworld.
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE  # Устанавливает параметры компиляции для тестового исполняемого файла test_version.
        -Wall -Wextra -pedantic -Werror
    )
endif()  # Конец условия проверки компилятора.

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)  # Определяет установку исполняемого файла helloworld_cli в директорию bin.

set(CPACK_GENERATOR DEB)  # Задает генератор пакетов CPack как DEB (Debian пакет).

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")  # Устанавливает основную версию пакета CPack из переменной PROJECT_VERSION_MAJOR.
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")  # Устанавливает минорную версию пакета CPack из переменной PROJECT_VERSION_MINOR.
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")  # Устанавливает патч-версию пакета CPack из переменной PROJECT_VERSION_PATCH.

set(CPACK_PACKAGE_CONTACT example@example.com)  # Задает контактный email для пакета CPack.

include(CPack)  # Включает поддержку CPack в проекте для создания пакетов.

enable_testing()  # Включает поддержку тестирования в проекте.

add_test(test_version test_version)  # Регистрирует тест test_version, который будет запускаться при выполнении тестов проекта.