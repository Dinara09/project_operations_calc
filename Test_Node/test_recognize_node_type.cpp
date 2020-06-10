#include <QTest>
#include "test_recognize_node_type.h"

Test_recognize_node_type::Test_recognize_node_type(QObject *parent):
    QObject(parent)
{

}

void Test_recognize_node_type:: fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost)
{
    variables.insert("a", "int");
    variables.insert("b", "float");
    variables.insert("c", "float");
    variables.insert("x", "double");
    variables.insert("y", "int");


    cost.insert("+", "1");
    cost.insert("-", "2");
    cost.insert("+?", "3");
    cost.insert("-?", "4");
    cost.insert("*", "5");
    cost.insert("/", "6");
    cost.insert("intTOfloat", "1");
    cost.insert("intTOdouble", "2");
    cost.insert("floatTOdoble", "3");
}

//Узел - целочисленная переменная
void Test_recognize_node_type::node_is_an_integer_variable()
{

    fill_maps(variables, cost);
    current_node = current_node->expression_tree_from_postfix("a b +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(current_node->get_left()->recognize_node_type(variables), "int");
    exp.clear();
    real.clear();
    errors.clear();
    stack.clear();
}

//Узел - целочисленная константа
void Test_recognize_node_type::node_is_an_integer_constant()
{
    fill_maps(variables, cost);
    current_node = current_node->expression_tree_from_postfix("1 b +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(current_node->get_left()->recognize_node_type(variables), "int");
    exp.clear();
    real.clear();
    errors.clear();
    stack.clear();
}

//Узел - вещественная константа
void Test_recognize_node_type::node_is_a_real_constant()
{
    fill_maps(variables, cost);
    current_node = current_node->expression_tree_from_postfix("1,23 b +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(current_node->get_left()->recognize_node_type(variables), "float");
    exp.clear();
    real.clear();
    errors.clear();
    stack.clear();
}

//Узел - вещественная переменная
void Test_recognize_node_type::node_is_a_real_variable()
{
    fill_maps(variables, cost);
    current_node = current_node->expression_tree_from_postfix("c b +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(current_node->get_left()->recognize_node_type(variables), "float");
    exp.clear();
    real.clear();
    errors.clear();
    stack.clear();
}
