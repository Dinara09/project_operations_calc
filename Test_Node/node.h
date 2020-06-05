#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QMap>
#include <QStack>
#include "error.h"

class Node
{
    QString value; //узел
    Node* right; //правая вершина данного узла
    Node* left; //левая вершина данного узла
    QString type_of_node; //тип узла

public:

    //получение данных о поле code_of_error
    QString get_value ();

    //получение данных о поле column_of_error
    Node* get_right ();

    //получение данных о поле information_of_error
    Node* get_left ();

    //получение данных о поле code_of_error
    QString get_type_of_node ();

    void fill_variables(QMap<QString, QString>& variables);

    void fill_cost (QMap<QString, QString>& cost);

    int search_current_node (QMap <int, Node*> &visit);

    Node *expression_tree_from_postfix(QString postfix_notation, QStack<Node*>& stack, QMap <int, Node*>& all_nodes, QList <Error>& errors, QMap<QString, QString>& variables, QMap<QString, QString>& cost );

    Node* depth_first_search(QMap <int, Node*>& all_nodes, QMap <int, Node*> &visit, int &count, QStack <Node*>& stack, QMap<QString, QString>& variables, QMap<QString, QString>& cost, QVector <int>& sum_of_operation, QStack <Node*>& stack1);

    Node* recognize_parent_of_node (QMap <int, Node*> &visit, Node* current_node);

    QString recognize_number_type();

    QString recognize_node_type (QMap<QString, QString>& variables);

    QString priority_recognition (QString type_of_left_node, QString type_of_right_node, QMap<QString, QString>& cost, int& cost_of_conversion_type);

    int  sum_of_current_operation(QMap<QString, QString>& variables, QMap<QString, QString>& cost);

    //конструктор по-умолчанию
    Node ();

    //конструктор с параметрами
    Node (QString value, Node  *right, Node  *left, QString type_of_node);

    //конструктор только с одним параметром
    Node (QString value);
};

#endif // NODE_H
