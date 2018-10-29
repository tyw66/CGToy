
TEMPLATE = subdirs

DESTDIR = $$PWD/../bin
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../../common/

include($$PWD/../../common/common.pri)
include($$PWD/core/core.pri)
include($$PWD/gui/gui.pri) #界面
#include($$PWD/cmd/cmd.pri) #命令行


QMAKE_CXXFLAGS +=  -std=c++11
QMAKE_CXXFLAGS += -fopenmp
LIBS += -lgomp -lpthread
