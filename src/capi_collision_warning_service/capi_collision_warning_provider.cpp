#include <v1/v1/adas/CollisionWarningStubDefault.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>



class CollisionWarning : public v1::v1::adas::CollisionWarningStubDefault {

    float ttc_threshold_ ;
    float simulated_ttc_ ;
    public:
    CollisionWarning (){
        
        ttc_threshold_ = 5.0f;
        simulated_ttc_ = 10.0f;
    }
    void SetTTCThreshold(std::shared_ptr<CommonAPI::ClientId> _client, float _threshold, SetTTCThresholdReply_t _reply) override {
        ttc_threshold_ = _threshold;
        _reply(true);  // send response back
    }



    void simulate_objects(){
        if(simulated_ttc_ < 0){
            simulated_ttc_ = 10.0f;
        }
        if (simulated_ttc_ < ttc_threshold_){
            v1::v1::adas::CollisionWarning::Severity Severity;
            uint32_t id = 1;

            if(simulated_ttc_ < 3.0f){
                Severity = v1::v1::adas::CollisionWarning::Severity::EMERGENCY;
            }
            else if( simulated_ttc_ < 4.0f){
                Severity = v1::v1::adas::CollisionWarning::Severity::CRITICAL;
            }
            else{
                Severity = v1::v1::adas::CollisionWarning::Severity::WARN;
            }
            fireFCWAlertEvent(simulated_ttc_, Severity,  id);
        }
        simulated_ttc_ = simulated_ttc_ - 0.25;
    }

};


int main(){
    auto runtime = CommonAPI::Runtime::get();
    auto service = std::make_shared<CollisionWarning>();
    runtime->registerService("local", "commonapi.adas.CollisionWarning", service);
    while(true){
        service->simulate_objects();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }



    return 0;
}