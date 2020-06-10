QT += gui
QT += testlib gui
QT += widgets
CONFIG += c++11 console
CONFIG -= app_bundle
win32:TARGET  = ../TestLib
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        error.cpp \
        main.cpp \
        node.cpp \
        test_depth_first_search.cpp \
        test_expression_tree_from_postfix.cpp \
        test_recognize_node_type.cpp \
        test_sum_of_current_operation.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    error.h \
    node.h \
    test_depth_first_search.h \
    test_expression_tree_from_postfix.h \
    test_recognize_node_type.h \
    test_sum_of_current_operation.h
