cmake_minimum_required(VERSION 3.5)

# Detecta se estamos em ambiente ESP-IDF
if(DEFINED ENV{IDF_PATH})
    set(ESP_IDF_BUILD TRUE)
    message(STATUS "Building with ESP-IDF")
else()
    set(ESP_IDF_BUILD FALSE)
    message(STATUS "Building as generic CMake project")
endif()

# Nome do componente/biblioteca
set(COMPONENT_NAME "f1_telemetry")

# Arquivos fonte compartilhados por todas as plataformas
set(SRCS 
    "src/f1_2022.c"
    "src/f1_2023.c"
    "src/f1_2024.c"
    "src/f1_telemetry.c"
)

# Diretórios de inclusão compartilhados
set(INCLUDE_DIRS "include")

# Condicionalmente configura o build baseado no ambiente
if(ESP_IDF_BUILD)
    # Configuração para ESP-IDF
    idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS ${INCLUDE_DIRS}
        # Adicione aqui quaisquer componentes do ESP-IDF que você precisa
        REQUIRES 
    )
else()
    project(${COMPONENT_NAME})
    
    # Add library
    add_library(${COMPONENT_NAME} ${SRCS})
    target_include_directories(${COMPONENT_NAME} PUBLIC ${INCLUDE_DIRS})
endif()