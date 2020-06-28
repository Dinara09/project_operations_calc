#include <QCoreApplication>
#include <iostream>
#include <conio.h>
#include <QtGlobal>
#include <QFile>
#include <QTextStream>
#include <QString>

#include "error.h"
#include "node.h"

QTextStream stream(stdin);

using namespace std;

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
    QString way_to_expression; //путь к файлу с выражением
    QString way_to_variables_file; //путь к файлу с перемнными
    QString way_to_cost_file; //путь к файлу с весами операций
    QString way_to_result_file; // путь к выходному файлу

    if (argc == 5)
    {
        way_to_expression = argv[1];
        way_to_variables_file = argv[2];
        way_to_cost_file = argv[3];
        way_to_result_file = argv[4];
    }

    else
    {
        cout << "Enter path of expression" << endl;
        way_to_expression = stream.readLine();

        cout << "Enter path of variables file" << endl;
        way_to_variables_file = stream.readLine();

        cout << "Enter path of cost file" << endl;
        way_to_cost_file = stream.readLine();

        cout << "Enter path of result file" << endl;
        way_to_result_file = stream.readLine();
    }

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

    //считываем файл с переменными
    read_file(errors, variables, way_to_variables_file, "variables");
    //считаем файл с весами
    read_file(errors, cost, way_to_cost_file, "cost");

    //Создаем дерево
    Node tree (*tree.expression_tree_from_postfix(read_expression(way_to_expression), stack, all_nodes, errors, variables, cost));

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
    write_file(errors, way_to_result_file, sum);

    return 0;
}
