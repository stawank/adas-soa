# Source - https://stackoverflow.com/a/33090791
# Posted by Arne, modified by community. See post 'Timeline' for change history
# Retrieved 2026-03-23, License - CC BY-SA 4.0

cmake_minimum_required(VERSION 3.16)
project(adas-soa
  VERSION
    1.0
  DESCRIPTION
    "adas-soa"
  LANGUAGES
    CXX
)
set(CMAKE_CXX_STANDARD 17)

set(VSOMEIP_INCLUDE_DIR /usr/local/include)
set(VSOMEIP_LIB_DIR /usr/local/lib)



link_directories(${VSOMEIP_LIB_DIR})
# add the data to the target, so it becomes visible in some IDE
add_executable(speed_provider src/speed_service/speed_provider.cpp)
add_executable(speed_subscriber src/speed_service/speed_subscriber.cpp)


# just for example add some compiler flags
#target_compile_options()

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(speed_provider PUBLIC 
  src/include
  ${VSOMEIP_INCLUDE_DIR})

target_include_directories(speed_subscriber PUBLIC 
  src/include
  ${VSOMEIP_INCLUDE_DIR})





# this defines the variables Boost_LIBRARIES that contain all library names
# that we need to link to
#find_package()

target_link_libraries(speed_provider PUBLIC
  vsomeip3
  pthread
)

target_link_libraries(speed_subscriber PUBLIC
  vsomeip3
  pthread
)




