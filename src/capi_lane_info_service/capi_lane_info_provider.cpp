#include <v1/v1/adas/LaneInfoStubDefault.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>



class LaneInfoService : public v1::v1::adas::LaneInfoStubDefault {
    int counter_;
    public:
    LaneInfoService (){
        counter_ = 0;
    }
    void send_lane_info_event(){
        int pos = counter_ % 75;
        v1::v1::adas::LaneInfo::LaneData lane;
        if(0<=pos && pos<25){
            
            //Staright road, centered, no ldw
            lane = v1::v1::adas::LaneInfo::LaneData( 0, 0, false, false, 2);

        }
        else if(25<= pos && pos <= 50){
            
            //Gentle left curve, drifting right — offset 0.3, curvature 0.002, ldw_left true
            lane = v1::v1::adas::LaneInfo::LaneData( 0.3, 0.002, true, false, 2);
            
        }
        else if(50< pos && pos <75){
            
            // Lane departure warning — offset 0.8, ldw_right true
            lane = v1::v1::adas::LaneInfo::LaneData( 0.8, 0.002, false, true, 2);

        }
        fireLaneUpdateEvent(lane);
        counter_++;
    }

};


int main(){
    auto runtime = CommonAPI::Runtime::get();
    auto service = std::make_shared<LaneInfoService>();
    runtime->registerService("local", "commonapi.adas.LaneInfo", service);
    
    while(true){
        service->send_lane_info_event();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}