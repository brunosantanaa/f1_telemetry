#ifndef F1_TELEMETRY_H_
#define F1_TELEMETRY_H_

#include "f1_2024.h"

typedef f1_2024_header_t f1_telemetry_header_t;
typedef f1_2024_pckt_telemetry_t f1_telemetry_pckt_telemetry_t;
typedef f1_2024_pckt_lap_t f1_telemetry_pckt_lap_t;
typedef f1_2024_pckt_car_damage_t f1_telemetry_pckt_car_damage_t;
typedef f1_2024_pckt_car_motion_t f1_telemetry_pckt_car_motion_t;
typedef f1_2024_pckt_car_status_t f1_telemetry_pckt_car_status_t;
typedef f1_2024_pckt_motion_t f1_telemetry_pckt_motion_t;

f1_telemetry_err_t F1_TELEMETRY_PacketParser(const void *data, size_t len);
f1_telemetry_err_t F1_TELEMETRY_GetTelemetry(f1_telemetry_pckt_telemetry_t *telemetry);
f1_telemetry_err_t F1_TELEMETRY_GetLap(f1_telemetry_pckt_lap_t *lap);
f1_telemetry_err_t F1_TELEMETRY_GetCarDamage(f1_telemetry_pckt_car_damage_t *damage);
f1_telemetry_err_t F1_TELEMETRY_GetCarMotion(f1_telemetry_pckt_car_motion_t *motion);
f1_telemetry_err_t F1_TELEMETRY_GetCarStatus(f1_telemetry_pckt_car_status_t *status);

f1_telemetry_err_t F1_2024_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry);
f1_telemetry_err_t F1_2024_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap);
f1_telemetry_err_t F1_2024_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage);
f1_telemetry_err_t F1_2024_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion);
f1_telemetry_err_t F1_2023_GetMotionEx(const void *data, size_t len, f1_telemetry_pckt_motion_t *motion);
f1_telemetry_err_t F1_2024_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status);

f1_telemetry_err_t F1_2023_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry);
f1_telemetry_err_t F1_2023_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap);
f1_telemetry_err_t F1_2023_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage);
f1_telemetry_err_t F1_2023_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion);
f1_telemetry_err_t F1_2023_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status);

f1_telemetry_err_t F1_2022_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry);
f1_telemetry_err_t F1_2022_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap);
f1_telemetry_err_t F1_2022_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage);
f1_telemetry_err_t F1_2022_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion);
f1_telemetry_err_t F1_2022_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status);

#endif // F1_TELEMETRY_H_