#include <v1/v1/adas/VehicleSpeedStubDefault.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>



class VehicleSpeedService : public v1::v1::adas::VehicleSpeedStubDefault {
    int counter_;
    public:
    VehicleSpeedService (){
        counter_ = 0;
    }
    void send_speed_event(){
        int pos = counter_ % 150;
        float speed = 0.0f;
        if(0<=pos && pos<50){
            speed = pos;
        }
        else if(50<= pos && pos <= 100){
            speed = 50;
        }
        else if(100< pos && pos <150){
            speed = 149 -pos;
        }
        
        fireSpeedEventEvent(speed);
        counter_++;
    }

};


int main(){
    auto runtime = CommonAPI::Runtime::get();
    auto service = std::make_shared<VehicleSpeedService>();
    runtime->registerService("local", "commonapi.adas.VehicleSpeed", service);
    
    while(true){
        service->send_speed_event();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}