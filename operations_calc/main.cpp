#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include <QtGlobal>
#include <QFile>
#include <QMap>
#include <QStack>

using namespace std;

//ЗАМЕТКИ//
/*
str=str+file.readLine();                      ПОСТРОЧНОЕ ЧТЕНИЕ
*/
/*class Error
{
    int code_of_error;
    int line_of_error;
    QString information_of_error;

public:
    //конструктор по-умолчанию
    Error ()
    {
        this->code_of_error = NULL;
        this->line_of_error = NULL;
        this->information_of_error = nullptr;
    }

    //конструктор с параметрами
    Error (int code_of_error, int line_of_error, QString information_of_error)
    {
        this->code_of_error = code_of_error;
        this->line_of_error = line_of_error;
        this->information_of_error = information_of_error;
    }
};*/

//класс, содержащий данные об одном узле дерева
class Node
{

    QString value; //узел
    Node* right; //правая вершина данного узла
    Node* left; //левая вершина данного узла
    QString type_of_node;

public:
    //конструктор по-умолчанию
    Node ()
    {
        this->value = nullptr;
        this->right = nullptr;
        this->left = nullptr;
        this->type_of_node = nullptr;
    }

    //конструктор с параметрами
    Node (QString value, Node  *right, Node  *left, QString type_of_node)
    {
        this->value = value;
        this->right = right;
        this->left = left;
        this->type_of_node = type_of_node;
    }

    //конструктор только с одним параметром
    Node (QString value)
    {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
        this->type_of_node = nullptr;
    }

    //проверка того, что подстрока является оператором
    bool is_operator (QString substr_of_expression)
    {
        if (substr_of_expression == "/" || substr_of_expression == "*" || substr_of_expression == "+" || substr_of_expression == "-"
                || substr_of_expression == "-?" || substr_of_expression == "+?") //если подстрока удовлетворяет данному условию...
        {
            return true;// вернуть признак того, что подстрока - оператор
        }

        return false;// иначе, вернуть прихнак того, что подстрока - операнд
    }

    Node* parent_of_node (QMap <int, Node*> &visit, Node* current_node)
    {
        QMap <int, Node*>::iterator iter;
        Node* node;
        for(iter = visit.begin(); iter != visit.end(); ++iter)
        {
            node = iter.value();
            if (iter.value()->right == current_node || iter.value()->left == current_node)
            {
                return iter.value();
            }
            /*if (node->left != nullptr || node->right != nullptr)
            {
                if (node->right != nullptr)
                {
                    if ((node->right->value == this->value && node->right->left == this->left && node->right->right == this->right) || (node->left->value == this->value && node->left->left == this->left && node->left->right == this->right) )
                    {
                        return iter.value();
                    }
                }
                else
                {
                    if (node->left->value == this->value && node->left->left == this->left && node->left->right == this->right)
                    {
                        return iter.value();
                    }
                }
            }*/
        }
        return nullptr;
    }

