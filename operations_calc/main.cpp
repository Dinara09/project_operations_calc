#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include <QtGlobal>
#include <QFile>
#include <QMap>
#include <QStack>
#include <QTextStream>
using namespace std;

//класс для хранения инфромации об ошибках
class Error
{
    int code_of_error; //код ошибки
    int column_of_error; //столбец с ошибкой
    QString information_of_error; //причина ошибки

public:

    //конструктор по-умолчанию
    Error ()
    {
        this->code_of_error = NULL;
        this->column_of_error = NULL;
        this->information_of_error = nullptr;
    }

    //конструктор с параметрами
    Error (int code_of_error, int column_of_error, QString information_of_error)
    {
        this->code_of_error = code_of_error;
        this->column_of_error = column_of_error;
        this->information_of_error = information_of_error;
    }

    //получение данных о поле code_of_error
    int get_code_error_code ()
    {
        return this->code_of_error; //вернуть содержимое  поля code_of_error
    }

    //получение данных о поле column_of_error
    int get_line_of_error ()
    {
        return this->column_of_error; //вернуть содержимое  поля column_of_error
    }

    //получение данных о поле information_of_error
    QString get_information_of_error ()
    {
        return this->information_of_error; //вернуть содержимое  поля information_of_error
    }
};

//проверка того, что подстрока является оператором
bool is_operator (QString substr_of_expression)
{
    //если подстрока удовлетворяет данному условию...
    if (substr_of_expression == "/" || substr_of_expression == "*" || substr_of_expression == "+" || substr_of_expression == "-"
            || substr_of_expression == "-?" || substr_of_expression == "+?")
    {
        return true;// вернуть признак того, что подстрока - оператор
    }

    return false;// иначе, вернуть прихнак того, что подстрока - операнд
}

//класс, содержащий данные об одном узле дерева
class Node
{

    QString value; //узел
    Node* right; //правая вершина данного узла
    Node* left; //левая вершина данного узла
    QString type_of_node; //тип узла

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

    //проверка на количество операторов выражении
    bool validation_of_quantity(QList <Error>& errors, QStringList& list)
    {
        int count_of_operation = 0; //создать счетчик для подсчета количества операторов и обнулить его
        bool find_error = false; //признак того, что была найдена ошибка

        //пока не дошли до конца выражения...
        for (int i = 0; i < list.size(); i++)
        {
            //если текущий элемент оператор...
            if (is_operator(list[i]))
            {
                count_of_operation++; //увеличиваем счетчик
            }
        }

        //если счетчик меньше 1....
        if (count_of_operation < 1)
        {
            Error few_operations (0, count_of_operation, "too few operations"); //создать объект класса Error и запомнить информацию о малом количестве операторов
            errors.append(few_operations); //добавить ошибку в контейнер
            find_error = true; //запомнить появления ошибки
        }

        //иначе если счетчик больше 10...
        else if (count_of_operation > 10)
        {
            Error many_operations (1, count_of_operation, "too many operations"); //создать объект класса Error запомнить информацию о превыщающем количестве операторов
            errors.append(many_operations); //добавить ошибку в контейнер
            find_error = true; //запомнить появления ошибки
        }

        return  find_error; //вернуть признак появления ошибки
    }

