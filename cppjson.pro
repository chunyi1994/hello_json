TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    json.cpp

HEADERS += \
    json_base_data.h \
    json.h \
    number_data.h \
    object_data.h \
    string_data.h \
    utils.h \
    array_data.h \
    bool_data.h \
    json_value.h

