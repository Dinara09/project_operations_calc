#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QStringList>
#include <QMap>
#include <QStack>

#include "error.h"

/// \file node.h
/// \brief Заголовочный файл для описания класса node.
///
/// Файл содержит информацию о методах и полях класса node.
///

//класс, содержащий данные об одном узле дерева
/// \brief Класс, содержащий данные об узле дерева.
///
/// Данный класс предоставляет информацию о каждом узле дерева, а именно: текущем узле, его "детях" и о типе текущего узла.
class Node
{

    QString value; //узел
    Node* right; //правая вершина данного узла
    Node* left; //левая вершина данного узла
    QString type_of_node; //тип узла

public:
    //конструктор по-умолчанию
    /// \brief Конструктор без параметров
    Node ();

    //конструктор с параметрами
    /// \brief Конструктор с параметрами
    /// \param [in] value значение текущего узела
    /// \param [in] right правая вершина текущего узла узла
    /// \param [in] left левая вершина текущего узла
    /// \param [in] type_of_node тип текущего узла
    Node (QString value, Node  *right, Node  *left, QString type_of_node);

    //конструктор только с одним параметром
    /// \brief Конструктор с параметрами
    /// \param [in] value значение текущего узела
    Node (QString value);

    //проверка того, что подстрока является оператором
    /// \brief Проверка того, что подстрока является оператором
    /// \param [in] substr_of_expression подстрока выражения для проверки
    /// \return признак того, что подстрока является/не является оператором
    bool is_operator (QString substr_of_expression);

    //проверка на количество операторов выражении
    /// \brief Проверка на количество операторов выражении
    /// \param [in,out] errors контейнер с возникшими ошибками
    /// \param [in] list контейнер с подстроками исходного выражения
    /// \return признак того, что количество операций удовлетворяет/не удовлетворяет установленным границам
    bool validation_of_quantity(QList <Error>& errors, QStringList& list);

    //проверка на содержание в строке знака операции
    /// \brief Проверка на содержание в строке знака операции
    /// \param [in] str подстрока выражения
    /// \return признак того, что подстрока содержит/не содержит знак операции
    bool is_contains_operation (QString str);

    //проверка на содержание переменной в контейнере
    /// \brief Проверка на содержание переменной в контейнер
    /// \param [in] character подстрока выражения
    /// \param [in] data контейнер, в котором будет оуществляться поиск
    /// \return признак того, что подстрока содержится/не содержится в контейнере
    bool is_in_the_container (QString character, QMap<QString, QString>& data);

    //проверка на валидность содержимого выражения
    /// \brief Проверка на валидность содержимого выражения
    /// \param [in,out] errors подстрока выражения
    /// \param [in] list контейнер с подстроками выражения
    /// \param [in] variables контейнер, хранящий информацию о каждой переменной
    /// \param [in] cost контейнер, хранящий информацию о каждой операции
    /// \return признак того, что подстрока валидна/не валидна
    void is_valid_character (QList <Error>& errors, QStringList& list, QMap<QString, QString>& variables, QMap<QString, QString>& cost);

    //построение дерева из обратной польской записи
    /// \brief Построение дерева из обратной польской записи
    /// \param [in] postfix_notation выражение для подсчета в обратной польской записи
    /// \param [in,out] stack стек, для храненияузлолв дерева
    /// \param [in,out] all_nodes контейнер, хранящий посещенные узлы дерева
    /// \param [in,out] errors контейнер, хранящий возникающие ошибки
    /// \param [in] variables контейнер, хранящий информацию о каждой переменной
    /// \param [in] cost контейнер, хранящий информацию о кажой операции
    /// \return указатель, который описывает вершину дерева
    Node *expression_tree_from_postfix(QString postfix_notation, QStack<Node*>& stack, QMap <int, Node*>& all_nodes, QList <Error>& errors, QMap<QString, QString>& variables, QMap<QString, QString>& cost );

    //поиск текущего узла дерева в контейнере, хранящем узлы дерева
    /// \brief Поиск текущего узла дерева в контейнере, хранящем узлы дерева
    /// \param [in] visit контейнер, содержащий посещенные узлы дерева
    /// \return указатель, который описывает глубину дерева
    int search_current_node (QMap <int, Node*> &visit);

    //поиск глубины дерева
    /// \brief Поиск глубины дерева
    /// \param [in] all_nodes контейнер, содержащий все узлы дерева
    /// \param [in,out] visit контейнер, для хранения посещенных узлов
    /// \param [in,out] count расстояние от вершины дерева до текущего узла
    /// \param [in,out] stack стек для хранения посещенныхх узлов
    /// \param [in] variables контейнер, хранящий информацию о каждой переменной
    /// \param [in] cost контейнер, хранящий информацию о кажой операции
    /// \param [out] sum_of_operation вектор, для хранения стоимости операций
    /// \param [in] tmp стек для хранения узлов, не все вершины которого были посещены
    /// \return указатель, который описывает глубину дерева
    Node* depth_first_search(QMap <int, Node*>& all_nodes, QMap <int, Node*> &visit, int &count, QStack <Node*>& stack, QMap<QString, QString>& variables, QMap<QString, QString>& cost, QVector <int>& sum_of_operation, QStack <Node*>& tmp);

    //определение родителя текущего узла
    /// \brief Определение родителя текущего узла
    /// \param [in] visit контейнер, содержащий посещенные узлы дерева
    /// \param [in] current_node текущий узел, родителя которого необходимо определить
    /// \return указатель, который описывает родителя узла
    Node* recognize_parent_of_node (QMap <int, Node*> &visit, Node* current_node);

    //определение типа константы
    /// \brief Определение типа константы
    /// \return строка, описывающая тип константы
    QString recognize_number_type ();

    //определение типа узла
    /// \brief Определение типа узла
    /// \param [in] variables контейнер, хранящий информацию о переменных
    /// \return строка, описывающая тип узла
    QString recognize_node_type (QMap<QString, QString>& variables);

    //определение приоритетного типа
    /// \brief Определение приоритетного типа
    /// \param [in] type_of_left_node тип левой вершины узла
    /// \param [in] type_of_right_node тип правой вершины узла
    /// \param [in] cost контейнер, содержащий информацию о каждой операции
    /// \param [in|out] cost_of_conversion_type вес конвертации из одного типа в другой
    /// \return строка, которая описывает приоритетный тип
    QString priority_recognition (QString type_of_left_node, QString type_of_right_node, QMap<QString, QString>& cost, int& cost_of_conversion_type);


    //стоимость текущей операции
    /// \brief Стоимость текущей операции
    /// \param [in] variables контейнер, содержащий информацию о каждой переменной
    /// \param [in] cost контейнер, содержащий информацию о каждой операции
    /// \return сумма текущей операции
    int sum_of_current_operation(QMap<QString, QString>& variables, QMap<QString, QString>& cost);
};
#endif // NODE_H
