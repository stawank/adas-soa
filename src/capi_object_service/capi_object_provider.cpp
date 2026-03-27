#include <v1/v1/adas/ObjectListServiceStubDefault.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>



class DetectedObjectService : public v1::v1::adas::ObjectListServiceStubDefault {
    int counter_;
    public:
    DetectedObjectService (){
        counter_ = 0;
    }
    void send_object_list_event(){
        int pos = counter_ % 75;
        v1::v1::adas::ObjectListService::DetectedObjectList list;
        if(0<=pos && pos<25){
            
            //Fire  empty road

        }
        else if(25<= pos && pos <= 50){
            
            //Fire One Vehicle Ahead
            
            v1::v1::adas::ObjectListService::DetectedObject vehicle(0x0001, "vehicle", 30.0f, 5.0f, 6.0f);
            list.push_back(vehicle);
        }
        else if(50< pos && pos <75){
            
            // Fire Pedestrian Crossing Two Objects
            v1::v1::adas::ObjectListService::DetectedObject vehicle(0x0001, "vehicle", 30.0f, 5.0f, 6.0f);
            v1::v1::adas::ObjectListService::DetectedObject person(0x0001, "pedestrian", 10.0f, 5.0f, 6.0f);
            list.push_back(vehicle);
            list.push_back(person);
        }
        fireObjectsDetectedEvent(list);
        counter_++;
    }

};


int main(){
    auto runtime = CommonAPI::Runtime::get();
    auto service = std::make_shared<DetectedObjectService>();
    runtime->registerService("local", "commonapi.adas.ObjectListService", service);
    
    while(true){
        service->send_object_list_event();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}