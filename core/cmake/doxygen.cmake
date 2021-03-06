set(ALL "ALL")
find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(doc_dir ${CMAKE_BINARY_DIR}/docs)
    file(MAKE_DIRECTORY ${doc_dir})
    configure_file(${PROJECT_SOURCE_DIR}/cmake/Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(docs ${ALL} ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${doc_dir})
    install(DIRECTORY ${doc_dir}/ DESTINATION ${doc_dir} PATTERN "${doc_dir}/*")
else(DOXYGEN_FOUND)
    add_custom_target(docs ${ALL} COMMAND ${CMAKE_COMMAND} -E echo COMMENT "Doxygen not found" VERBATIM)
endif(DOXYGEN_FOUND)
