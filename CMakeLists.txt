cmake_minimum_required(VERSION 3.5)
project(webserver)

set(CMAKE_CXX_STANDARD 11)

#aux_source_directory(version_0.1/test SRC_DIR)


#aux_source_directory(version_0.3/src SRC_DIR)

#set(SOURCE_FILES
#        version_0.2/src/httpparse.cpp
#        version_0.2/src/httpresponse.cpp
#        version_0.2/src/main.cpp
#        version_0.2/src/server.cpp
#        version_0.2/src/ssocket.cpp
#        version_0.2/src/ThreadPool.cpp
#        version_0.2/src/Util.cpp
#        )


set(CXX_FLAGS
        -Wall
        -std=c++11
        -lpthread
        -Wno-unused-parameter
        -O3
        )

link_libraries(pthread)
link_libraries(ssl)
link_libraries(crypto)
link_libraries(dl)
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")


# set(SOURCE_FILES
#         version_0.1/src/main.cpp
#         version_0.1/src/mysocket.cpp
#         version_0.1/src/server.cpp
#         version_0.1/src/httpparse.cpp 
#         version_0.1/src/httpresponse.cpp   
#         version_0.1/src/utils.cpp    
#         )

# set(SOURCE_FILES
#         version_0.2/src/main.cpp
#         version_0.2/src/ntyreactor.cpp
#         version_0.2/src/export_fun.cpp
    
# )
# set(SOURCE_FILES
#         version_0.2_ws/src/main.cpp
#         version_0.2_ws/src/ntyreactor.cpp
#         version_0.2_ws/src/export_fun.cpp  
# )
set(SOURCE_FILES
        version_0.3/src/main.cpp
        version_0.3/src/ntyreactor.cpp
        version_0.3/src/export_fun.cpp  
        version_0.3/src/thread_pool.cpp
        version_0.3/src/deadlock_sucess.cpp
)

add_executable(webserver  ${SOURCE_FILES})