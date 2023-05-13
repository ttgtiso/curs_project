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

	#file (GLOB project_LIB_MYSQL 
	#    lib/linux/mariadb/*) - забыть как страшный сон
	set(CXX_FLAGS "-lmysql"
					"-lmysqlcppconn"
					"-lmysqlclient-r")
	add_executable(Curs_project ${project_GLOB})
	target_compile_options(Curs_project PRIVATE ${CXX_FLAGS})
	target_link_libraries(Curs_project ${wxWidgets_LIBRARIES}
										${MYSQL_LIB_DIR}
										"/usr/lib/x86_64-linux-gnu/libmysqlcppconn.so")
	target_include_directories(Curs_project PRIVATE ${wxWidgets_INCLUDE_DIRS}
	                                                include/)
endif (UNIX)

if (WIN32)
	# Windows static library
	set(wxWidgets_ROOT_DIR "C:/wxWidgets")
	set(wxWidgets_LIB_DIR "C:/wxWidgets/lib/vc143_x64_dll")	

	find_package(wxWidgets REQUIRED COMPONENTS net core base)
	if(wxWidgets_USE_FILE) # not defined in CONFIG mode
	    include(${wxWidgets_USE_FILE})
	endif()

	file(GLOB project_GLOB
		    include/*
		    src/*
	)
	add_compile_definitions(STATIC_CONCPP)
	file(GLOB MYSQL_INCLUDE_DIR "C:/mysql-connector/include/jdbc")
	file(GLOB MYSQL_LIB_DIR "C:/mysql-connector/lib64/vs14/*")

	add_executable(Curs_project ${project_GLOB})
	target_link_libraries(Curs_project ${wxWidgets_LIBRARIES}
										${MYSQL_LIB_DIR})
	target_include_directories(Curs_project PRIVATE ${wxWidgets_INCLUDE_DIRS}
		                                        	"include/"
													${MYSQL_INCLUDE_DIR})
endif (WIN32)
		    
