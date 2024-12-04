#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GraphicPrimitive.h"

int id_document = 1;

/// @brief класс, представляющий документ
class Document
{
private:
    const int id;                                                     // id документа
    std::string nameDocument;                                         // название документа
    std::string pathDocument;                                         // путь до документа
    std::vector<std::shared_ptr<GraphicPrimitive>> graphicPrimitives; // набор графических примитивов в документе
public:
    /// @brief конструктор по умолчанию
    Document() : nameDocument(""), pathDocument(""), id(id_document++)
    {
        std::cout << "Создан пустой документ; ID: " << id << std::endl;
    }

    /// @brief конструктор с параметрами
    /// @param nameDocument название документа
    /// @param pathDocument путь до документа
    Document(const std::string nameDocument, const std::string pathDocument) : nameDocument(nameDocument), pathDocument(pathDocument), id(id_document++)
    {
        std::cout << "Создан документ: \"" << nameDocument << "\"; путь до документа: " << pathDocument << "; ID: " << id << std::endl;
    }

    /// @brief гетер названия документа
    /// @return название документа
    const std::string getNameDocument()
    {
        std::cout << "Название документа: \"" << nameDocument << "\" (ID: " << id << ")" << std::endl;
        return nameDocument;
    }

    /// @brief гетер id
    /// @return id
    const int getId()
    {
        std::cout << "ID документа \"" << nameDocument << "\": " << id << std::endl;
        return id;
    }

    /// @brief гетер пути документа
    /// @return путь документа
    const std::string getPathDocument()
    {
        std::cout << "Путь до документа \"" << nameDocument << "\": " << pathDocument << " (ID: " << id << ")" << std::endl;
        return pathDocument;
    }

    /// @brief сетер названия документа
    /// @param name название документа
    void setName(const std::string &name)
    {
        nameDocument = name;
        std::cout << "Установлено название документа: \"" << nameDocument << "\" (ID: " << id << ")" << std::endl;
    }

    /// @brief сетер пути документа
    /// @param path путь документа
    void setPath(const std::string &path)
    {
        pathDocument = path;
        std::cout << "Установлен путь до документа \"" << nameDocument << "\": " << pathDocument << " (ID: " << id << ")" << std::endl;
    }

    /// @brief импорт документа из файла
    /// @param path путь файла
    void importDocument(const std::string &path)
    {
        if (pathDocument == path)
        {
            std::cout << "Документ \"" << nameDocument << "\" импортирован из файла: " << path << " (ID: " << id << ")" << std::endl;
        }
        else
        {
            std::cout << "Документа \"" << nameDocument << "\" нет в файле: " << path << " (ID: " << id << ")" << std::endl;
        }
    }

    /// @brief экспорт документа в файл
    /// @param path путь файла
    void exportDocument(const std::string &path)
    {
        pathDocument = path;
        std::cout << "Документ \"" << nameDocument << "\" экспортирован в файл: " << path << " (ID: " << id << ")" << std::endl;
    }

    /// @brief добавление примитива
    /// @param figure примитив
    void addGraphicPrimitive(std::shared_ptr<GraphicPrimitive> figure)
    {
        graphicPrimitives.push_back(figure);
        std::cout << "В документ \"" << nameDocument << "\" (ID: " << id << ") добавлен графический примитив: " << figure->getFigureName() << " (ID: " << figure->getId() << ")" << std::endl;
    }

    /// @brief удаление примитива
    /// @param figure примитив
    void deleteGraphicPrimitive(int id)
    {
        bool found = false; // нашелся ли примитив в документе
        for (auto it = graphicPrimitives.begin(); it != graphicPrimitives.end(); ++it) {
            if ((*it)->getId() == id) { // если ID совпадают
                found = true; // примитив нашелся
                graphicPrimitives.erase(it); // удаляем элемент
                std::cout << "Из документа \"" << getNameDocument() << "\" (ID: " << getId() << ") удален графический примитив с ID: " << id << std::endl;
                break; // выходим из цикла после удаления
            }
        }
        if (!found) { // примитив не нашелся
            std::cout << "Графический примитив с ID: " << id << " не найден в документе \"" << getNameDocument() << "\" (ID: " << getId() << ")" << std::endl;
        }
    }


    void showGraphicPrimitivesInfo() const {
        if (graphicPrimitives.empty()) {
            std::cout << "В документе \"" << nameDocument << "\" (ID: " << id << ") нет графических примитивов." << std::endl;
            return;
        }

        std::cout << "Графические примитивы в документе \"" << nameDocument << "\" (ID: " << id << "):" << std::endl;
        for (const auto& primitive : graphicPrimitives) {
            std::cout << "- " << primitive->getFigureName() << " (ID: " << primitive->getId() << ")" << std::endl;
        }
    }
    

    /// @brief деструктор
    ~Document()
    {
        std::cout << "Удален документ \"" << nameDocument << "\" (ID: " << id << ")" << std ::endl;
    }
};