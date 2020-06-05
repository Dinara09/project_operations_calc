#include <QTest>
#include "test_node.h"

Test_Node::Test_Node(QObject *parent) :
    QObject(parent)
{
}

void Test_Node:: fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost)
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

bool Test_Node:: is_errors_contains(QList <Error> errors, QString reason_of_error)
{
    bool is_find = false;

    for (int i = 0; i < errors.size(); i++)
    {
        if (errors[i].get_information_of_error() == reason_of_error)
            is_find = true;
    }

    return is_find;
}

 void Test_Node:: expression_tree_from_postfix()
 {
     QMap <int, Node*> all_nodes;
     QList <Error> errors;
     QStack <Node*> stack;
     QMap <QString, QString> variables;
     QMap <QString, QString> cost;

     fill_maps(variables, cost);
     Node *real = new Node ();
     Node *exp = new Node ();
     Node *right_branch = new Node ();
     Node *left_branch = new Node ();

     //Пустое выражение
     real = real->expression_tree_from_postfix("", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "too few operations"), true);
     QCOMPARE (real->get_value() , exp->get_value());
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //Выражение, содержащее только одну переменную и ничего больше
     real = real->expression_tree_from_postfix("a", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "too few operations"), true);
     QCOMPARE (real->get_value() , exp->get_value());
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //Недостаточное количество переменных для выполнения операции
     real = real->expression_tree_from_postfix("a +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "missing number of operands to perform the operation"), true);
     QCOMPARE (real->get_value(), "");
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //Отсутствие пробелов после каждого операнда и оператора
     real = real->expression_tree_from_postfix("ab+", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "missing space between arguments"), true);
     QCOMPARE (real->get_value(), "");
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //Выражение содержит больше 10 операторов
     real = real->expression_tree_from_postfix("a b + c - 1 * 3 - d * 2 / a + 1 + 3 - 1 + 2 -", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "too many operations"), true);
     QCOMPARE (real->get_value(), "");
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //В выражении содержится недопустимый символ
     real = real->expression_tree_from_postfix("( a b ) +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(is_errors_contains(errors, "invalid characters in expression"), true);
     QCOMPARE (real->get_value(), "");
     QCOMPARE (real->get_right(), exp->get_right());
     QCOMPARE (real->get_left(), exp->get_left());
     stack.clear();
     all_nodes.clear();
     errors.clear();

     //Выражение, в котором одна бинарная операция
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

     //Выражение, в котором одна унарная операция
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

     //Выражение, в котором участвуют константные значения
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

     //Вершина дерева – бинарный оператор
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

     //Вершина дерева – унарный оператор
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

     //Каждый оператор бинарный
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

     //Каждый оператор унарный
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

     //Комплексный тест
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

 void Test_Node:: depth_first_search()
 {
     QMap <int, Node*> all_nodes;
     QMap <int, Node*> visit;
     int count = 0;
     QVector <int> sum_of_operation;
     QStack <Node*> tmp;
     QList <Error> errors;
     QStack <Node*> stack;
     QMap <QString, QString> variables;
     QMap <QString, QString> cost;

     fill_maps(variables, cost);
     Node* exp = new Node();
     Node* real = new Node();

     //Дерево с одним бинарным оператором, узлы вершины – переменные
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

     //Дерево с одним унарным оператором
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

     //Дерево с одним бинарным оператором, узлы вершины – константы
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

     //Вершина дерева – бинарный оператор
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

     //Вершина дерева – унарный оператор
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

     //Каждый оператор бинарный
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

     //Каждый оператор унарный
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

     //Комплексный тест
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

 void Test_Node:: recognize_node_type ()
{
     QMap <int, Node*> all_nodes;
     QList <Error> errors;
     QStack <Node*> stack;
     QMap <QString, QString> variables;
     QMap <QString, QString> cost;

     fill_maps(variables, cost);
     Node *current_node = new Node ();
     QString exp;
     QString real;

     //Узел - целочисленная переменная
     current_node = current_node->expression_tree_from_postfix("a b +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(current_node->get_left()->recognize_node_type(variables), "int");
     exp.clear();
     real.clear();
     errors.clear();
     stack.clear();

     //Узел - целочисленная константа
     current_node = current_node->expression_tree_from_postfix("1 b +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(current_node->get_left()->recognize_node_type(variables), "int");
     exp.clear();
     real.clear();
     errors.clear();
     stack.clear();

     //Узел - вещественная константа
     current_node = current_node->expression_tree_from_postfix("1,23 b +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(current_node->get_left()->recognize_node_type(variables), "float");
     exp.clear();
     real.clear();
     errors.clear();
     stack.clear();

     //Узел - вещественная переменная
     current_node = current_node->expression_tree_from_postfix("c b +", stack, all_nodes, errors, variables, cost);
     QCOMPARE(current_node->get_left()->recognize_node_type(variables), "float");
     exp.clear();
     real.clear();
     errors.clear();
     stack.clear();
 }

 void Test_Node:: sum_of_current_operation()
 {
     QMap <int, Node*> all_nodes;
     QList <Error> errors;
     QStack <Node*> stack;
     QMap <QString, QString> variables;
     QMap <QString, QString> cost;
     int sum_of_operation = 0;

     fill_maps(variables, cost);
     Node* left_branch = new Node();
     Node* right_branch = new Node();
     Node* peek = new Node();

     //Операция унарная, операнд – константа (целочисленная)
     left_branch = new Node("3", nullptr, nullptr, nullptr);
     right_branch = nullptr;
     peek = new Node("-?", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 4);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – переменные (целочисленные)
     left_branch = new Node("a", nullptr, nullptr, nullptr);
     right_branch = new Node("a", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 1);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция унарная, операнд – переменная (целочисленная)
     left_branch = new Node("a", nullptr, nullptr, nullptr);
     right_branch = nullptr;
     peek = new Node("-?", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 4);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – константы (целочисленные)
     left_branch = new Node("1", nullptr, nullptr, nullptr);
     right_branch = new Node("2", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 1);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция унарная, операнд – константа (вещественная)
     left_branch = new Node("3,5", nullptr, nullptr, nullptr);
     right_branch = nullptr;
     peek = new Node("-?", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 4);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – переменные (вещественные)
     left_branch = new Node("b", nullptr, nullptr, nullptr);
     right_branch = new Node("c", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 1);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция унарная, операнд – переменная (вещественная)
     left_branch = new Node("b", nullptr, nullptr, nullptr);
     right_branch = nullptr;
     peek = new Node("-?", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 4);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – константы (вещественные)
     left_branch = new Node("1,2", nullptr, nullptr, nullptr);
     right_branch = new Node("2,6", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 1);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – константы (вещественная и целочисленная)
     left_branch = new Node("1,2", nullptr, nullptr, nullptr);
     right_branch = new Node("2", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 2);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Операция бинарная, операнды – переменные (вещественная и целочисленная)
     left_branch = new Node("a", nullptr, nullptr, nullptr);
     right_branch = new Node("b", nullptr, nullptr, nullptr);
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 2);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Одна из вершин - оператор
     left_branch = new Node("a", nullptr, nullptr, nullptr);
     right_branch = new Node("-", nullptr, nullptr, "int");
     peek = new Node("+", right_branch, left_branch, nullptr);
     sum_of_operation = peek->sum_of_current_operation(variables, cost);
     QCOMPARE(sum_of_operation, 1);
     all_nodes.clear();
     errors.clear();
     stack.clear();
     sum_of_operation = 0;

     //Обе вершины - операторы
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


