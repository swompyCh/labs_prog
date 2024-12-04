#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "Document.h"

class Controller {
private:
    std::shared_ptr<Document> currentDocument; // текущий документ
public:
    
    Controller() : currentDocument(nullptr) {}
    
    void createDocument() {
        std::cout << "Введите имя нового документа: ";
        std::string filename;
        std::cin >> filename;

        std::cout << "Введите путь для нового документа: ";
        std::string path;
        std::cin >> path;

        currentDocument = std::make_shared<Document>(filename, path);
    }
  
    void importDocument(const std::string& path) {
        if (currentDocument) {
            currentDocument->importDocument(path);
        } else {
            std::cout << "Нет текущего документа для импорта" << std::endl;
        }
    }
    
    void exportDocument(const std::string& path) {
        if (currentDocument) {
            currentDocument->exportDocument(path);
        } else {
            std::cout << "Нет текущего документа для экспорта" << std::endl;
        }
    }
    
    void setCurrentDocument(const std::shared_ptr<Document>& document) {
        currentDocument = document;
    }
    
    void addGraphicPrimitive(const std::string& type) {
        if (!currentDocument) {
            std::cout << "Нет текущего документа. Сначала создайте или выберите документ." << std::endl;
            return;
        }
        std::shared_ptr<GraphicPrimitive> primitive;
        if (type == "Circle") {
            std::cout << "Введите радиус: ";
            double radius;
            std::cin >> radius;

            primitive = std::make_shared<Circle>(radius);
        } else if (type == "Rectangle") {
            std::cout << "Введите длину: ";
            double length;
            std::cin >> length;

            std::cout << "Введите ширину: ";
            double width;
            std::cin >> width;

            primitive = std::make_shared<Rectangle>(width, length);
        } else if (type == "Square") {
            std::cout << "Введите длину: ";
            double length;
            std::cin >> length;

            primitive = std::make_shared<Square>(length);
        } else {
            std::cout << "Неизвестный тип графического примитива: " << type << std::endl;
            return;
        }
        currentDocument->addGraphicPrimitive(primitive);
    }
    
    void deleteGraphicPrimitive(int id) {
        if (!currentDocument) {
            std::cout << "Нет текущего документа. Сначала создайте или выберите документ" << std::endl;
            return;
        }

        currentDocument->deleteGraphicPrimitive(id);
    }
    
    void showCurrentDocumentInfo() const {
        if (currentDocument) {
            std::cout << "Информация о текущем документе:" << std::endl;
            currentDocument->getNameDocument();
            currentDocument->getId();
            currentDocument->getPathDocument();
            
            // Вывод информации о графических примитивах
            currentDocument->showGraphicPrimitivesInfo();
        } else {
            std::cout << "Нет текущего документа" << std::endl;
        }
    }
};