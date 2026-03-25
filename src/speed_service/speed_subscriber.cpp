#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <vsomeip/runtime.hpp>
#include <cstring>

class SpeedSubscriber{
    
    std::shared_ptr<vsomeip::runtime> runtime_;
    std::shared_ptr<vsomeip::application> app_;
    
    

    public:
    SpeedSubscriber(){
        runtime_ = vsomeip::runtime::get();
        app_ = runtime_->create_application("SpeedSubscriber"); 
        
    }

    bool init(){
        if(!app_->init()){
            return false;
        }
        auto res = [this](vsomeip::state_type_e _state){
            if(_state==vsomeip::state_type_e::ST_REGISTERED){
                std::cout<<"Registered with routing manager"<<std::endl;
                
                app_->request_service(0x1234, 0x0001);
                
                
                
    

            }
        };
        
        auto message_handler_lambda = [] (const std::shared_ptr<vsomeip::message>& _message ){
            auto payload = _message->get_payload();
            float speed;
            memcpy(&speed, payload->get_data(), sizeof(speed));
            std::cout<<"Recieved speed: "<< speed << std::endl;
        };
        auto availability_handler_lambda = [this] (vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available ){
            if(_is_available){ 
                app_->subscribe(0x1234, 0x0001,0x0001, vsomeip::DEFAULT_MAJOR,vsomeip::ANY_EVENT);
            }
        };
        app_->register_message_handler(0x1234, 0x0001, 0x8001, message_handler_lambda);
        app_->request_event(0x1234, 0x0001, 0x8001,{0x0001},vsomeip::event_type_e::ET_EVENT);
        app_->register_availability_handler(0x1234, 0x0001, availability_handler_lambda);
        app_->register_state_handler(res);
        return true;
        
        
        
    }

    void start(){

        app_->start();
    }






};

int main(){

    SpeedSubscriber speed_subscriber;
    speed_subscriber.init();
    speed_subscriber.start();

    return 0;
}