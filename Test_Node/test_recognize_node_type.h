#ifndef RECOGNIZE_NODE_TYPE_H
#define RECOGNIZE_NODE_TYPE_H
#include <QObject>
#include <QMap>
#include "node.h"

class Test_recognize_node_type: public QObject
{
    Q_OBJECT

public:
    QMap <int, Node*> all_nodes;
    QList <Error> errors;
    QStack <Node*> stack;
    QMap <QString, QString> variables;
    QMap <QString, QString> cost;

    QString exp;
    QString real;
    Node *current_node = new Node ();

    void fill_maps(QMap<QString, QString> &variables, QMap<QString, QString> &cost);

    explicit Test_recognize_node_type(QObject *parent = 0);
private slots:

    //Узел - целочисленная переменная
    void node_is_an_integer_variable();

    //Узел - целочисленная константа
    void node_is_an_integer_constant();

    //Узел - вещественная константа
    void node_is_a_real_constant();

    //Узел - вещественная переменная
    void node_is_a_real_variable();
};

#endif // RECOGNIZE_NODE_TYPE_H
