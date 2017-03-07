TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    json.cpp

HEADERS += \
    json.h \
    json_type.h \
    utils.h \
    key.h \
    json_num.h \
    json_base.h \
    json_bool.h \
    json_str.h \
    json_obj.h \
    json_arr.h \
    json_factory.h \
    json_raii.h