    //построение дерева из обратной польской записи
    Node *expression_tree_from_postfix(QString postfix_notation, QStack<Node*>& stack, QMap <int, Node*>& all_nodes)
    {
        QString substr; //строка, хранящая текущую подстроку выражения в обратной польской записи
        Node *part_of_tree;
        Node  *right_branch, *left_branch; //
        QStringList list; //контейнер, хранящий подстроки выражения в обратной польской записи
        int index_of_current_substr; //индекс текущей подстроки в контейнере list
        int size_of_expression = 0; //количество операторов и операндов в выражении

        for (int i = 0; i < postfix_notation.size(); i++) //для всех символов строки и пока не дошли до конца...
        {
            if (postfix_notation[i] == ' ') //если текущий символ - пробел...
            {
                size_of_expression++; //инкрементируем значение операндов и операторов
            }
        }
        size_of_expression++; //инкрементрием значение операндов и операторов (в итоге получаем значение операторов и операндов в строке)

        /*if (size_of_expression < 2) //если выражение состоит меньше, чем из двух подстрок
        {
            Error too_few_arguments(0, 101, "too_few_arguments"); //создаем и заполняем объект класса Error
            errors.insert(0, too_few_arguments); //запоминаем ошибку в контейнере QList
        }*/

        list = postfix_notation.split( QRegExp("\\s+")); //разбиваем выражение в обратной польской записи на подстроки и сохраняем их в контейнере list
        substr = list[0]; //запоминаем в переменной substr первую подстроку выражения в обратной польской записи
        index_of_current_substr = 1; //переменная, хранящая индекс текущей подстроки в контейнере list становится равной 1

        for (int i = 1; substr != nullptr && index_of_current_substr <= size_of_expression; i++) //для каждой подстроки выражения и пока не дошли до конца
        {//и индекс текущей подстроки в контейнере list не больше количества операторов и операндов в выражении...

            if (!is_operator(substr)) //если подстрока - операнд...
            {
                Node *part_of_tree = new Node (substr); //инициализируем объект при помощи конструктора с одним параметром
                stack.push(part_of_tree); //добавить текущий элемент в стек
                all_nodes.insert(i-1, part_of_tree);
            }

            else //иначе, если текущая подстрока - операнд...
            {
                if (substr == "-?" || substr == "+?")
                {
                    left_branch = stack.pop(); //выгрузить из стека текущий элемент и запомнить в перемнную right_branch
                    part_of_tree = new Node (substr, nullptr, left_branch, nullptr); //инициализируем объект при помощи конструктора с параметрами
                }
                else
                {
                    right_branch = stack.pop(); //выгрузить из стека текущий элемент и запомнить в перемнную right_branch
                    left_branch = stack.pop(); //выгрузить из стека следующий за текущий элемент в переменную left_branch
                    part_of_tree = new Node (substr, right_branch, left_branch, nullptr); //инициализируем объект при помощи конструктора с параметрами
                }

                stack.push(part_of_tree); //добавить текущий элемент в стек
                all_nodes.insert(i-1, part_of_tree);
            }

            if (index_of_current_substr != size_of_expression) //если индекс текущей подстроки в контейнере list не равен больше количеству операторов и операндов в выражении...
                substr = list[i]; //достать из контейнера list  следующую подстроку и запомнить ее в перемнную substr

            index_of_current_substr++; //инкрементировать значение индекса текущей подстроки
        }
        return stack[0]; //вернуть элемент начала стека
    }

    int search_current_node (QMap <int, Node*> &visit)
    {
        QMap<int, Node*>::iterator iter;
        for (iter = visit.begin(); iter != visit.end(); ++iter)
        {

            if (iter.value() == this)
            {
                return iter.key();
            }
        }
        return NULL;
    }

    Node* depth_first_search(QMap <int, Node*>& all_nodes, QMap <int, Node*> &visit, int &count, QStack <Node*>& stack)
    {
        while (all_nodes.size() != visit. size())
        {
            count++;

            if (this->left != nullptr && this->left->search_current_node(visit) == NULL)
            {
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this);
                }
                stack.push(this);
                return left->depth_first_search(all_nodes, visit, count, stack);
            }

