#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/runtime.hpp>
#include <thread>
#include <atomic>

class SpeedProvider{
    
    std::shared_ptr<vsomeip::runtime> runtime_;
    std::shared_ptr<vsomeip::application> app_;
    std::thread timer_thread_;
    std::atomic<bool> running_;
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
        }
        };
        app_->register_state_handler(res);
        return false;
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