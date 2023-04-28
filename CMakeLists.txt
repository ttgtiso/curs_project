cmake_minimum_required(VERSION 3.18.4)
project(Curs_project VERSION 0.1.0)

if (UNIX)
	find_package(wxWidgets REQUIRED COMPONENTS net core base)
	if(wxWidgets_USE_FILE) # not defined in CONFIG mode
	    include(${wxWidgets_USE_FILE})
	endif()

	file(GLOB project_GLOB
	    include/*
	    src/*
	)

	file (GLOB project_LIB_MYSQL
	    lib/linux/mariadb/*)

	add_executable(Curs_project ${project_GLOB})
	target_link_libraries(Curs_project ${wxWidgets_LIBRARIES}
					                   ${project_LIB_MYSQL})
	target_include_directories(Curs_project PRIVATE ${wxWidgets_INCLUDE_DIRS}
	                                                include/)
endif (UNIX)

if (WIN32)
	set(wxWidgets_ROOT_DIR "C:/wxWidgets")
	set(wxWidgets_LIB_DIR "C:/wxWidgets/lib/gcc1220_x64_dll")	

	find_package(wxWidgets REQUIRED COMPONENTS net core base)
	if(wxWidgets_USE_FILE) # not defined in CONFIG mode
	    include(${wxWidgets_USE_FILE})
	endif()

	file(GLOB project_GLOB
		    include/*
		    src/*
	)
	file (GLOB project_LIB_MYSQL
		    lib/windows/mariadb/*)
	add_executable(Curs_project ${project_GLOB})
	target_link_libraries(Curs_project ${wxWidgets_LIBRARIES}
						                   ${project_LIB_MYSQL})
	target_include_directories(Curs_project PRIVATE ${wxWidgets_INCLUDE_DIRS}
		                                                include/)
endif (WIN32)
		    
