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

//класс, содержащий данные об одном узле дерева
class Node
{

    QString value; //родитель узла
    Node* right; //правая ветвь
    Node* left; //левая ветвь

public:
    //конструктор по-умолчанию
    Node ()
    {
        this->value = nullptr;
        this->right = nullptr;
        this->left = nullptr;
    }

    //конструктор с параметрами
    Node (QString value, Node  *right, Node  *left)
    {
        this->value = value;
        this->right = right;
        this->left = left;
    }

    //конструктор только с одним параметром
    Node (QString value)
    {
        this->value = value;
        this->right = nullptr;
        this->left = nullptr;
    }

    //проверка того, что подстрока является оператором
    bool is_operator (QString substr_of_expression)
    {
        if (substr_of_expression == "/" || substr_of_expression == "*" || substr_of_expression == "+" || substr_of_expression == "-"
                || substr_of_expression == "-?" || substr_of_expression == "-?") //если подстрока удовлетворяет данному условию...
        {
            return true;// вернуть признак того, что подстрока - оператор
        }

        return false;// иначе, вернуть прихнак того, что подстрока - операнд
    }

    //построение дерева из обратной польской записи
    Node *expression_tree_from_postfix(QString postfix_notation, QStack<Node*>& stack)
    {
        QString substr; //строка, хранящая текущую подстроку выражения в обратной польской записи
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
        list = postfix_notation.split( QRegExp("\\s+")); //разбиваем выражение в обратной польской записи на подстроки и сохраняем их в контейнере list
        substr = list[0]; //запоминаем в переменной substr первую подстроку выражения в обратной польской записи
        index_of_current_substr = 1; //переменная, хранящая индекс текущей подстроки в контейнере list становится равной 1

        for (int i = 1; substr != NULL && index_of_current_substr <= size_of_expression; i++) //для каждой подстроки выражения и пока не дошли до конца
        {//и индекс текущей подстроки в контейнере list не больше количества операторов и операндов в выражении...

            if (!is_operator(substr)) //если подстрока - оператор...
            {
               // part_of_tree = new Node; //создать элемент типа Node
                Node *part_of_tree = new Node (substr); //инициализируем объект при помощи конструктора с одним параметром
                stack.push(part_of_tree); //добавить текущий элемент в стек
            }

            else //иначе, если текущая подстрока - операнд...
            {
                right_branch = stack.pop(); //выгрузить из стека текущий элемент и запомнить в перемнную right_branch
                left_branch = stack.pop(); //выгрузить из стека следующий за текущий элемент в переменную left_branch
                Node *part_of_tree = new Node (substr, right_branch, left_branch); //инициализируем объект при помощи конструктора с параметрами
                stack.push(part_of_tree); //добавить текущий элемент в стек
            }

            if (index_of_current_substr != size_of_expression) //если индекс текущей подстроки в контейнере list не равен больше количеству операторов и операндов в выражении...
                substr = list[i]; //достать из контейнера list  следующую подстроку и запомнить ее в перемнную substr

            index_of_current_substr++; //инкрементировать значение индекса текущей подстроки
        }
        return stack[0]; //вернуть элемент начала стека
    }

    //агоритм поиска в глубину
    int depth_first_search()
    {
        int sum_of_value_of_operations = 0;

        if (left != nullptr)
        {
            sum_of_value_of_operations += left->depth_first_search();
        }

        if (right != nullptr)
        {
            sum_of_value_of_operations += right->depth_first_search();
        }
        return sum_of_value_of_operations;
    }

    //представление нотаций
    void preOrder(Node *part_of_tree)
    {
        if (part_of_tree != NULL)
        {
            cout << qPrintable(part_of_tree->value);
            preOrder(part_of_tree->left);
            preOrder(part_of_tree->right);
        }
    }

    void inOrder(Node *part_of_tree)
    {
        if (part_of_tree != NULL)
        {
            inOrder(part_of_tree->left);
            cout << qPrintable(part_of_tree->value);
            inOrder(part_of_tree->right);
        }
    }

    void postOrder(Node *part_of_tree)
    {
        if (part_of_tree != NULL)
        {
            postOrder(part_of_tree->left);
            postOrder(part_of_tree->right);
            cout << qPrintable(part_of_tree->value);
        }
    }
};

//чтение из файла
void read_file (QMap<QString, QString> data)
{
    QString str; //создаем объект класса QString для хранения строки из файла
    QFile file ("C:/Users/dinar/OneDrive/Desktop/operations_calc/build-operations_calc-Desktop_Qt_5_13_1_MinGW_64_bit-Debug/test.txt"); //создаем объект класса QFile
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

        //Создаем дерево
        Node tree (*tree.expression_tree_from_postfix("1 2 + 3 a + + b c - + b * 2 / c + 2 + a +", stack));

        //Traversal Operation on expression tree
        cout << "\nIn-Order Traversal :   ";
        tree.inOrder(stack[0]);

        cout << "\nPre-Order Traversal :  ";
        tree.preOrder(stack[0]);

        cout << "\nPost-Order Traversal : ";
        tree.postOrder(stack[0]);
        return 0;
}
