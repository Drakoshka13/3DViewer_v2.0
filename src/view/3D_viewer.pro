QT       += core gui openglwidgets opengl
LIBS += -lopengl32 -lglu32 -lgdi32


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/lib/s21_matrix_oop.cc \
    ../model/model_viewer.cc \
    main.cc \
    mainwindow.cpp \
    myopenglwidget.cpp

HEADERS += \
    ../controller/controller_viewer.h \
    ../model/lib/s21_matrix_oop.h \
    ../model/model_viewer.h \
    mainwindow.h \
    myopenglwidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