            if (this->right != nullptr && this->right->search_current_node(visit) == NULL)
            {
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this);
                }
                stack.push(this);
                return right->depth_first_search(all_nodes, visit, count, stack);
            }

            if (this->left == nullptr && this->right == nullptr)
            {
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this);
                    if (!stack.empty())
                    {
                    Node*peek = stack.pop();
                    int key = peek->search_current_node(visit);
                    if (visit.value(key)->right != nullptr)
                    {
                        return visit.value(key)->right->depth_first_search(all_nodes, visit, key, stack);
                    }
                    else
                    {
                        peek = stack.pop();
                        key = peek->search_current_node(visit);
                        return visit.value(key)->right->depth_first_search(all_nodes, visit, key, stack);
                    }
                    }

                }

            }
        }

        return visit.last();
     }


    void remove (QMap <int, Node*>& nodes)
    {
        QMap <int, Node*>::iterator iter;
        bool is_find = false;
        iter = nodes.begin();

        while (is_find != true)
        {
            if (iter.value() == this)
            {
                nodes.erase(iter);
                is_find = true;
            }
            else
            {
                if (iter != nodes.end())
                iter++;
                else is_find = true;
            }
        }

    }


    int sum_of_operations (QMap <int, Node*>& visit, QMap <QString, QString>& variables, QMap <QString, QString>& cost)
    {
        Node* parent;
        QVector <int> sum_of_operation;
        int sum = 0;
        int count = 0;

        QMap <int, Node*> labeled_nodes;
        QMap <int, Node*> visit1;
        QStack <Node*> stack;
        labeled_nodes = visit;
        Node * node;
        parent = parent_of_node(visit, visit.last());

        while (parent != nullptr)
        {
            //key = this->search_current_node(visit);
            //parent = parent_of_node(visit);

            if (parent_of_node(visit, parent) == nullptr)
            {
                if (!labeled_nodes.empty())
                {
                    parent->remove(labeled_nodes);
                    if (parent->right->search_current_node(labeled_nodes) != NULL)
                    {
                        node = parent->right->depth_first_search(labeled_nodes, visit1,count,stack);
                    }
                    else if (parent->left->search_current_node(labeled_nodes) != NULL)
                    {
                        node = parent->left->depth_first_search(labeled_nodes, visit1,count,stack);
                    }
                    parent = parent_of_node(visit, node);
                }

            }

            sum_of_operation.prepend(parent->sum_of_current_operation(variables, cost));
            parent->left->remove(labeled_nodes);
            parent->right->remove(labeled_nodes);
            parent->remove(labeled_nodes);

            if (parent_of_node(visit, parent) != nullptr)
            {
                parent = parent_of_node(visit, parent);
            }
            else
                parent = nullptr;



        }

        for (int i = 0; i < sum_of_operation.size(); i++)
        {
            sum+=sum_of_operation[i];
        }
        return sum;
    }

    QString recognize_number_type ()
    {
        int whole_part;
        int fractional_part;
        bool ok;
        QStringList list = this->value.split(",");
        whole_part = list[0].toInt(& ok, 10);
        if (list.size() != 1)
        {
            fractional_part = list[1].toInt(& ok, 10);
        }
        if (fractional_part == NULL)
        {
            return "int";
        }
        else if ((whole_part-1 >  2147483646 && fractional_part > 0) || (whole_part+1 <  -2147483647 && fractional_part < 0))
        {
           return "double";
        }
        else
            return "float";
    }

    QString recognize_node_type (QMap<QString, QString>& data)
    {
        QRegExp str("\\d*,?\\d*");
        QString type_of_node;
        QMap<QString, QString>::iterator iter;

        if (is_operator(this->value))
        {
            type_of_node = this->type_of_node;
        }
        else
        {
            if (str.exactMatch(this->value))
            {
                type_of_node = this->recognize_number_type();
            }
            else
            {
                 type_of_node = data.find(this->value).value();
            }
        }

        this->type_of_node = type_of_node;
        return type_of_node;
    }

    QString priority_recognition (QString type_of_left_node, QString type_of_right_node)
    {
        QString priority_type;
        if (type_of_left_node == "int" && type_of_right_node == "int")
            priority_type = "int";
        else if ((type_of_left_node == "int" && type_of_right_node == "float") || (type_of_left_node == "float" && type_of_right_node == "int"))
            priority_type = "float";
        else if (type_of_left_node == "float" && type_of_right_node == "float")
            priority_type =  "float";
        else if (type_of_left_node == "double" || type_of_right_node == "double")
            priority_type =  "double";
        else if (type_of_left_node == "int" && type_of_right_node == "")
        {
            priority_type = "int";
        }
        else if (type_of_left_node == "float" && type_of_right_node == "")
        {
            return "float";
        }
        else if (type_of_left_node == "double" && type_of_right_node == "")
        {
            return  "double";
        }
        return priority_type;
    }

