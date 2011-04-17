# -------------------------------------------------
# Project created by QtCreator 2011-04-05T19:23:13
# -------------------------------------------------
TARGET = LEDCube
CONFIG += uitools
TEMPLATE = app
QT = gui core
SOURCES += main.cpp \
    mainwindow.cpp \
    effect_base.cpp \
    test_effect.cpp \
    effect_driver.cpp \
    rain_effect.cpp \
    ball_effect.cpp \
    wave_effect.cpp \
    text_scroll_effect.cpp \
    sphere_effect.cpp
HEADERS += mainwindow.h \
    effect_base.h \
    test_effect.h \
    effect_driver.h \
    rain_effect.h \
    ball_effect.h \
    wave_effect.h \
    text_scroll_effect.h \
    sphere_effect.h
FORMS += mainwindow.ui \
    test_effect_ctrl.ui \
    rain_effect_ctrl.ui \
    ball_effect_ctrl.ui \
    wave_effect_ctrl.ui \
    text_scroll_effect_ctrl.ui \
    sphere_effect_ctrl.ui
INCLUDEPATH += ../../../boost_1_46_1 \
    ../../../boost_1_46_1/boost
LIBS += -L../../../boost_1_46_1/stage/lib \
    -lws2_32

LIBS += -lboost_system-mgw44-mt-1_46_1 \
        -lboost_thread-mgw44-mt-1_46_1

RESOURCES += \
    resources.qrc