    //проверка на содержание в строке знака операции
    bool is_contains_operation (QString str)
    {
        bool is_contains = false; //создать переменную о содержании знака и запомнить в ней false

        //если содержится "+"...
        if (str.contains("+", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }
        //если содержится "-"...
        else if (str.contains("-", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }
        //если содержится "/"...
        else if (str.contains("/", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }
        //если содержится "*"...
        if (str.contains("*", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }
        //если содержится "-?"...
        if (str.contains("-?", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }
        //если содержится "+?"...
        if (str.contains("+?", Qt:: CaseSensitive))
        {
            is_contains = true; //запомнить true
        }

        return is_contains; //вернуть признак содержания
    }

    //проверка на содержание переменной в контейнере
    bool is_in_the_container (QString character, QMap<QString, QString>& data)
    {
        QMap <QString, QString>::iterator iter; // итератор для контейнера
        bool is_find = false; //создать переменную о признаки нахождения элемента в контейнере и запомнить в ней false

        //для всех элементов контейнера и пока не дошли до конца контейнера...
        for(iter = data.begin(); iter != data.end(); ++iter)
        {
            //если текущий элемент найден...
            if (iter.key() == character)
            {
                is_find = true; //запомнить true
            }
        }

        return is_find; //вернуть признак нахождения элемента в контейнере
    }

    //проверка на валидность содержимого выражения
    void is_valid_character (QList <Error>& errors, QStringList& list, QMap<QString, QString>& variables, QMap<QString, QString>& cost)
    {
        QRegExp reg_const_character ("\\d*,?\\d*"); //регулярное выражение для проверки константной переменной
        QRegExp reg_sequence_of_variables ("[a-z][a-z]+"); //регулярное выражение для проверки последовательности переменных
        QRegExp reg_variable("[a-z]"); //регулярное выражение для проверки переменной

        //для всех элементов строки и пока не дошли до конца...
        for (int i = 0; i < list.size(); i++)
        {
            //если текущий элемент не оператор и текущий элемент содержит знак операции...
            if (!is_operator (list[i]) && is_contains_operation(list[i]))
            {
                Error missing_space (2, i, "missing space between arguments"); //создать объект класса Error и запомнить информацию о пропуске пробела
                errors.append(missing_space); //добавить ошибку в контейнер
            }
            //иначе если текущий элемент не оператор и не содержится в контейнере с переменными и не соответствует констатной переменной и соответсвует последовательности переменных...
            else if (!is_operator(list[i]) && !is_in_the_container(list[i], variables) && !reg_const_character.exactMatch(list[i]) && reg_sequence_of_variables.exactMatch(list[i]))
            {
                Error missing_space (2, i, "missing space between arguments"); //создать объект класса Error и запомнить информацию о пропуске пробела
                errors.append(missing_space); //добавить ошибку в контейнер
            }
            //иначе если текущий элемент не оператор и не содержится в контейнере с переменными  и не соответствует констатной переменной и не соответсвует последовательности переменных...
            else if (!is_operator(list[i]) && !is_in_the_container(list[i], variables) && !reg_const_character.exactMatch(list[i]) && !reg_sequence_of_variables.exactMatch(list[i]))
            {
                Error invalid_characters (3, i, "invalid characters in expression"); //создать объект класса Error и запомнить информацию о недопустимом символе
                errors.append(invalid_characters); //добавить ошибку в контейнер
            }
            //иначе если текущий элемент не оператор и соответствует переменной и не содержится в контейнере с переменными...
            else if (!is_operator(list[i]) && reg_variable.exactMatch(list[i]) && !is_in_the_container(list[i], variables))
            {
                Error no_operand_information (4, i, "no information about variable"); //создать объект класса Error и запомнить информацию об отсутствие информации о перемнной
                errors.append(no_operand_information); //добавить ошибку в контейнер
            }
            //иначе если текущий элемент оператор и не содержится в контейнере с весами...
            else if (is_operator(list[i]) && !is_in_the_container(list[i], cost))
            {
                Error no_operator_information (5, i, "no information about operator"); //создать объект класса Error и запомнить информацию об отсутствие информации о операции
                errors.append(no_operator_information); //добавить ошибку в контейнер
            }
        }
    }

    //построение дерева из обратной польской записи
    Node *expression_tree_from_postfix(QString postfix_notation, QStack<Node*>& stack, QMap <int, Node*>& all_nodes, QList <Error>& errors, QMap<QString, QString>& variables, QMap<QString, QString>& cost )
    {
        QString current_substr_expression; //строка, хранящая текущую подстроку выражения в обратной польской записи
        Node *peek; //объект класса Node для запоминанния верхнего элемента стека
        Node *part_of_tree;
        Node  *right_branch, *left_branch; //левая и правая вершины текущего узла
        QStringList expression_elements; //контейнер, хранящий подстроки выражения в обратной польской записи
        int index_of_current_substr; //индекс текущей подстроки в контейнере list
        int size_of_expression = 0; //количество операторов и операндов в выражении

        //для всех символов строки и пока не дошли до конца...
        for (int i = 0; i < postfix_notation.size(); i++)
        {
            //если текущий символ - пробел...
            if (postfix_notation[i] == ' ')
            {
                size_of_expression++; //инкрементируем значение операндов и операторов
            }
        }
        size_of_expression++; //инкрементируем значение операндов и операторов (в итоге получаем значение операторов и операндов в строке)

        expression_elements = postfix_notation.split(QRegExp("\\s+")); //разбиваем выражение в обратной польской записи на подстроки и сохраняем их в контейнере expression_elements
        current_substr_expression = expression_elements[0]; //запоминаем в переменной current_substr_expression первую подстроку выражения в обратной польской записи
        index_of_current_substr = 1; //переменная, хранящая индекс текущей подстроки в контейнере expression_elements становится равной 1
        validation_of_quantity(errors, expression_elements); //проверка валидности количества операторов
        is_valid_character(errors, expression_elements, variables, cost); //проверка валидности содержимого выражения

        //если контейнер с ошибками пуст...
        if (errors.empty())
        {
            //для каждой подстроки выражения и пока не дошли до конца и индекс текущей подстроки в контейнере expression_elements не больше количества операторов и операндов в выражении...
            for (int i = 1; current_substr_expression != nullptr && index_of_current_substr <= size_of_expression; i++)
            {
                //если подстрока - операнд...
                if (!is_operator(current_substr_expression))
                {
                    Node *part_of_tree = new Node (current_substr_expression); //инициализируем объект при помощи конструктора с одним параметром
                    stack.push(part_of_tree); //добавить текущий элемент в стек
                    all_nodes.insert(i-1, part_of_tree); //добавить текущий элемент в контейнер
                }

                //иначе, если текущая подстрока - операнд...
                else
                {
                    //если элемент равен "-?" или "+?"...
                    if (current_substr_expression == "-?" || current_substr_expression == "+?")
                    {
                        left_branch = stack.pop(); //выгрузить из стека текущий элемент и запомнить в переменную right_branch
                        part_of_tree = new Node (current_substr_expression, nullptr, left_branch, nullptr); //инициализируем объект при помощи конструктора с параметрами
                    }

                    //иначе...
                    else
                    {
                        right_branch = stack.pop(); //выгрузить из стека текущий элемент и запомнить в переменную right_branch
                        if (stack.empty())
                        {
                            Error missin_number_of_operands (6, i, "missing number of operands to perform the operation"); //создать объект класса Error и
                                                                                            //запомнить информацию об несоответствующем количестве операторов
                            errors.append(missin_number_of_operands); //добавить ошибку в контейнер

                        }
                        else
                        {
                            left_branch = stack.pop(); //выгрузить из стека следующий за текущий элемент в переменную left_branch
                            part_of_tree = new Node (current_substr_expression, right_branch, left_branch, nullptr); //инициализируем объект при помощи конструктора с параметрами
                        }
                    }


                    stack.push(part_of_tree); //добавить текущий элемент в стек
                    all_nodes.insert(i-1, part_of_tree); //добавить текущий элемент в контейнер с узлами дерева
                }

                //если индекс текущей подстроки в контейнере expression_elements не равен больше количеству операторов и операндов в выражении...
                if (index_of_current_substr != size_of_expression)
                {
                    current_substr_expression = expression_elements[i]; //достать из контейнера expression_elements  следующую подстроку и запомнить ее в переменную current_substr_expression
                }

                index_of_current_substr++; //инкрементировать значение индекса текущей подстроки
            }
            peek = stack[0]; //запомнить элемент начала стека
        }

        //иначе...
        if (!errors.empty())
        {
            peek = new Node (); //запомнить в переменной для хранения верхнего элемента стека пустой узел
        }

        return peek; //вернуть верхний элемент стека
    }

    //поиск текущего узла дерева в контейнере, хранящем узлы дерева
    int search_current_node (QMap <int, Node*> &visit)
    {
        QMap<int, Node*>::iterator iter; //создаем итератор

        //для всех элементов контейнера и пока не дошли до конца контейнера...
        for (iter = visit.begin(); iter != visit.end(); ++iter)
        {
            //если текущей элемент контейнера равен текущему узлу дерева...
            if (iter.value() == this)
            {
                return iter.key(); //вернуть ключ этого элемента
            }
        }
        return NULL; //иначе если текущий узел дерева не найден в контейнере, вернуть NULL
    }

    //поиск глубины дерева
    Node* depth_first_search(QMap <int, Node*>& all_nodes, QMap <int, Node*> &visit, int &count, QStack <Node*>& stack, QMap<QString, QString>& variables, QMap<QString, QString>& cost, QVector <int>& sum_of_operation, QStack <Node*>& stack1)
    {
        //пока не посетили все узлы дерева...
        while (all_nodes.size() != visit. size())
        {
            count++; //увеличиваем счетчик, указывающий на расстояние от вершины дерева

            //если существует левая вершина текущего узла и вершина не была посещена...
            if (this->left != nullptr && this->left->search_current_node(visit) == NULL)
            {
                //если текущий узел не был посещен...
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this); //отметить текущий узел посещенным
                }

                stack.push(this); //добавить текущий узел в стек
                return left->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, stack1); //вызвать функцию для левой вершины данного узла
            }

            //если существует правая вершина текущего узла и вершина не была посещена...
            if (this->right != nullptr && this->right->search_current_node(visit) == NULL)
            {
                //если текущий узел не был посещен...
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this); //отметить текущий узел посещенным
                }

                stack.push(this); //добавить текущий узел в стек
                return right->depth_first_search(all_nodes, visit, count, stack, variables, cost, sum_of_operation, stack1); //вызвать функцию для правой вершины данного узла
            }

            //если не существует ни левой, ни правой вершины текущего узла...
            if (this->left == nullptr && this->right == nullptr)
            {
                //если текущий узел не был посещен...
                if (this->search_current_node(visit) == NULL)
                {
                    visit.insertMulti(count, this); //отметить текущий узел посещенным
                    this->type_of_node = this->recognize_node_type(variables); //определить тип текущего узла и запомнить его

                    //если у родителя текущего узла есть левая вершина с определенной приоритетностью и нет правой...
                    if (recognize_parent_of_node(all_nodes, this)->left->type_of_node != nullptr && recognize_parent_of_node(all_nodes, this)->right == nullptr)
                    {
                        sum_of_operation.prepend(recognize_parent_of_node(all_nodes, this)->sum_of_current_operation(variables, cost)); //определить стоимость операции и сохранить в вектор

                    }

                    //иначе если у родителя текущего узла есть и правая и левая вершины с определенными приоритетностями...
                    else if (recognize_parent_of_node(all_nodes, this)->left->type_of_node != nullptr && recognize_parent_of_node(all_nodes, this)->right->type_of_node != nullptr)
                    {
                        sum_of_operation.prepend(recognize_parent_of_node(all_nodes, this)->sum_of_current_operation(variables, cost)); //определить стоимость операции и сохранить в вектор

                        //если стек1 не пустой...
                        if (!stack1.empty())
                        {
                            stack1.pop(); //удалить верхний элемент
                        }
                    }

                    //иначе...
                    else
                    {
                        stack1.push(recognize_parent_of_node(all_nodes, this)); //загрузить в стек1 текущий элемент
                    }

                    //если стек1 не пустой...
                    if (!stack1.empty())
                    {
                        Node* element_of_stack1; //создать объект класса Node
                        element_of_stack1 = stack1.top(); //сохранить в него верхний элемент стека

                        //если у левой и правой вершины сохраненного элемента определены типы...
                        if (element_of_stack1->left->type_of_node != nullptr && element_of_stack1->right->type_of_node != nullptr)
                        {
                            sum_of_operation.prepend(element_of_stack1->sum_of_current_operation(variables, cost)); //определить стоимость текущей операции и сохранить в вектор
                            stack1.pop(); //извлечь из стека верхний элемент
                        }
                    }

                    //если стек не пустой...
                    if (!stack.empty())
                    {
                        Node*peek; //создать объект класса Node
                        peek = stack.pop(); //сохранить в него элемент вершины стека
                        int key; //создать переменную для хранения значения ключа элемента контейнера
                        key = peek->search_current_node(visit); //сохранить в нее значение ключа извлеченного элемента

                        //если правая вершина элемента контейнера с данным ключом существует...
                        if (visit.value(key)->right != nullptr)
                        {
                            return visit.value(key)->right->depth_first_search(all_nodes, visit, key, stack, variables, cost, sum_of_operation, stack1); //вызвать функцию для правой вершины извлеченного элемента
                        }


                        //иначе если значение ключа не равно 0...
                        else if (visit.key(peek) != 0)
                        {
                            if (!stack.empty())
                            {
                                peek = stack.pop(); //извлечь элемент вершины стека
                                key = peek->search_current_node(visit); //сохранить в переменную для хранения значения ключа элемента значение ключа извлеченного элемента
                                return visit.value(key)->right->depth_first_search(all_nodes, visit, key, stack,variables, cost, sum_of_operation,stack1); //вызвать функцию для правой вершины извлеченного элемента
                            }

                        }
                    }
                }


            }
        }
        //если тип корня дерева еще не определен...
        if (all_nodes.last()->type_of_node == nullptr)
        {
             Node* peek = all_nodes[all_nodes.size() -1]; //запомнить его в объект класса Node
             sum_of_operation.prepend(peek->sum_of_current_operation(variables, cost)); //определить стоимость операции и сохранить в стек
        }

        return visit.last(); //вернуть последний элемент контейнера
     }