int sum_of_current_operation(QMap<QString, QString>& variables, QMap<QString, QString>& cost)
{
    QString type_of_left_node;
    QString type_of_right_node;
    QString priority_type;
    QString cost_of_node;
    bool ok;
    if (this->left != nullptr)
    {
        if (!is_operator(this->left->value))
        {
            type_of_left_node = this->left->recognize_node_type(variables);
        }
        else
        {
            type_of_left_node = this->left->type_of_node;
        }
    }
    if (this->right != nullptr)
    {
        if (!is_operator(this->right->value))
        {
            type_of_right_node = this->right->recognize_node_type(variables);
        }
        else
        {
            type_of_right_node = this->right->type_of_node;
        }
    }
    priority_type = priority_recognition(type_of_left_node, type_of_right_node);
    this->type_of_node = priority_type;
    cost_of_node = cost.find(priority_type+this->value).value();
    return cost_of_node.toInt(& ok, 10);
}



   /* bool find (Node* part_of_tree,  QMap <int, Node*> distance_of_all_paths)
    {
        bool result = false;
        Node* res;
        QMap <int, Node*>:: iterator iter;
        for (iter = distance_of_all_paths.begin(); iter != distance_of_all_paths.end(); ++iter)
        {
            res = iter.value();
            if (res == part_of_tree)
            {
                return true;
            }
        }

        return result;
    }

    //алгоритм поиска в глубину
    void depth_first_search_of_one_way (int count_of_nodes, QMap <int, Node*>& distance_of_all_paths )
    {
        distance_of_all_paths.insert(count_of_nodes, this);

        if (left != nullptr && is_operator (left->value) && !find(left, distance_of_all_paths))
        {
            count_of_nodes++;
            distance_of_all_paths.insert(count_of_nodes, left);
            left->depth_first_search_of_one_way(count_of_nodes, distance_of_all_paths);

            //sum_of_value_of_operations += left->depth_first_search();
        }

        else if (right != nullptr && is_operator (right->value) && !find(right, distance_of_all_paths))
        {
            count_of_nodes++;
            distance_of_all_paths.insertMulti(count_of_nodes, right);
            right->depth_first_search_of_one_way(count_of_nodes, distance_of_all_paths);

            //sum_of_value_of_operations += right->depth_first_search();
        }
        else if (left != nullptr&& !find(left, distance_of_all_paths))
        {
            count_of_nodes++;
            distance_of_all_paths.insertMulti(count_of_nodes, left);
        }
        else if (right != nullptr&& !find(right, distance_of_all_paths))
        {
            count_of_nodes++;
            distance_of_all_paths.insertMulti(count_of_nodes, right);
        }
        //return sum_of_value_of_operations;
    }

    bool is_all_nodes_visited (QMap <int, Node*>& distance_of_all_paths)
    {
        bool is_visited = false;
        QMap <int, Node*>:: iterator iter;
        for (iter = distance_of_all_paths.begin(); iter != distance_of_all_paths.end(); ++iter)
        {
            is_visited = find(iter.value(), distance_of_all_paths);
            if (!find(left, distance_of_all_paths) || !find(right, distance_of_all_paths))
            {
                return false;
            }
        }
        return is_visited;
    }
    Node *tree_depth_search (QMap <int, Node*>& distance_of_all_paths)
    {

        int count_of_nodes = 0;
        QMap <int, Node*>::iterator iter;
        QMap <int, Node*>::iterator copy_iter;
        Node *previous_node;
        Node *depth_of_the_tree;
        bool is_tree_macked = false;

        depth_first_search_of_one_way(count_of_nodes, distance_of_all_paths);
        iter = distance_of_all_paths.end();
        copy_iter = distance_of_all_paths.end();
        --iter;
        --copy_iter;
        do
        {

            //copy_iter = distance_of_all_paths.begin();
            //while (!is_operator(iter.value()->value))
           // {
                if (iter != distance_of_all_paths.end())
                {
                    --iter;
                    if (iter.value()->left == copy_iter.value() || iter.value()->right == copy_iter.value())
                    {
                        previous_node = iter.value();
                        int key = iter.key();
                        previous_node->depth_first_search_of_one_way(key, distance_of_all_paths);
                        copy_iter =iter;
                    }
                }

          //  }

          /*  iter = distance_of_all_paths.end();
            //copy_iter = distance_of_all_paths.begin();
            --iter;*/



           /* is_tree_macked = is_all_nodes_visited(distance_of_all_paths);

        }
        while (!is_tree_macked);

        depth_of_the_tree = distance_of_all_paths.last();

        return depth_of_the_tree;
    }*/



    //представление нотаций
    void preOrder(Node *part_of_tree)
    {
        if (part_of_tree != nullptr)
        {
            cout << qPrintable(part_of_tree->value);
            preOrder(part_of_tree->left);
            preOrder(part_of_tree->right);
        }
    }

    void inOrder(Node *part_of_tree)
    {
        if (part_of_tree != nullptr)
        {
            inOrder(part_of_tree->left);
            cout << qPrintable(part_of_tree->value);
            inOrder(part_of_tree->right);
        }
    }

    void postOrder(Node *part_of_tree)
    {
        if (part_of_tree != nullptr)
        {
            postOrder(part_of_tree->left);
            postOrder(part_of_tree->right);
            cout << qPrintable(part_of_tree->value);
        }
    }
};

