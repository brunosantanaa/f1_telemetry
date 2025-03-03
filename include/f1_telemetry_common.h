#ifndef F1_TELEMETRY_COMMON_H_
#define F1_TELEMETRY_COMMON_H_

#define F1_ERS_MAX_VALUE (4 * 1000 * 1000.0)
#define F1_FULL_TANK (20)
#define F1_NUM_CARS_22 (22)
#define F1_NUM_TIRES_4 (4)

typedef enum
{
    F1_ERR_OK = 0,
    F1_ERR_NO_DATA,
    F1_ERR_NO_MEM = 0x101,
    F1_ERR_INVALID_ARG,
    F1_ERR_FAIL = -1
} f1_telemetry_err_t;

#endif // F1_TELEMETRY_COMMON_H_