    //определение родителя текущего узла
    Node* recognize_parent_of_node (QMap <int, Node*> &visit, Node* current_node)
    {
        QMap <int, Node*>::iterator iter; // итератор для контейнера, хранящего узлы дерева
        Node* node; //объект класса Node

        //для всех элементов контейнера и пока не дошли до конца контейнера...
        for(iter = visit.begin(); iter != visit.end(); ++iter)
        {
            node = iter.value(); //сохранить в пееременной объекта класса Node текущий элемент контейнера

            //если левая или правая вершина данного элемента равна текущему узлу...
            if (iter.value()->right == current_node || iter.value()->left == current_node)
            {
                return iter.value(); //вернуть данный элемент контейнера
            }
        }

        return nullptr; //если не найден родитель текущего узла, вернуть nullptr
    }

    //определение типа константы
    QString recognize_number_type ()
    {
        int whole_part; //создать переменную, хранящую целую часть
        int fractional_part = NULL; //создать переменную, хранящую дробную часть
        bool ok;
        QStringList parts_of_number; //создать объект класса QStringList

        parts_of_number = this->value.split(","); //разделить текущую строку и сохранить в parts_of_number
        whole_part = parts_of_number[0].toInt(& ok, 10); //сохранить первый элемент parts_of_number в целую часть

        //если количество элементов в parts_of_number не равно 1...
        if (parts_of_number.size() != 1)
        {
            fractional_part = parts_of_number[1].toInt(& ok, 10); //сохранить второй элемент parts_of_number в дробную часть
        }

        //если дробная часть отсутствует...
        if (fractional_part == NULL)
        {
            return "int"; //вернуть строку "int"
        }

        //иначе если целая и дробная часть соответствует условию типа данных double
        else if ((whole_part-1 >  2147483646 && fractional_part > 0) || (whole_part+1 <  -2147483647 && fractional_part < 0))
        {
           return "double"; //вернуть строку "double"
        }

        //иначе...
        else
            return "float"; // вернуть строку "float"
    }

