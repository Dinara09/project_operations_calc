#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include <QtGlobal>
#include <QFile>
#include <QMap>
using namespace std;

//ЗАМЕТКИ//
/*
str=str+file.readLine();                      ПОСТРОЧНОЕ ЧТЕНИЕ
*/

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


//стуктура, хранящая данные об одном узле в дереве
struct Node
{
    QString value; //родитель узла
    Node * right; //правая ветвь
    Node * left; //левая ветвь
};

QString postfix_expression; //создаем объект класса QString для хранения строки в обратной польской записи
int top = -1; //переменная для хранения индекса элемента в стеке
Node * stack[ 35 ]; //стек из элементов типа Node

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


//добавление в стек элемента
void push(Node *part_of_tree)
{
    top++; //икрементируем значение индекса элемента в стеке
    stack[top] = part_of_tree; //добавляем в стек текущий элемент
}

//извлечение из стека элемента
Node *pop()
{
    top--; //декрементируем значение индекса элемента в стеке
    return (stack[top + 1]); //получаем текущий элемент стека(эмелент, которого стал top+1)
}

//построение дерева из обратной польской записи
Node* expression_tree_from_postfix(QString postfix_notation)
{
    QString substr; //строка, хранящая текущую подстроку выражения в обратной польской записи
    Node *part_of_tree, *right_branch, *left_branch; //
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
            part_of_tree = new Node; //создать элемент типа Node
            part_of_tree->value = substr; //запомнить в поле value текущую подстроку
            part_of_tree->left = NULL; //запомнить в поле left значение NULL
            part_of_tree->right = NULL; //запомнить в поле right значение NULL
            push(part_of_tree); //добавить текущий элемент в стек
        }

        else //иначе, если текущая подстрока - операнд...
        {
            right_branch = pop(); //выгрузить из стека текущий элемент и запомнить в перемнную right_branch
            left_branch = pop(); //выгрузить из стека следующий за текущий элемент в переменную left_branch
            part_of_tree = new Node; //создать элемент типа Node
            part_of_tree->value = substr; //запомнить в поле value текущую подстроку
            part_of_tree->right = right_branch; //запомнить в поле right значение переменной right_branch
            part_of_tree->left = left_branch; //запомнить в поле left значение переменной left_branch
            push(part_of_tree); //добавить текущий элемент в стек
        }

        if (index_of_current_substr != size_of_expression) //если индекс текущей подстроки в контейнере list не равен больше количеству операторов и операндов в выражении...
            substr = list[i]; //достать из контейнера list  следующую подстроку и запомнить ее в перемнную substr

        index_of_current_substr++; //инкрементировать значение индекса текущей подстроки
    }
    return stack[0]; //вернуть элемент начала стека
}

//обходв глубину
int depth_first_search()
{

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
int main(int argc, char *argv[])
{
   // char* expression;
   // cout << "Enter Postfix Expression : ";
        //gets(expression);

        //Creation of Expression Tree
        Node tree = *expression_tree_from_postfix("a b - 5 +");

        //Traversal Operation on expression tree
        cout << "\nIn-Order Traversal :   ";
        inOrder(stack[0]);

        cout << "\nPre-Order Traversal :  ";
        preOrder(stack[0]);

        cout << "\nPost-Order Traversal : ";
        postOrder(stack[0]);
        return 0;
}
