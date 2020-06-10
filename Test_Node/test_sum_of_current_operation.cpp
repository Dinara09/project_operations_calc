#include <QTest>
#include "test_sum_of_current_operation.h"

Test_sum_of_current_operation::Test_sum_of_current_operation(QObject *parent) :
    QObject(parent)
{

}

void Test_sum_of_current_operation:: fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost)
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

//Операция унарная, операнд – константа (целочисленная)
void Test_sum_of_current_operation::operation_is_unary_operand_is_a_constant_integer()
{
    fill_maps(variables, cost);
    left_branch = new Node("3", nullptr, nullptr, nullptr);
    right_branch = nullptr;
    peek = new Node("-?", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 4);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – переменные (целочисленные)
void Test_sum_of_current_operation::operation_is_binary_operands_are_variables_integer()
{
    fill_maps(variables, cost);
    left_branch = new Node("a", nullptr, nullptr, nullptr);
    right_branch = new Node("a", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 1);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция унарная, операнд – переменная (целочисленная)
void Test_sum_of_current_operation::operation_is_unary_operand_is_a_variable_integer()
{
    fill_maps(variables, cost);
    left_branch = new Node("a", nullptr, nullptr, nullptr);
    right_branch = nullptr;
    peek = new Node("-?", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 4);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – константы (целочисленные)
void Test_sum_of_current_operation::operation_is_binary_operands_are_constants_integers()
{
    fill_maps(variables, cost);
    left_branch = new Node("1", nullptr, nullptr, nullptr);
    right_branch = new Node("2", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 1);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция унарная, операнд – константа (вещественная)
void Test_sum_of_current_operation::operation_is_unary_operand_is_a_constant_floating_point_numbers()
{
    fill_maps(variables, cost);
    left_branch = new Node("3,5", nullptr, nullptr, nullptr);
    right_branch = nullptr;
    peek = new Node("-?", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 4);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – переменные (вещественные)
void Test_sum_of_current_operation::operation_is_binary_operands_are_variables_floating_point_numbers()
{
    fill_maps(variables, cost);
    left_branch = new Node("b", nullptr, nullptr, nullptr);
    right_branch = new Node("c", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 1);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция унарная, операнд – переменная (вещественная)
void Test_sum_of_current_operation::operation_is_unary_operand_is_a_variable_floating_point_numbers()
{
    fill_maps(variables, cost);
    left_branch = new Node("b", nullptr, nullptr, nullptr);
    right_branch = nullptr;
    peek = new Node("-?", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 4);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – константы (вещественные)
void Test_sum_of_current_operation::operation_is_binary_operands_are_constants_floating_point_numbers()
{
    fill_maps(variables, cost);
    left_branch = new Node("1,2", nullptr, nullptr, nullptr);
    right_branch = new Node("2,6", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 1);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – константы (вещественная и целочисленная)
void Test_sum_of_current_operation::operation_is_binary_operands_are_constants_floating_point_numbers_and_integer()
{
    fill_maps(variables, cost);
    left_branch = new Node("1,2", nullptr, nullptr, nullptr);
    right_branch = new Node("2", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 2);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Операция бинарная, операнды – переменные (вещественная и целочисленная)
void Test_sum_of_current_operation::operation_is_binary_operands_are_variables_floating_point_numbers_and_integer()
{
    fill_maps(variables, cost);
    left_branch = new Node("a", nullptr, nullptr, nullptr);
    right_branch = new Node("b", nullptr, nullptr, nullptr);
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 2);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Одна из вершин - оператор
void Test_sum_of_current_operation::one_of_the_vertices_is_operator()
{
    fill_maps(variables, cost);
    left_branch = new Node("a", nullptr, nullptr, nullptr);
    right_branch = new Node("-", nullptr, nullptr, "int");
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 1);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}

//Обе вершины - операторы
void Test_sum_of_current_operation::both_vertices_are_operators()
{
    fill_maps(variables, cost);
    left_branch = new Node("+", nullptr, nullptr, "int");
    right_branch = new Node("-", nullptr, nullptr, "double");
    peek = new Node("+", right_branch, left_branch, nullptr);
    sum_of_operation = peek->sum_of_current_operation(variables, cost);
    QCOMPARE(sum_of_operation, 3);
    all_nodes.clear();
    errors.clear();
    stack.clear();
    sum_of_operation = 0;
}
