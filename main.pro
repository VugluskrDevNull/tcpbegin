TEMPLATE = subdirs

libtimebomb.subdir  = lib/timebomb
libqircbot.subdir   = lib/qircbot
timebomb.subdir     = apps/timebomb
qircbot.subdir      = apps/qircbot

SUBDIRS = common      \
          libtimebomb \
          libqircbot  \
                      \
          timebomb    \
          qircbot

libtimebomb.depends  = common
libqircbot.depends   = common
timebomb.depends     = common libtimebomb
qircbot.depends      = common libqircbot
