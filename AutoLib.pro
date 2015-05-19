APP_NAME = AutoLib

CONFIG += qt warn_on cascades10

LIBS += -lbb -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM
LIBS += -lbbsystem
LIBS += -lbb
LIBS += -lbbdata
LIBS += -lbbplatform
LIBS += -lbbplatformbbm 
LIBS += -lQtLocationSubset

include(config.pri)
