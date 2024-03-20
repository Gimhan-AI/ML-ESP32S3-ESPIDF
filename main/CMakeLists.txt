idf_component_register(
    SRCS main.cc main_functions.cc constants.cc output_handler.cc model.cc
    INCLUDE_DIRS ""
    PRIV_REQUIRES spi_flash esp_timer
)
