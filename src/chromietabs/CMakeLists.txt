add_library(chromietabs
    commandfactory.cc
    commands.cc
    fileparser.cc
    pathutils.cc
    pickle.cc
    rawcommand.h
    sessionanalyzer.cc
    sessionreader.cc)

install(TARGETS chromietabs
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES
    commandfactory.h
    commands.h
    fileparser.h
    pathutils.h
    pickle.h
    rawcommand.h
    sessionanalyzer.h
    sessionreader.h
    DESTINATION include/${PROJECT_NAME})
