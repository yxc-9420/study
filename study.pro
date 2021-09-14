QT -= gui
QT += network
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        DesignMode/csimplefactory.cpp \
        DesignMode/main.cpp \
        Example/general.cpp \
        LeetCode/leet17.cpp \
        LeetCode/leet22.cpp \
        LeetCode/leet541.cpp \
        LeetCode/main.cpp \
        MultiThreading/cthreadpool.cpp \
        MultiThreading/main.cpp \
        MultiThreading/multiThreading.cpp \
        STL/main.cpp \
        STL/my_vector.cpp \
        STL/rbtree.cpp \
        STL/stl_algorithm.cpp \
        STL/tree.cpp \
        Socket/client.cpp \
        Socket/server.cpp \
        carraysort.cpp \
        cmysharedptr.cpp \
        main.cpp \
        mystring.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DesignMode/csimplefactory.h \
    MultiThreading/cthreadpool.h \
    STL/my_vector.h \
    STL/rbtree.h \
    STL/tree.h \
    carraysort.h \
    cmysharedptr.h \
    mystring.h

OTHER_FILES+=\
    笔记.md\
    操作系统.md\
    计算机网络.md
DISTFILES += \
    MultiThreading/multi.exe \
    Socket/client.exe \
    Socket/server.exe \
    basic.md \
    git.md \
    main.exe
