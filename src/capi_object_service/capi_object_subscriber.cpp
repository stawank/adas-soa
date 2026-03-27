#include <v1/v1/adas/ObjectListServiceProxy.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>
#include <iostream>


int main(){
    auto runtime = CommonAPI::Runtime::get();
    
    auto proxy = runtime->buildProxy<v1::v1::adas::ObjectListServiceProxy>("local", "commonapi.adas.ObjectListService");
    
    while(!proxy->isAvailable()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    proxy->getObjectsDetectedEvent().subscribe([](const v1::v1::adas::ObjectListService::DetectedObjectList& object_list){
        if(object_list.empty()){
            std::cout<<"Empty road detected."<< std::endl;
        }else{
            std::cout<< "Number of objects detected: "<< object_list.size()<< std::endl;
            for (auto object : object_list){
                std::cout<< "Object ID: "<< object.getID() << std::endl;
                std::cout<< "Object type: "<< object.getType() << std::endl;
                std::cout<< "Object distance: "<< object.getDistance() << std::endl;
                std::cout<< "Object relative velocity: "<< object.getRelative_velocity() << std::endl;
                std::cout<< "Object ttc: "<< object.getTime_to_collision() << std::endl;

            }
                                            
        
        }
        
    });
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}