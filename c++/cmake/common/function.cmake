
MACRO(CUR_DIR RESULT TARGET_PATH)
    string(REPLACE "/" ";" PATH_NAME ${TARGET_PATH})
    list(REVERSE PATH_NAME)
    list(GET PATH_NAME 0 NAME)
    SET(${RESULT} ${NAME})
ENDMACRO(CUR_DIR)

MACRO(SUB_DIRS RESULT TARGET_PATH)
    FILE(GLOB CHILDREN RELATIVE ${TARGET_PATH} ${TARGET_PATH}/*)
    SET(DIR_LIST "")
    FOREACH(CHILD ${CHILDREN})
        IF(IS_DIRECTORY ${TARGET_PATH}/${CHILD})
            LIST(APPEND DIR_LIST ${CHILD})
        ENDIF()
    ENDFOREACH()
    SET(${RESULT} ${DIR_LIST})
ENDMACRO(SUB_DIRS)

MACRO(EXISTS_FILE_SUB_PATHS RESULT TARGET_PATH FILE_NAME)
    SUB_DIRS(TARGET_DIR ${TARGET_PATH})
    SET(DIR_LIST "")
    FOREACH(TARGET ${TARGET_DIR})
        IF(EXISTS ${TARGET_PATH}/${TARGET}/${FILE_NAME})
            LIST(APPEND DIR_LIST ${TARGET_PATH}/${TARGET})
        ENDIF()
    ENDFOREACH()
    SET(${RESULT} ${DIR_LIST})
ENDMACRO(EXISTS_FILE_SUB_PATHS)
