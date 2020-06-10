#ifndef TEST_EXPRESSION_TREE_FROM_POSTFIX_H
#define TEST_EXPRESSION_TREE_FROM_POSTFIX_H
#include <QObject>
#include <QMap>
#include "node.h"

class Test_expression_tree_from_postfix : public QObject
{
    Q_OBJECT

public:
    QMap <int, Node*> all_nodes;
    QList <Error> errors;
    QStack <Node*> stack;
    QMap <QString, QString> variables;
    QMap <QString, QString> cost;

    Node *real = new Node ();
    Node *exp = new Node ();
    Node *right_branch = new Node ();
    Node *left_branch = new Node ();

    void fill_maps (QMap <QString, QString>& variables, QMap <QString, QString>& cost);

    bool is_errors_contains(QList <Error> errors, QString reason_of_error);

    explicit Test_expression_tree_from_postfix(QObject *parent = 0);

private slots:

    //Пустое выражение
    void empty_expression();

    //Выражение, содержащее только одну переменную и ничего больше
    void expression_containing_only_one_variable();

    //Недостаточное количество переменных для выполнения операции
    void not_enough_variables_to_complete_the_operation();

     //Отсутствие пробелов после каждого операнда и оператора
    void no_spaces_after_each_operand_and_operator();

    //Выражение содержит больше 10 операторов
    void expression_contains_more_than_10_statements();

    //В выражении содержится недопустимый символ
    void the_expression_contains_an_invalid_character();

    //Выражение, в котором одна бинарная операция
    void an_expression_in_which_one_binary_operation();

    //Выражение, в котором одна унарная операция
    void an_expression_in_which_one_unary_operation();

    //Выражение, в котором участвуют константные значения
    void an_expression_in_which_constant_values_are_involved();

    //Вершина дерева – бинарный оператор
    void top_is_a_binary_operator();

    //Вершина дерева – унарный оператор
    void top_unary_operator();

    //Каждый оператор бинарный
    void each_operator_is_binary();

    //Каждый оператор унарный
    void each_operator_is_unary();

    //Комплексный тест
    void comprehensive_test();
};

#endif // TEST_EXPRESSION_TREE_FROM_POSTFIX_H
