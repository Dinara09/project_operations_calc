#ifndef ERROR_H
#define ERROR_H
#include <QString>

class Error
{
    int code_of_error; //код ошибки
    int column_of_error; //столбец с ошибкой
    QString information_of_error; //причина ошибки

public:
    //конструктор по-умолчанию
    Error ();
    //конструктор с параметрами
    Error (int code_of_error, int column_of_error, QString information_of_error);
    //получение данных о поле code_of_error
    int get_code_error_code ();
    //получение данных о поле column_of_error
    int get_line_of_error ();
    //получение данных о поле information_of_error
    QString get_information_of_error ();

};

#endif // ERROR_H

