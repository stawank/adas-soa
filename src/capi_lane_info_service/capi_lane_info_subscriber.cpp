#include <v1/v1/adas/LaneInfoProxy.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>
#include <iostream>


int main(){
    auto runtime = CommonAPI::Runtime::get();
    
    auto proxy = runtime->buildProxy<v1::v1::adas::LaneInfoProxy>("local", "commonapi.adas.LaneInfo");
    
    while(!proxy->isAvailable()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    proxy->getLaneUpdateEvent().subscribe([](const v1::v1::adas::LaneInfo::LaneData& lane_data){   
        std::cout<< "Lane Offset [m]: "<< lane_data.getLane_offset_m() << std::endl;
        std::cout<< "Lane Curvature [m]: "<< lane_data.getCurvature_m() << std::endl;
        std::cout<< "LDW Left: "<< lane_data.getLdw_left() << std::endl;
        std::cout<< "LDW Right: "<< lane_data.getLdw_right()<< std::endl;
        std::cout<< "Lane Count: "<< static_cast<int>(lane_data.getLane_count())<< std::endl;
    
    });
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}