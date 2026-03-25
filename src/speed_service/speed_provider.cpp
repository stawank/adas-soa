#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/runtime.hpp>
#include <thread>
#include <atomic>
#include <cstring>

class SpeedProvider{
    
    std::shared_ptr<vsomeip::runtime> runtime_;
    std::shared_ptr<vsomeip::application> app_;
    std::thread timer_thread_;
    std::atomic<bool> running_;
    
    void send_speed_event(){
        
        float speed = 65.5f;
        std::vector<vsomeip::byte_t> payload_data(4);
        memcpy(payload_data.data(), &speed, sizeof(speed));
        auto payload = runtime_->create_payload(payload_data);
        app_->notify(0x1234, 0x0001, 0x8001, payload);
    }
    public:
    SpeedProvider(){
        runtime_ = vsomeip::runtime::get();
        app_ = runtime_->create_application("SpeedProvider"); 
        running_ = false;
    }

    bool init(){
        if(!app_->init()){
            return false;
        };
        auto res = [this](vsomeip::state_type_e _state){
        if(_state==vsomeip::state_type_e::ST_REGISTERED){
            std::cout<<"Registered with routing manager"<<std::endl;
            app_->offer_service(0x1234, 0x0001);
            std::set<vsomeip::eventgroup_t> eventgroup = {0x0001};
            app_->offer_event(0x1234, 0x0001, 0x8001, eventgroup, vsomeip::event_type_e::ET_EVENT);
            std::vector<vsomeip::byte_t> initial_data(4);

            running_ = true;

            timer_thread_ = std::thread([this](){            
                while(running_){
                send_speed_event();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                };
                }
            );
        }
        };
        app_->register_state_handler(res);
        return true;
    }

    void start(){

        app_->start();
    }






};

int main(){

    SpeedProvider speed_provider;
    speed_provider.init();
    speed_provider.start();

    return 0;
}