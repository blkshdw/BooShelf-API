cmake_minimum_required(VERSION 3.3)
project(BooShelf_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS system thread regex)
INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIR}
)

link_directories(
        ${CMAKE_INSTALL_PREFIX}/lib
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(Jansson REQUIRED )
if (JANSSON_FOUND)
    include_directories(${JANSSON_INCLUDE_DIRS})
endif()

set(SOURCE_FILES main.cpp exceptions/httpExceptions.cpp
        exceptions/httpExceptions.h
        tools/auth.cpp
        tools/auth.h
        routes/books/books.cpp routes/books/books.h
        routes/users/users.cpp routes/users/users.h
        routes/reviews/reviews.cpp routes/reviews/reviews.h
        tools/token.cpp tools/token.h
        middleware/auth.cpp middleware/auth.h
        access-rights/Visitor.h
        access-rights/UserVisitor.cpp access-rights/UserVisitor.h
        access-rights/GuestVisitor.cpp access-rights/GuestVisitor.h models/validator/validator.h models/user.h models/book.h models/review.h middleware/headers.cpp middleware/headers.h models/tracking.h routes/trackings/trackings.cpp routes/trackings/trackings.h)
add_executable(BooShelf_server ${SOURCE_FILES})
TARGET_LINK_LIBRARIES( BooShelf_server ${Boost_LIBRARIES} ${JANSSON_LIBRARIES} ssl crypto rethinkdb++ jwt)
