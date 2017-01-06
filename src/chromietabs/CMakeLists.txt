add_library(chromietabs
    commandfactory.cc
    commands.cc
    pathutils.cc
    pickle.cc
    rawcommand.h
    sessionanalyzer.cc
    sessionreader.cc
    snssfilereader.cc)

install(TARGETS chromietabs
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES
    commandfactory.h
    commands.h
    pathutils.h
    pickle.h
    rawcommand.h
    sessionanalyzer.h
    sessionreader.h
    snssfilereader.h
    DESTINATION include/${PROJECT_NAME})