//чтение из файла
void read_file (QMap<QString, QString>& data, QString way)
{
    QString str; //создаем объект класса QString для хранения строки из файла
    QFile file (way); //создаем объект класса QFile
    QStringList list; //объект класса QStringList для хранения подстрок текущей строки файла

    //если возможно открыть файл для чтения...
    if (file.open(QIODevice::ReadOnly))
    {
        //до тех пор, пока не достигли конца файла...
        while(!file.atEnd())
        {
            str=str+file.readLine(); //сохраняем в объект str текущую строку из файла
            list = str.split( QRegExp("\\s+")); //разбиваем текущую строку файла на подстроки и сохраняем их в контейнере list
            data.insert(list[0], list[1]); //добавляем в словарь полученные подстроки
            str = ""; //очищаем объект str для хранения следующей строки
        }
        file.close(); //закрываем файл
    }
}


int main(int argc, char *argv[])
{
        QStack <Node*> stack;
        QMap <int, Node*> distance_of_all_paths;
        QMap <int, Node*> all_nodes;
        QMap <int, Node*> visit;
        QMap <int, Node*> visit1;
        QStack <Node*> stack1;
        QStack <Node*> stack2;
        QMap <QString, QString> variables;
        QMap <QString, QString> cost;
        int count  = -1;
        int sum = 0;
        //Создаем дерево
        //Node tree (*tree.expression_tree_from_postfix("2 2 / +", stack, all_nodes));

        //QList <Error> errors;
      //  QMap <int, Node*> distance_of_all_paths;
        //int count_of_nodes = 0;
        read_file(variables, "C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/variables.txt");
        read_file(cost, "C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/cost.txt");
        //Создаем дерево
        Node tree (*tree.expression_tree_from_postfix("a +? b + 2 /", stack, all_nodes));
        Node depth_of_the_tree(*tree.depth_first_search(all_nodes, visit, count, stack1));
        sum = depth_of_the_tree.sum_of_operations(visit, variables, cost);
        //tree.depth_first_search(count_of_nodes ,distance_of_all_paths);
       // depth_of_the_tree = tree.tree_depth_search(distance_of_all_paths);

        //Traversal Operation on expression tree
        cout << "\nIn-Order Traversal :   ";
        tree.inOrder(stack[0]);

        cout << "\nPre-Order Traversal :  ";
        tree.preOrder(stack[0]);

        cout << "\nPost-Order Traversal : ";
        tree.postOrder(stack[0]);
        return 0;
}
