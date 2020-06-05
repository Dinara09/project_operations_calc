#ifndef TEST_NODE_H
#define TEST_NODE_H
#include <QObject>
#include <QMap>
#include "node.h"


class Test_Node : public QObject
{
    Q_OBJECT
    QMap <QString, QString> variables;
    QMap <QString, QString> cost;

public:
    void fill_maps (QMap <QString, QString>& variables, QMap <QString, QString>& cost);

    bool is_errors_contains(QList <Error> errors, QString reason_of_error);

    explicit Test_Node(QObject *parent = 0);

private slots: // должны быть приватными
    void expression_tree_from_postfix();

    void depth_first_search();

    void sum_of_current_operation();

    void recognize_node_type ();
};

#endif // TEST_NODE_H
