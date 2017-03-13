TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QMAKE_CXXFLAGS +=  -Wno-unused-function
QMAKE_CXXFLAGS +=  -Wno-unused-variable

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
    test/dotest.h \
    test/test.h

