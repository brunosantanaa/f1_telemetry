#ifndef F1_TELEMETRY_H_
#define F1_TELEMETRY_H_

#include "f1_2024.h"

f1_telemetry_err_t F1_TELEMETRY_PacketParser(const void *data, size_t len);
f1_telemetry_err_t F1_TELEMETRY_GetTelemetry(f1_telemetry_pckt_telemetry_t *telemetry);
f1_telemetry_err_t F1_TELEMETRY_GetLap(f1_telemetry_pckt_lap_t *lap);
f1_telemetry_err_t F1_TELEMETRY_GetCarDamage(f1_telemetry_pckt_car_damage_t *damage);
f1_telemetry_err_t F1_TELEMETRY_GetCarMotion(f1_telemetry_pckt_car_motion_t *motion);
f1_telemetry_err_t F1_TELEMETRY_GetCarStatus(f1_telemetry_pckt_car_status_t *status);

#endif // F1_TELEMETRY_H_