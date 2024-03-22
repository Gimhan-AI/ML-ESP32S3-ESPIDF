
# README
## Description
This project implements a 6-layer Artificial Neural Network (ANN) on an ESP32 microcontroller using TensorFlow Lite Micro. The ANN is designed for inference tasks and can be deployed on embedded systems for various applications such as sensor data analysis, classification, or control tasks.

## Requirements
ESP32-S3-DevkitC microcontroller development board.
TensorFlow Lite Micro library.
ESP-IDF in VScode
Training dataset (if retraining the model)
Installation
Clone or download this repository.
Install the required libraries.
Connect your ESP32 board to your computer.
Upload the code to the ESP32 board.

## Usage
Ensure that the ESP32 board is properly connected to the power source.
The ANN will run inference tasks automatically upon booting up.
Modify the code as needed to customize inputs, outputs, or model architecture.

## Model Training
### If you want to retrain the model:
Prepare your training dataset.
Train the model using TensorFlow or any other preferred framework.
Convert the trained model to TensorFlow Lite format.
Then Convert the model to C Code usin XXD converter.
Replace the existing model file in the project with the new one.
Rebuild and upload the project to the ESP32 board.
The model training process was done through Colab notebooks.
