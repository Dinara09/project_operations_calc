#ifndef TEST_DEPTH_FIRST_SEARCH_H
#define TEST_DEPTH_FIRST_SEARCH_H
#include <QObject>
#include <QMap>
#include "node.h"

class Test_depth_first_search: public QObject
{
    Q_OBJECT

public:
    QMap <int, Node*> all_nodes;
    QMap <int, Node*> visit;
    int count = 0;
    QVector <int> sum_of_operation;
    QStack <Node*> tmp;
    QList <Error> errors;
    QStack <Node*> stack;
    QMap <QString, QString> variables;
    QMap <QString, QString> cost;
    Node* exp = new Node();
    Node* real = new Node();
    explicit Test_depth_first_search(QObject *parent = 0);

    void fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost);

private slots:

    //Дерево с одним бинарным оператором, узлы вершины – переменные
    void binary_operator_nodes_are_variables();

    //Дерево с одним унарным оператором
    void one_unary_operator();

    //Дерево с одним бинарным оператором, узлы вершины – константы
    void binary_operator_nodes_are_constants();

    //Вершина дерева – бинарный оператор
    void top_is_a_binary_operator();

    //Вершина дерева – унарный оператор
    void top_is_a_unary_operator();

    //Каждый оператор бинарный
    void each_operator_is_binary();

    //Каждый оператор унарный
    void each_operator_is_unary();

    //Комплексный тест
    void comprehensive_test();

};

#endif // TEST_DEPTH_FIRST_SEARCH_H
