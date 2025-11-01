
macro(sge_add_example target)
    # Парсим аргументы - только источники и зависимости
    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    
    # Создаем исполняемый файл
    add_executable(${target} ${THIS_SOURCES})
    
    # Линкуем с зависимостями если они указаны
    if(THIS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${THIS_DEPENDS})
    endif()
endmacro()

add_subdirectory(SimpleApp)
add_subdirectory(DevTestApp)
