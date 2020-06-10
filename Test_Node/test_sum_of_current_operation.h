#ifndef TEST_SUM_OF_CURRENT_OPERATION_H
#define TEST_SUM_OF_CURRENT_OPERATION_H
#include <QObject>
#include <QMap>
#include "node.h"

class Test_sum_of_current_operation: public QObject
{
    Q_OBJECT

public:
    QMap <int, Node*> all_nodes;
    QList <Error> errors;
    QStack <Node*> stack;
    QMap <QString, QString> variables;
    QMap <QString, QString> cost;
    int sum_of_operation = 0;

    Node* left_branch = new Node();
    Node* right_branch = new Node();
    Node* peek = new Node();

    void fill_maps (QMap <QString, QString>& variables, QMap <QString, QString>& cost);

    bool is_errors_contains(QList <Error> errors, QString reason_of_error);

    explicit Test_sum_of_current_operation(QObject *parent = 0);

private slots:

    //Операция унарная, операнд – константа (целочисленная)
    void operation_is_unary_operand_is_a_constant_integer();

    //Операция бинарная, операнды – переменные (целочисленные)
    void operation_is_binary_operands_are_variables_integer();

    //Операция унарная, операнд – переменная (целочисленная)
    void operation_is_unary_operand_is_a_variable_integer();

    //Операция бинарная, операнды – константы (целочисленные)
    void operation_is_binary_operands_are_constants_integers();

    //Операция унарная, операнд – константа (вещественная)
    void operation_is_unary_operand_is_a_constant_floating_point_numbers();

    //Операция бинарная, операнды – переменные (вещественные)
    void operation_is_binary_operands_are_variables_floating_point_numbers();

    //Операция унарная, операнд – переменная (вещественная)
    void operation_is_unary_operand_is_a_variable_floating_point_numbers();

    //Операция бинарная, операнды – константы (вещественные)
    void operation_is_binary_operands_are_constants_floating_point_numbers();

    //Операция бинарная, операнды – константы (вещественная и целочисленная)
    void operation_is_binary_operands_are_constants_floating_point_numbers_and_integer();

    //Операция бинарная, операнды – переменные (вещественная и целочисленная)
    void operation_is_binary_operands_are_variables_floating_point_numbers_and_integer();

    //Одна из вершин - оператор
    void one_of_the_vertices_is_operator();

    //Обе вершины - операторы
    void both_vertices_are_operators();
};

#endif // TEST_SUM_OF_CURRENT_OPERATION_H
