#include <QTest>
#include "test_depth_first_search.h"

Test_depth_first_search::Test_depth_first_search(QObject *parent) :
    QObject(parent)
{

}

void Test_depth_first_search:: fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost)
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

//Дерево с одним бинарным оператором, узлы вершины – переменные
void Test_depth_first_search::binary_operator_nodes_are_variables()
{
    fill_maps(variables, cost);

    real = real->expression_tree_from_postfix("a b +", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("a", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 2);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Дерево с одним унарным оператором
void Test_depth_first_search::one_unary_operator()
{
    real = real->expression_tree_from_postfix("a +?", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("a", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 3);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Дерево с одним бинарным оператором, узлы вершины – константы
void Test_depth_first_search:: binary_operator_nodes_are_constants()
{
    real = real->expression_tree_from_postfix("1 2 +", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("1", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 1);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Вершина дерева – бинарный оператор
void Test_depth_first_search::top_is_a_binary_operator()
{
    real = real->expression_tree_from_postfix("b c + a -", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("b", nullptr, nullptr, "float");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 3);
    QCOMPARE(sum_of_operation[1], 1);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Вершина дерева – унарный оператор
void Test_depth_first_search::top_is_a_unary_operator()
{
    real = real->expression_tree_from_postfix("1 2 + +?", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("1", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 3);
    QCOMPARE(sum_of_operation[1], 1);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}
//Каждый оператор бинарный
void Test_depth_first_search:: each_operator_is_binary()
{
    real = real->expression_tree_from_postfix("1 2 + 2 3 + -", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("1", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 2);
    QCOMPARE(sum_of_operation[1], 1);
    QCOMPARE(sum_of_operation[2], 1);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Каждый оператор унарный
void Test_depth_first_search:: each_operator_is_unary()
{
    real = real->expression_tree_from_postfix("1 +? -?", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("1", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 4);
    QCOMPARE(sum_of_operation[1], 3);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

//Комплексный тест
void Test_depth_first_search::comprehensive_test()
{
    real = real->expression_tree_from_postfix("a b + 3 -? *", stack, all_nodes,errors, variables, cost);
    real = real->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, tmp);
    exp = new Node ("a", nullptr, nullptr, "int");
    QCOMPARE(real->get_value(), exp->get_value());
    QCOMPARE(real->get_type_of_node(), exp->get_type_of_node());
    QCOMPARE(sum_of_operation[0], 6);
    QCOMPARE(sum_of_operation[1], 4);
    QCOMPARE(sum_of_operation[2], 2);
    stack.clear();
    all_nodes.clear();
    errors.clear();
    visit.clear();
    count = 0;
    sum_of_operation.clear();
    tmp.clear();
}

