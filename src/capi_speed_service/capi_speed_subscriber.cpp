#include <v1/v1/adas/VehicleSpeedProxy.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>
#include <iostream>


int main(){
    auto runtime = CommonAPI::Runtime::get();
    
    auto proxy = runtime->buildProxy<v1::v1::adas::VehicleSpeedProxy>("local", "commonapi.adas.VehicleSpeed");
    
    while(!proxy->isAvailable()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    proxy->getSpeedEventEvent().subscribe([](const float& speed){
        std::cout<<"Recieved speed: "<< speed << std::endl;
    });
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}