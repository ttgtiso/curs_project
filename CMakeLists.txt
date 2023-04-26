cmake_minimum_required(VERSION 3.18.4)
project(Curs_project VERSION 0.1.0)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

file(GLOB project_GLOB
    include/*
    src/*
)
add_executable(Curs_project ${project_GLOB})
target_link_libraries(Curs_project ${wxWidgets_LIBRARIES})
target_include_directories(Curs_project PRIVATE ${wxWidgets_INCLUDE_DIRS}
                            include/)