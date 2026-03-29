#include <v1/v1/adas/CollisionWarningProxy.hpp>
#include <v1/v1/adas/LaneInfoProxy.hpp>
#include <v1/v1/adas/ObjectListServiceProxy.hpp>
#include <v1/v1/adas/VehicleSpeedProxy.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>
#include <iostream>
#include <chrono>


class ServiceMonitor{
    std::shared_ptr<v1::v1::adas::LaneInfoProxy<>> lane_info_proxy_;
    std::shared_ptr<v1::v1::adas::CollisionWarningProxy<>> collision_warning_proxy_;
    std::shared_ptr<v1::v1::adas::ObjectListServiceProxy<>> object_list_proxy_;
    std::shared_ptr<v1::v1::adas::VehicleSpeedProxy<>> vehicle_speed_proxy_;
    std::shared_ptr<CommonAPI::Runtime> runtime_;

    public:
    ServiceMonitor(){
        runtime_ = CommonAPI::Runtime::get();
        
    }

    std::chrono::milliseconds calculate_availability_latency_lis(){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        lane_info_proxy_ = runtime_->buildProxy<v1::v1::adas::LaneInfoProxy>("local", "commonapi.adas.LaneInfo");

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        return latency;
        
    }


    std::chrono::milliseconds calculate_availability_latency_vss(){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        vehicle_speed_proxy_ = runtime_->buildProxy<v1::v1::adas::VehicleSpeedProxy>("local", "commonapi.adas.VehicleSpeed");
        while(!vehicle_speed_proxy_->isAvailable()){
            
            if (!vehicle_speed_proxy_) {
                std::cerr << "Failed to build VehicleSpeed proxy" << std::endl;
                return std::chrono::milliseconds(-1);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        return latency;
        
    }

    std::chrono::milliseconds calculate_availability_latency_ols(){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        object_list_proxy_ = runtime_->buildProxy<v1::v1::adas::ObjectListServiceProxy>("local", "commonapi.adas.ObjectListService");

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        return latency;
        
    }

    std::chrono::milliseconds calculate_availability_latency_cws(){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        collision_warning_proxy_ = runtime_->buildProxy<v1::v1::adas::CollisionWarningProxy>("local", "commonapi.adas.CollisionWarning");

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto latency = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        return latency;
        
    }
};

int main(){
    // Redirect vsomeip logging to stderr so report stays clean
    setenv("VSOMEIP_CONFIGURATION_FILE", "", 0);
    auto runtime = CommonAPI::Runtime::get();
    ServiceMonitor service_monitor;

    std::cout << "\n=== SOME/IP Service Availability Report ===" << std::endl;
    std::cout << "LaneInfo Service:         " << service_monitor.calculate_availability_latency_lis().count() << "ms" << std::endl;
    std::cout << "VehicleSpeed Service:     " << service_monitor.calculate_availability_latency_vss().count() << "ms" << std::endl;
    std::cout << "ObjectList Service:       " << service_monitor.calculate_availability_latency_ols().count() << "ms" << std::endl;
    std::cout << "CollisionWarning Service: " << service_monitor.calculate_availability_latency_cws().count() << "ms" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    return 0;
}