#ifndef ERROR_H
#define ERROR_H
#include <QList>
#include <QString>

/// \file error.h
/// \brief Заголовочный файл для описания класса error.
///
/// Файл содержит информацию о методах и полях класса error.
///

//класс для хранения инфромации об ошибках
/// \brief Класс, хранящий инфромацию об ошибках.
///
/// Данный класс предоставляет информацию об ошибки и месте его возникновения
class Error
{
    int code_of_error; //код ошибки
    int column_of_error; //столбец с ошибкой
    QString information_of_error; //причина ошибки

public:

    //конструктор по-умолчанию
    /// \brief Конструктор без параметров.
    Error ();

    //конструктор с параметрами
    /// \brief Конструктор с параметрами
    /// \param [in] code_of_error код ошибки
    /// \param [in] column_of_error столбец с ошибкой
    /// \param [in] information_of_error причина ошибки
    Error (int code_of_error, int column_of_error, QString information_of_error);

    //получение данных о поле code_of_error
    /// \brief получение данных о поле code_of_error
    /// \return код ошибки
    int get_code_error_code ();

    //получение данных о поле column_of_error
    /// \brief получение данных о поле column_of_error
    /// \return столбец с ошибкой
    int get_line_of_error ();

    //получение данных о поле information_of_error
    /// \brief получение данных о поле information_of_error
    /// \return причину возникновения ошибки
    QString get_information_of_error ();
};

#endif // ERROR_H
