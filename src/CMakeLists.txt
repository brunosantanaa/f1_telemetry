# Source files
set(F1_TELEMETRY_SOURCES
    f1_2022.c
    f1_2023.c
    f1_2024.c
    f1_telemetry.c
)

# Header files
set(F1_TELEMETRY_HEADERS
    f1_2022.h
    f1_2023.h
    f1_2024.h
    f1_telemetry_common.h
    f1_telemetry.h
)

# Create library
add_library(f1_telemetry STATIC
    ${F1_TELEMETRY_SOURCES}
    ${F1_TELEMETRY_HEADERS}
)

# Include directories
target_include_directories(f1_telemetry PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Install rules
install(TARGETS f1_telemetry
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${F1_TELEMETRY_HEADERS}
    DESTINATION include
)
