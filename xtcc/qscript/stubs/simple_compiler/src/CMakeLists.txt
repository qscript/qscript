cmake_minimum_required (VERSION 2.6)
project (qscript)
#set SOURCE = src
## find_package(BISON)
## find_package(FLEX)

#BISON_TARGET(qscriptParser q.y ${CMAKE_CURRENT_BINARY_DIRECTORY}/q.C)
#FLEX_TARGET(qscriptLexer lex.l ${CMAKE_CURRENT_BINARY_DIRECTORY}/lex.C)

INCLUDE_DIRECTORIES(${qscript_BINARY_DIR})
#ADD_CUSTOM_TARGET (qscriptParser echo "creating q.C parser for grammar")
#ADD_CUSTOM_TARGET (dataEntryParser echo "creating data_entry.C parser for data entry")
#ADD_CUSTOM_TARGET (qscriptLexer echo "creating lex.C scanner for grammar")
#ADD_CUSTOM_TARGET (dataEntryLexer echo "creating scan_data.C scanner for data entry")


ADD_CUSTOM_COMMAND(
#TARGET qscriptLexer
	SOURCE ${qscript_SOURCE_DIR}/lex.l
	COMMENT "building lex.C right now"
	COMMAND flex -o${qscript_BINARY_DIR}/lex.cxx ${qscript_SOURCE_DIR}/lex.l
	DEPENDS ${qscript_SOURCE_DIR}/lex.l
	OUTPUT ${qscript_BINARY_DIR}/lex.cxx 
	)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
#TARGET qscriptParser 
	SOURCE ${qscript_SOURCE_DIR}/q.ypp
	COMMENT "building q.C right now"
	COMMAND bison -d ${qscript_SOURCE_DIR}/q.ypp -o ${qscript_BINARY_DIR}/q.cxx
	COMMAND mv ${qscript_BINARY_DIR}/q.hxx ${qscript_BINARY_DIR}/q.h 
	DEPENDS ${qscript_SOURCE_DIR}/q.ypp
	OUTPUT ${qscript_BINARY_DIR}/q.cxx ${qscript_BINARY_DIR}/q.h 
	)


ADD_CUSTOM_COMMAND(
#TARGET dataEntryLexer
	SOURCE ${qscript_SOURCE_DIR}/scan_data.l
	COMMAND flex -o${qscript_BINARY_DIR}/scan_data.cxx ${qscript_SOURCE_DIR}/scan_data.l
	OUTPUT ${qscript_BINARY_DIR}/scan_data.cxx 
	)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
#TARGET dataEntryParser 
	SOURCE ${qscript_SOURCE_DIR}/data_entry.ypp
	COMMAND bison -p scan_data -d ${qscript_SOURCE_DIR}/data_entry.ypp -o ${qscript_BINARY_DIR}/data_entry.cxx
	COMMAND mv ${qscript_BINARY_DIR}/data_entry.hxx ${qscript_BINARY_DIR}/data_entry.h 
	OUTPUT ${qscript_BINARY_DIR}/data_entry.cxx ${qscript_BINARY_DIR}/data_entry.h 
	)

INCLUDE_DIRECTORIES(${qscript_SOURCE_DIR})
add_executable (qscript debug_mem.cpp expr.cpp main.cpp 
		named_range.cpp qscript_lib.h qscript_parser.cpp 
		question.cpp scope.cpp stmt.cpp 
		stmt_common.cpp symtab.cpp utils.cpp xtcc_set.cpp q.ypp lex.l scan_data.l data_entry.ypp
		question_disk_data.h 
		${qscript_BINARY_DIR}/data_entry.cxx ${qscript_BINARY_DIR}/data_entry.h
		${qscript_BINARY_DIR}/q.cxx ${qscript_BINARY_DIR}/q.h 
		${qscript_BINARY_DIR}/lex.cxx 
		${qscript_BINARY_DIR}/scan_data.cxx user_navigation.h
		)

target_link_libraries ( qscript readline)

add_dependencies ( qscript qscriptLexer qscriptParser dataEntryLexer dataEntryParser)


# Since parser.c does not exists yet when cmake is run, mark
# it as generated
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/q.C GENERATED)
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/lex.C GENERATED)
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/q.h GENERATED)
#
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/scan_data.C GENERATED)
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/data_entry.C GENERATED)
# SET_SOURCE_FILES_PROPERTIES(${qscript_BINARY_DIR}/data_entry.h GENERATED)

# Include binary directory to include lexer.c in parser.c


