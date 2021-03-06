TEMPLATE = subdirs


libtimebomb.subdir  = lib/timebomb
libqircbot.subdir   = lib/qircbot
timebomb.subdir     = apps/timebomb
qircbot.subdir      = apps/qircbot
qircgui.subdir      = apps/qircgui  #add

SUBDIRS = common      \
          libtimebomb \
          libqircbot  \
                      \
          timebomb    \
          qircbot     \
          qircgui                    #add

libqircbot.depends   = common
timebomb.depends     = common libtimebomb
qircbot.depends      = common libqircbot
+qircgui.depends      = common libqircbot libtimebomb
