cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(pluginTest)

################################################################################
# Launcher
################################################################################

add_executable(launcher main.c)
target_link_libraries(launcher PUBLIC ${CMAKE_DL_LIBS})
target_link_options(launcher PUBLIC -rdynamic)


################################################################################
# Plugin
################################################################################

add_library(plugin MODULE plugin.c)

if(APPLE)
    target_link_options(plugin PUBLIC -undefined dynamic_lookup)
endif()
