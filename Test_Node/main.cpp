#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_expression_tree_from_postfix.h"
#include "test_depth_first_search.h"
#include "test_recognize_node_type.h"
#include "test_sum_of_current_operation.h"

int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new Test_expression_tree_from_postfix, argc, argv);
    QTest::qExec(new Test_depth_first_search, argc, argv);
    QTest::qExec(new Test_recognize_node_type, argc, argv);
    QTest::qExec(new Test_sum_of_current_operation, argc, argv);
    return 0;
}
