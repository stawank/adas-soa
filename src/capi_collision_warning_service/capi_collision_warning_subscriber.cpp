#include <v1/v1/adas/CollisionWarningProxy.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <thread>
#include <iostream>


int main(){
    auto runtime = CommonAPI::Runtime::get();
    
    auto proxy = runtime->buildProxy<v1::v1::adas::CollisionWarningProxy>("local", "commonapi.adas.CollisionWarning");
    
    while(!proxy->isAvailable()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    proxy->getFCWAlertEvent().subscribe([](const float& ttc,
        const v1::v1::adas::CollisionWarning::Severity& Severity, 
        const uint32_t& id){   
            std::cout << "FCW Alert! TTC: " << ttc << "s";
            std::cout << " Object ID: " << id;
            std::cout << " Severity: " << static_cast<int>(Severity) << std::endl;

    
    });
    CommonAPI::CallStatus status;
    bool accepted;
    proxy->SetTTCThreshold(3.0f, status, accepted);
    if (status == CommonAPI::CallStatus::SUCCESS) {
        std::cout << "Threshold set to 3.0s, accepted: " << accepted << std::endl;
    }
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}