    //определение типа узла
    QString recognize_node_type (QMap<QString, QString>& variables)
    {
        QRegExp reg_const_character("\\d*,?\\d*"); //регулярное выражение для проверки константной переменной
        QString type_of_node; //создать строку для хранения типа узла
        QMap<QString, QString>::iterator iter; //создать итератор

        //если текущий узел - оператор...
        if (is_operator(this->value))
        {
            type_of_node = this->type_of_node; //запомнить в строку, хранящую тип узла значения поля type_of_node
        }

        //иначе...
        else
        {
            //если переменная соответствует регулярному выражению...
            if (reg_const_character.exactMatch(this->value))
            {
                type_of_node = this->recognize_number_type(); //запомнить в строку, хранящую тип узла возвращаемое значение функции recognize_number_type
            }

            //иначе...
            else
            {
                 type_of_node = variables.find(this->value).value(); //запомнить в строку, хранящую тип узла соответствующее значение из контейнера с переменными
            }
        }

        this->type_of_node = type_of_node; //сохранить в поле type_of_node полученную строку с типом текущего узла
        return type_of_node; //вернуть полученную строку с типом узла
    }

    //определение приоритетного типа
    QString priority_recognition (QString type_of_left_node, QString type_of_right_node, QMap<QString, QString>& cost, int& cost_of_conversion_type)
    {
        QString priority_type; //создать строку, хранящую тип приоритетности
        bool ok;

        //если обе вершины имеют тип "int"...
        if (type_of_left_node == "int" && type_of_right_node == "int")
        {
            priority_type = "int"; //запомнить в строке, хранящей  тип приоритетности "int"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        //иначе если одна из вершин имеет тип "int" и другая "float"...
        else if ((type_of_left_node == "int" && type_of_right_node == "float") || (type_of_left_node == "float" && type_of_right_node == "int"))
        {
            priority_type = "float"; //запомнить в строке, хранящей  тип приоритетности "float"
            cost_of_conversion_type = cost.find("intTOfloat").value().toInt(& ok, 10); //запомнить в стоимости конвертации значение из файла с весами
        }

        //иначе если обе вершины имеют тип "float"...
        else if (type_of_left_node == "float" && type_of_right_node == "float")
        {
            priority_type =  "float"; //запомнить в строке, хранящей  тип приоритетности "float"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        //иначе если одна из вершин имеет тип "float" и другая "double"...
        else if ((type_of_left_node == "float" && type_of_right_node == "double") || (type_of_left_node == "double" && type_of_right_node == "float"))
        {
            priority_type =  "float"; //запомнить в строке, хранящей  тип приоритетности "float"
            cost_of_conversion_type = cost.find("floatTOdouble").value().toInt(& ok, 10); //запомнить в стоимости конвертации значение из файла с весами
        }

        //иначе если одна из вершин имеет тип "float" и другая "double"...
        else if ((type_of_left_node == "int" && type_of_right_node == "double") || (type_of_left_node == "double" && type_of_right_node == "int"))
        {
            priority_type =  "float"; //запомнить в строке, хранящей  тип приоритетности "float"
            cost_of_conversion_type = cost.find("intTOdouble").value().toInt(& ok, 10); //запомнить в стоимости конвертации значение из файла с весами
        }

        //иначе если обе вершины имеют тип "double"...
        else if (type_of_left_node == "double" || type_of_right_node == "double")
        {
            priority_type =  "double"; //запомнить в строке, хранящей  тип приоритетности "double"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        //иначе если левая вершина имеет тип "int" и левая ""...
        else if (type_of_left_node == "int" && type_of_right_node == "")
        {
            priority_type = "int"; //запомнить в строке, хранящей  тип приоритетности "int"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        //иначе если левая вершина имеет тип "float" и левая ""...
        else if (type_of_left_node == "float" && type_of_right_node == "")
        {
            priority_type = "float"; //запомнить в строке, хранящей  тип приоритетности "float"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        //иначе если левая вершина имеет тип "double" и левая ""...
        else if (type_of_left_node == "double" && type_of_right_node == "")
        {
            priority_type =  "double"; //запомнить в строке, хранящей  тип приоритетности "double"
            cost_of_conversion_type = 0; //запомнить в стоимости конвертации значение нуля
        }

        return priority_type; //вернуть строку, хранящую тип приоритетности
    }

    //стоимость текущей операции
    int sum_of_current_operation(QMap<QString, QString>& variables, QMap<QString, QString>& cost)
    {
        QString type_of_left_node; //создать строку, хранящей тип левой вершины
        QString type_of_right_node; //создать строку, хранящей тип правой вершины
        QString priority_type; //создать строку, хранящей приоритетный тип
        QString cost_of_node; //создать строку, хранящей стоимость узла
        int cost_of_conversion_type = 0; //создать переменную, хранящую стоимость конвертации типа
        bool ok;

        //если существует левая вершина текущего узла...
        if (this->left != nullptr)
        {
            //если текущий узел не оператор...
            if (!is_operator(this->left->value))
            {
                type_of_left_node = this->left->recognize_node_type(variables); //вызываем функцию определения типа узла для левой вершины и запоминаем в type_of_left_node
            }

            //иначе
            else
            {
                type_of_left_node = this->left->type_of_node; //сохраняем в type_of_left_node значение поля type_of_node левой вершины
            }
        }

        //если существует правая вершина текущего узла...
        if (this->right != nullptr)
        {
            //если текущий узел не оператор...
            if (!is_operator(this->right->value))
            {
                type_of_right_node = this->right->recognize_node_type(variables); //вызываем функцию определения типа узла для правой вершины и запоминаем в type_of_right_node
            }

            //иначе...
            else
            {
                type_of_right_node = this->right->type_of_node; //сохраняем в type_of_right_node значение поля type_of_node правой вершины
            }
        }

        priority_type = priority_recognition(type_of_left_node, type_of_right_node, cost, cost_of_conversion_type); //определяем приоритетный тип
        this->type_of_node = priority_type; //запоминаем в поле type_of_node текущего узла приоритетный тип
        cost_of_node = cost.find(this->value).value(); // определяем стоимость операции
        return cost_of_node.toInt(& ok, 10) + cost_of_conversion_type; //возвращаем стоимость
    }

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

//чтение файла с выражением в обратной польской записи
QString read_expression (QString way_to_input_file)
{
    QString content_of_line_file; //создаем объект класса QString для хранения строки из файла
    QFile file (way_to_input_file); //создаем объект класса QFile

    //если возможно открыть файл для чтения...
    if (file.open(QIODevice::ReadOnly))
    {
        //до тех пор, пока не достигли конца файла...
        while(!file.atEnd())
        {
            content_of_line_file=content_of_line_file+file.readLine(); //сохраняем в объект str текущую строку из файла
        }
        file.close(); //закрываем файл
    }
    return content_of_line_file;
}

//чтение из файла с перемеменными и весами
void read_file (QList <Error>& errors, QMap<QString, QString>& data, QString way_to_input_file, QString name_of_file)
{
    QString content_of_line_file; //создаем объект класса QString для хранения строки из файла
    QFile file (way_to_input_file); //создаем объект класса QFile
    QStringList expression_elements; //объект класса QStringList для хранения подстрок текущей строки файла
    QRegExp reg_variable("[a-z]"); //регулярное выражение для проверки переменной
    QRegExp reg_number("\\d+"); //регулярное выражение для проверки числа

    //если возможно открыть файл для чтения...
    if (file.open(QIODevice::ReadOnly))
    {
        //до тех пор, пока не достигли конца файла...
        while(!file.atEnd())
        {
            content_of_line_file=content_of_line_file+file.readLine(); //сохраняем в объект content_of_line_file текущую строку из файла
            expression_elements = content_of_line_file.split( QRegExp("\\s+")); //разбиваем текущую строку файла на подстроки и сохраняем их в контейнере list

            //если первый элемент не соответствует переменной и второй элемент не строка "int" или "float" или "double" и текущий файл - файл с переменными...
            if (!(reg_variable.exactMatch(expression_elements[0]) && (expression_elements[1] == "int" || expression_elements[1] == "float" || expression_elements[1] == "double")) && name_of_file == "variables")
            {
                Error error_in_variables_file (7, 0, "invalid file format with variables"); //создать объект класса Error и запомнить информацию о неверном формате файла с перемнными
                errors.append(error_in_variables_file);
            }

            //иначе если первый элемент не соответствует оператору или строке "intTOfloat" или ""intTOdouble" или "floatTOdoble" и второй элемент не число и текущий файл - файл с весами...
            else if (!((is_operator(expression_elements[0]) || expression_elements[0] == "intTOfloat" || expression_elements[0] == "intTOdouble" || expression_elements[0] == "floatTOdoble") && reg_number.exactMatch(expression_elements[1])) && name_of_file == "cost")
            {
                Error error_in_cost_file (8, 0, "invalid file format with cost"); //создать объект класса Error и запомнить информацию о неверном формате с весами
                errors.append(error_in_cost_file);
            }

            //иначе...
            else
            {
                data.insert(expression_elements[0], expression_elements[1]); //добавляем в словарь полученные подстроки
                content_of_line_file = ""; //очищаем объект content_of_line_file для хранения следующей строки
            }
        }

        file.close(); //закрываем файл
    }
}

//запись результата в файл
void write_file (QList <Error>& errors, QString way_to_output_file, int sum)
{
    QFile file (way_to_output_file); //создаем объект класса QFile

    //если файл открыт для записи...
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file); //создаем объект класса QTextStream

        //если контейнер с ошибками не пуст...
        if (!errors.empty())
        {
            QString error_info; //создаем строку для хранения информации об ошибке

            for(int i = 0; i < errors.size(); i++)
            {
                Error error = errors[i]; //запоминаем в объкте класса Error текущий элемент контейнера с ошибками
                //запоминаем содерщимое объекта в строку
                error_info = "code of error: "+QString::number(error.get_code_error_code())+"\ncolumn of error: "+QString::number(error.get_line_of_error())+"\ninformation of error: "+error.get_information_of_error();
                out << error_info << endl; //выгружаем в файл строку
            }
        }

        //иначе...
        else
        {
            QString result; //создаем строку для хранения результата подсчета
            result = "result is "+QString::number(sum); //сохраняем в нее результат
            out << result << endl; //выгружаем в файл
        }

        file.close(); //закрываем файл
    }
}

int main(int argc, char *argv[])
{
    /*QString way_to_expression = argv[1]; //путь к файлу с выражением
    QString way_to_variables_file = argv[2]; //путь к файлу с перемнными
    QString way_to_cost_file = argv[3]; //путь к файлу с весами операций
    QString way_to_result_file = argv[4]; // путь к выходному файлу*/

    QStack <Node*> stack; //стек для функции expression_tree_from_postfix
    QMap <int, Node*> distance_of_all_paths; //карта для хранения расстояния от вершины дерева до каждого узла
    QMap <int, Node*> all_nodes; //карта для хранения всех узлов дерева
    QMap <int, Node*> visit; //карта для посещенных узлов
    QList <Error> errors; //QList для хранения объектов класса Error
    QStack <Node*> stack1; //стек для функции depth_of_the_tree
    QStack <Node*> stack2; //стек для уже посещенных узлов функции depth_of_the_tree
    QMap <QString, QString> variables; //карта для хранения информации о переменных
    QMap <QString, QString> cost;  //карта для хранения информации о весах операций
    QVector <int> sum_operation; //вектор для хранения веса каждой операции
    int count  = -1; //счетчик растояний от вершины дерева функции depth_of_the_tree, значение равно -1
    int sum = 0; //сумма всех операций, значение равно 0
    //"C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/variables.txt"

    //считываем файл с переменными
    read_file(errors, variables, "C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/variables.txt", "variables");
    //считаем файл с весами
    read_file(errors, cost, "C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/cost.txt", "cost");

    //Создаем дерево
    Node tree (*tree.expression_tree_from_postfix(read_expression("C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/expression.txt"), stack, all_nodes, errors, variables, cost));

    //если стек для функции expression_tree_from_postfix не равен 1
    if (stack.size() != 1 && errors.empty())
    {
        Error few_oparators (9, stack.size(), "inappropriate number of operators"); //создать объект класса Error и запомнить информацию о нехватке операторов
        errors.append(few_oparators); //добавить ошибку в контейнер
    }

    //иначе...
    else
    {
        //если контейнер с ошибками пустой...
        if (errors.empty())
        {
            //вызвать функцию обхода в глубину
            Node depth_of_the_tree(*tree.depth_first_search(all_nodes, visit, count, stack1, variables, cost, sum_operation, stack2));

            //для каждого элемента вектора и пока не дошли до конца...
            for (int i = 0; i < sum_operation.size(); i++)
            {
                sum+=sum_operation[i]; //увеличивываем сумму всех операций, прибавляя текущее значение вектора
            }
        }
    }

    //записываем рузультаты в выходной файл
    write_file(errors, "C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/result.txt", sum);

    return 0;
}
