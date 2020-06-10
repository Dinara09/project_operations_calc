#include <QTest>
#include "test_expression_tree_from_postfix.h"

Test_expression_tree_from_postfix::Test_expression_tree_from_postfix(QObject *parent) :
    QObject(parent)
{
}

void Test_expression_tree_from_postfix:: fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost)
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

bool Test_expression_tree_from_postfix:: is_errors_contains(QList <Error> errors, QString reason_of_error)
{
    bool is_find = false;

    for (int i = 0; i < errors.size(); i++)
    {
        if (errors[i].get_information_of_error() == reason_of_error)
            is_find = true;
    }

    return is_find;
}

//Пустое выражение
void Test_expression_tree_from_postfix::empty_expression()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "too few operations"), true);
    QCOMPARE (real->get_value() , exp->get_value());
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Выражение, содержащее только одну переменную и ничего больше
void Test_expression_tree_from_postfix::expression_containing_only_one_variable()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("a", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "too few operations"), true);
    QCOMPARE (real->get_value() , exp->get_value());
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Недостаточное количество переменных для выполнения операции
void Test_expression_tree_from_postfix::not_enough_variables_to_complete_the_operation()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("a +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "missing number of operands to perform the operation"), true);
    QCOMPARE (real->get_value(), "");
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

 //Отсутствие пробелов после каждого операнда и оператора
void Test_expression_tree_from_postfix::no_spaces_after_each_operand_and_operator()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("ab+", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "missing space between arguments"), true);
    QCOMPARE (real->get_value(), "");
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Выражение содержит больше 10 операторов
void Test_expression_tree_from_postfix::expression_contains_more_than_10_statements()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("a b + c - 1 * 3 - d * 2 / a + 1 + 3 - 1 + 2 -", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "too many operations"), true);
    QCOMPARE (real->get_value(), "");
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//В выражении содержится недопустимый символ
void Test_expression_tree_from_postfix::the_expression_contains_an_invalid_character()
{
    fill_maps(variables, cost);
    real = real->expression_tree_from_postfix("( a b ) +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(is_errors_contains(errors, "invalid characters in expression"), true);
    QCOMPARE (real->get_value(), "");
    QCOMPARE (real->get_right(), exp->get_right());
    QCOMPARE (real->get_left(), exp->get_left());
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Выражение, в котором одна бинарная операция
void Test_expression_tree_from_postfix::an_expression_in_which_one_binary_operation()
{
    fill_maps(variables, cost);
    right_branch = new Node ("b", nullptr, nullptr, nullptr);
    left_branch = new Node ("a", nullptr, nullptr, nullptr);
    exp = new Node ("+", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("a b +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right()->get_value(), exp->get_right()->get_value());
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_left(), nullptr);
    QCOMPARE (real->get_right()->get_right(), nullptr);
    QCOMPARE (real->get_right()->get_left(), nullptr);
    stack.clear();
    all_nodes.clear();
    errors.clear();
}
//Выражение, в котором одна унарная операция
void Test_expression_tree_from_postfix:: an_expression_in_which_one_unary_operation()
{
    fill_maps(variables, cost);
    right_branch = new Node (nullptr, nullptr, nullptr, nullptr);
    left_branch = new Node ("a", nullptr, nullptr, nullptr);
    exp = new Node ("+?", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("a +?", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_left(), nullptr);
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Выражение, в котором участвуют константные значения
void Test_expression_tree_from_postfix::an_expression_in_which_constant_values_are_involved()
{
    fill_maps(variables, cost);
    right_branch = new Node ("2", nullptr, nullptr, nullptr);
    left_branch = new Node ("1", nullptr, nullptr, nullptr);
    exp = new Node ("+", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("1 2 +", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right()->get_value(), exp->get_right()->get_value());
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_left(), nullptr);
    QCOMPARE (real->get_right()->get_right(), nullptr);
    QCOMPARE (real->get_right()->get_left(), nullptr);
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Вершина дерева – бинарный оператор
void Test_expression_tree_from_postfix::top_is_a_binary_operator()
{
    fill_maps(variables, cost);
    right_branch = new Node ("+", nullptr, nullptr, nullptr);
    left_branch = new Node ("a", nullptr, nullptr, nullptr);
    exp = new Node ("-", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("a b c + -", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right()->get_value(), exp->get_right()->get_value());
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_right()->get_right()->get_value(), "c");
    QCOMPARE (real->get_right()->get_left()->get_value(), "b");
    QCOMPARE (real->get_left()->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_left(), nullptr);
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Вершина дерева – унарный оператор
void Test_expression_tree_from_postfix::top_unary_operator()
{
    fill_maps(variables, cost);
    right_branch = new Node (nullptr, nullptr, nullptr, nullptr);
    left_branch = new Node ("+", nullptr, nullptr, nullptr);
    exp = new Node ("+?", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("1 2 + +?", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right()->get_value(), "2");
    QCOMPARE (real->get_left()->get_left()->get_value(), "1");
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Каждый оператор бинарный
void Test_expression_tree_from_postfix::each_operator_is_binary()
{
    fill_maps(variables, cost);
    right_branch = new Node ("+", nullptr, nullptr, nullptr);
    left_branch = new Node ("+", nullptr, nullptr, nullptr);
    exp = new Node ("-", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("1 2 + 2 3 + -", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right()->get_value(), exp->get_right()->get_value());
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right()->get_value(), "2");
    QCOMPARE (real->get_left()->get_left()->get_value(), "1");
    QCOMPARE (real->get_right()->get_right()->get_value(), "3");
    QCOMPARE (real->get_right()->get_left()->get_value(), "2");
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Каждый оператор унарный
void Test_expression_tree_from_postfix::each_operator_is_unary()
{
    fill_maps(variables, cost);
    right_branch = new Node (nullptr, nullptr, nullptr, nullptr);
    left_branch = new Node ("+?", nullptr, nullptr, nullptr);
    exp = new Node ("-?", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("1 +? -?", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right(), nullptr);
    QCOMPARE (real->get_left()->get_left()->get_value(), "1");
    stack.clear();
    all_nodes.clear();
    errors.clear();
}

//Комплексный тест
void Test_expression_tree_from_postfix::comprehensive_test()
{
    fill_maps(variables, cost);
    right_branch = new Node ("-?", nullptr, nullptr, nullptr);
    left_branch = new Node ("+", nullptr, nullptr, nullptr);
    exp = new Node ("*", right_branch, left_branch, nullptr);
    real =real->expression_tree_from_postfix("a b + 3 -? *", stack, all_nodes, errors, variables, cost);
    QCOMPARE(errors.empty(), true);
    QCOMPARE (real->get_value(), exp->get_value());
    QCOMPARE (real->get_right()->get_value(), exp->get_right()->get_value());
    QCOMPARE (real->get_left()->get_value(), exp->get_left()->get_value());
    QCOMPARE (real->get_left()->get_right()->get_value(), "b");
    QCOMPARE (real->get_left()->get_left()->get_value(), "a");
    QCOMPARE (real->get_right()->get_right(), nullptr);
    QCOMPARE (real->get_right()->get_left()->get_value(), "3");
    stack.clear();
    all_nodes.clear();
    errors.clear();
}
