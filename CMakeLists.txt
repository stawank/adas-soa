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
set(COMMONAPI_INCLUDE_DIR /usr/local/include/CommonAPI-3.2)
set(COMMONAPI_LIB_DIR /usr/local/lib)
set(GENERATED_DIR ${CMAKE_SOURCE_DIR}/fidl/generated)

set(SPEED_GENERATED_SOURCES
    ${GENERATED_DIR}/v1/v1/adas/VehicleSpeedSomeIPDeployment.cpp
    ${GENERATED_DIR}/v1/v1/adas/VehicleSpeedSomeIPStubAdapter.cpp
    ${GENERATED_DIR}/v1/v1/adas/VehicleSpeedSomeIPProxy.cpp
)

set(OBJECTLIST_GENERATED_SOURCES
    ${GENERATED_DIR}/v1/v1/adas/ObjectListServiceSomeIPDeployment.cpp
    ${GENERATED_DIR}/v1/v1/adas/ObjectListServiceSomeIPStubAdapter.cpp
    ${GENERATED_DIR}/v1/v1/adas/ObjectListServiceSomeIPProxy.cpp
)

set(LANEINFO_GENERATED_SOURCES
    ${GENERATED_DIR}/v1/v1/adas/LaneInfoSomeIPDeployment.cpp
    ${GENERATED_DIR}/v1/v1/adas/LaneInfoSomeIPStubAdapter.cpp
    ${GENERATED_DIR}/v1/v1/adas/LaneInfoSomeIPProxy.cpp
)

link_directories(${VSOMEIP_LIB_DIR})
# add the data to the target, so it becomes visible in some IDE
add_executable(speed_provider src/speed_service/speed_provider.cpp)
add_executable(speed_subscriber src/speed_service/speed_subscriber.cpp)
add_executable(capi_speed_provider
    src/capi_speed_service/capi_speed_provider.cpp
    ${SPEED_GENERATED_SOURCES}
)

add_executable(capi_speed_subscriber
    src/capi_speed_service/capi_speed_subscriber.cpp
    ${SPEED_GENERATED_SOURCES}
)

add_executable(capi_object_provider
    src/capi_object_service/capi_object_provider.cpp
    ${OBJECTLIST_GENERATED_SOURCES}
)

add_executable(capi_object_subscriber
    src/capi_object_service/capi_object_subscriber.cpp
    ${OBJECTLIST_GENERATED_SOURCES}
)

add_executable(capi_lane_info_provider
    src/capi_lane_info_service/capi_lane_info_provider.cpp
    ${LANEINFO_GENERATED_SOURCES}
)

add_executable(capi_lane_info_subscriber
    src/capi_lane_info_service/capi_lane_info_subscriber.cpp
    ${LANEINFO_GENERATED_SOURCES}
)

# just for example add some compiler flags
#target_compile_options()

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(speed_provider PUBLIC 
  src/include
  ${VSOMEIP_INCLUDE_DIR})

target_include_directories(speed_subscriber PUBLIC 
  src/include
  ${VSOMEIP_INCLUDE_DIR})


target_include_directories(capi_speed_provider PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)

target_include_directories(capi_speed_subscriber PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)

target_include_directories(capi_object_provider PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)

target_include_directories(capi_object_subscriber PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)

target_include_directories(capi_lane_info_provider PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)

target_include_directories(capi_lane_info_subscriber PUBLIC
    src/include
    ${VSOMEIP_INCLUDE_DIR}
    ${COMMONAPI_INCLUDE_DIR}
    ${GENERATED_DIR}
)


target_link_libraries(capi_speed_provider PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)

target_link_libraries(capi_speed_subscriber PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)

target_link_libraries(capi_object_provider PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)

target_link_libraries(capi_object_subscriber PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)

target_link_libraries(capi_lane_info_provider PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)

target_link_libraries(capi_lane_info_subscriber PUBLIC
    vsomeip3
    CommonAPI
    CommonAPI-SomeIP
    pthread
)


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




