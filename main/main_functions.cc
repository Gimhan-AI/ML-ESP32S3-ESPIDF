#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "esp_timer.h" 

#include "main_functions.h"
#include "model.h"
#include "constants.h"
#include "output_handler.h"

namespace {
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr; 
TfLiteTensor* output = nullptr;
int inference_count = 0;

constexpr int kTensorArenaSize = 20000; 
uint8_t tensor_arena[kTensorArenaSize];
}

void setup() {
    model = tflite::GetModel(converted_model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        MicroPrintf("Model provided is schema version %d not equal to supported "
                    "version %d.", model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }

    static tflite::MicroMutableOpResolver<3> resolver; 
    resolver.AddRelu();
    resolver.AddReshape();
    if (resolver.AddFullyConnected() != kTfLiteOk) {
        return;
    }

    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize);
    interpreter = &static_interpreter;

    if (interpreter->AllocateTensors() != kTfLiteOk) {
        MicroPrintf("AllocateTensors() failed");
        return;
    }

    input = interpreter->input(0);
    output = interpreter->output(0);

    inference_count = 0;
}

void loop() {
    float input_data[2] = {7500.0f, 30.0f}; 

    for (size_t i = 0; i < 2; ++i) {
        input->data.f[i] = input_data[i];
    }

    int64_t start_time = esp_timer_get_time(); 
    if (interpreter->Invoke() != kTfLiteOk) {
        MicroPrintf("Invoke failed.");
        return;
    }
    int64_t end_time = esp_timer_get_time(); 

    float y = output->data.f[0];
    HandleOutput(input_data[0], input_data[1], y);

    MicroPrintf("Inference Time: %lld microseconds", (end_time - start_time));

    inference_count += 1;
    if (inference_count >= kInferencesPerCycle) inference_count = 0;
}
