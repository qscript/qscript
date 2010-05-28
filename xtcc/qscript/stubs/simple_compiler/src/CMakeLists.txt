#cmake_minimum_required (VERSION 2.6)
#project (qscript)
#set SOURCE = src
## find_package(BISON)
## find_package(FLEX)

#BISON_TARGET(qscriptParser q.y ${CMAKE_CURRENT_BINARY_DIRECTORY}/q.C)
#FLEX_TARGET(qscriptLexer lex.l ${CMAKE_CURRENT_BINARY_DIRECTORY}/lex.C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES(${qscript_BINARY_DIR})
ADD_CUSTOM_TARGET (qscriptParser echo "creating q.C parser for grammar"
	SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/q.ypp
	COMMENT "building q.C right now"
	COMMAND bison -d q.ypp -o q.cpp
	COMMAND mv q.hpp q.h 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/q.ypp
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
		)

ADD_CUSTOM_TARGET (qscriptLexer echo "creating lex.C scanner for grammar"
	SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
	COMMENT "building lex.C right now"
	COMMAND echo "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}"
	COMMAND flex -o lex.cpp lex.l
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
		)

ADD_CUSTOM_TARGET (dataEntryParser echo "creating data_entry.C parser for data entry"
	SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.ypp
	COMMAND bison -p scan_data -d data_entry.ypp -o data_entry.cpp
	COMMAND mv data_entry.hpp data_entry.h 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
		)

ADD_CUSTOM_TARGET (dataEntryLexer 
	SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/scan_data.l
	COMMAND echo "creating scan_data.cpp scanner for data entry ${CMAKE_CURRENT_SOURCE_DIR}"
	COMMAND flex -o scan_data.cpp scan_data.l
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
		)


ADD_CUSTOM_COMMAND(
	TARGET qscriptLexer
	SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
	COMMENT "building lex.C right now"
	COMMAND echo "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}"
	COMMAND flex -o ${CMAKE_CURRENT_SOURCE_DIR}/lex.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lex.l
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.cpp 
	)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
	TARGET qscriptParser 
	SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/q.ypp
	COMMENT "building q.C right now"
	COMMAND bison -d ${CMAKE_CURRENT_SOURCE_DIR}/q.ypp -o ${CMAKE_CURRENT_SOURCE_DIR}/q.cpp
	COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/q.hpp ${CMAKE_CURRENT_SOURCE_DIR}/q.h 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/q.ypp
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/q.cpp ${CMAKE_CURRENT_SOURCE_DIR}/q.h 
	)


ADD_CUSTOM_COMMAND(
	TARGET dataEntryLexer
	SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/scan_data.l
	COMMAND flex -o${CMAKE_CURRENT_SOURCE_DIR}/scan_data.cpp ${CMAKE_CURRENT_SOURCE_DIR}/scan_data.l
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/scan_data.cpp 
	)

# Create custom command for bison/yacc (note the DEPENDS)
ADD_CUSTOM_COMMAND(
	TARGET dataEntryParser 
	SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.ypp
	COMMAND bison -p scan_data -d ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.ypp -o ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.cpp
	COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.hpp ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.h 
	OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.cpp ${CMAKE_CURRENT_SOURCE_DIR}/data_entry.h 
	)

INCLUDE_DIRECTORIES(${qscript_SOURCE_DIR})
add_executable (qscript debug_mem.cpp expr.cpp main.cpp 
		named_range.cpp qscript_lib.h qscript_parser.cpp 
		question.cpp scope.cpp stmt.cpp 
		stmt_common.cpp symtab.cpp utils.cpp xtcc_set.cpp q.ypp lex.l scan_data.l data_entry.ypp
		question_disk_data.h 
		${qscript_SOURCE_DIR}/src/data_entry.cpp ${qscript_SOURCE_DIR}/src/data_entry.h
		${qscript_SOURCE_DIR}/src/q.cpp ${qscript_SOURCE_DIR}/src/q.h 
		${qscript_SOURCE_DIR}/src/lex.cpp 
		${qscript_SOURCE_DIR}/src/scan_data.cpp user_navigation.h
		)
add_dependencies ( qscript qscriptLexer qscriptParser dataEntryLexer dataEntryParser)

target_link_libraries ( qscript readline)



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


