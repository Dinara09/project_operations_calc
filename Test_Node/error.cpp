#include "error.h"

//конструктор по-умолчанию
Error:: Error ()
{
    this->code_of_error = NULL;
    this->column_of_error = NULL;
    this->information_of_error = nullptr;
}

//конструктор с параметрами
Error:: Error (int code_of_error, int column_of_error, QString information_of_error)
{
    this->code_of_error = code_of_error;
    this->column_of_error = column_of_error;
    this->information_of_error = information_of_error;
}

//получение данных о поле code_of_error
int Error:: get_code_error_code ()
{
    return this->code_of_error; //вернуть содержимое  поля code_of_error
}

//получение данных о поле column_of_error
int Error:: get_line_of_error ()
{
    return this->column_of_error; //вернуть содержимое  поля column_of_error
}

//получение данных о поле information_of_error
QString Error:: get_information_of_error ()
{
    return this->information_of_error; //вернуть содержимое  поля information_of_error
}
