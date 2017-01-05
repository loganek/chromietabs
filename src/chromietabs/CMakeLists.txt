add_library(chromietabs
    commandfactory.cc
    commands.cc
    fileparser.cc
    pickle.cc
    rawcommand.h
    sessionreader.cc)

install(TARGETS chromietabs
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

install(FILES
    commandfactory.h
    commands.h
    fileparser.h
    pickle.h
    rawcommand.h
    sessionreader.h
    DESTINATION include/${PROJECT_NAME})
