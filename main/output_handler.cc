#include "output_handler.h"
#include "tensorflow/lite/micro/micro_log.h"

void HandleOutput(float speed, float torque, float prediction) {
    MicroPrintf("Speed: %f, Torque: %f, Prediction: %f", speed, torque, prediction);
    
    if (prediction > 0.5) {
        MicroPrintf("Condition: High efficeincy detected");
        
    } else {
        MicroPrintf("Condition: Low efficency detected");
       
    }
}