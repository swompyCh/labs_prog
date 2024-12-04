#include "GraphicPrimitive.h"
#include "DocController.h"


// Представление GUI
void printMenu()
{
    std::cout << "\nВыберитe действие:\n";
    std::cout << "1. Создать документ\n";
    std::cout << "2. Импорт документа\n";
    std::cout << "3. Экспорт документа\n";
    std::cout << "4. Добавить примитив\n";
    std::cout << "5. Удалить примитив\n";
    std::cout << "6. Показать информацию о текущем документе\n";
    std::cout << "7. Выход\n";
    std::cout << "Введите номер действия: ";
}

int main()
{
    Controller controller;

    while (true)
    {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            controller.createDocument();
            break;
        case 2:
        {
            std::cout << "Введите путь до импортируемого документа: ";
            std::string path;
            std::cin >> path;
            std::cout << "Импорт документа из файла: " << std::endl;
            controller.importDocument(path);
            std::cout << std::endl;
            break;
        }
        case 3:
        {
            std::cout << "Введите путь до экспортируемого документа: " << std::endl;
            std::string path;
            std::cin >> path;
            controller.exportDocument(path);
            std::cout << std::endl;
            break;
        }
        case 4:
        {
            std::cout << "Введите тип примитива(Circle, Square, Rectangle): " << std::endl;
            std::string type;
            std::cin >> type;
            controller.addGraphicPrimitive(type);
            break;
        }
        case 5:
        {
            std::cout << "Введите ID графического примитива для удаления: " << std::endl;
            int id;
            std::cin >> id;
            controller.deleteGraphicPrimitive(id);
            std::cout << std::endl;
            break;
        }
        case 6:
        {
            std::cout << "Показать информацию о текущем документе: " << std::endl;
            controller.showCurrentDocumentInfo();
            std::cout << std::endl;
            break;
        }
        case 7:
        {
            std::cout << "Выход.\n";
            return 0;
        }
        default:
            std::cout << "Неккоректный выбор";
        }
    }

    // std::cout << "Создание нового документа: " << std::endl;
    // controller.createDocument("Мой документ", "/path/to/document");
    // std::cout << std::endl;

    // std::cout << "Добавление графических примитивов: " << std::endl;
    // controller.addGraphicPrimitive("круг", 5.0);                 // добавляем круг с радиусом 5.0
    // controller.addGraphicPrimitive("прямоугольник", 10.0, 20.0); // добавляем прямоугольник 10x20
    // controller.addGraphicPrimitive("квадрат", 15.0);             // добавляем квадрат со стороной 15.0
    // std::cout << std::endl;

    // std::cout << "Показать информацию о текущем документе: " << std::endl;
    // controller.showCurrentDocumentInfo();
    // std::cout << std::endl;

    // std::cout << "Экспорт документа в файл: " << std::endl;
    // controller.exportDocument("/path/to/exported_document");
    // std::cout << std::endl;

    // std::cout << "Импорт документа из файла: " << std::endl;
    // controller.importDocument("/path/to/document");
    // std::cout << std::endl;

    // std::cout << "Удаление графического примитива: " << std::endl;
    // controller.deleteGraphicPrimitive("круг");
    // std::cout << std::endl;

    // std::cout << "Вызов деструкторов после завершения программы: " << std::endl;
    // return 0;
}