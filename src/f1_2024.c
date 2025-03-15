/**
 * @file f1_2024.c
 * @author Bruno de Santana
 * @brief
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "f1_2024.h"

#include <string.h>

#include "f1_telemetry.h"

f1_telemetry_err_t F1_2024_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry)
{
  if (telemetry == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2024_pckt_telemetry_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(telemetry, data, sizeof(f1_2024_pckt_telemetry_t));

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2024_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap)
{
  if (lap == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2024_pckt_lap_t))
  {
    return F1_ERR_NO_DATA;
  }

  memcpy(lap, data, sizeof(f1_2024_pckt_lap_t));
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2024_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage)
{
  if (damage == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2024_pckt_car_damage_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(damage, data, sizeof(f1_2024_pckt_car_damage_t));
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2024_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2024_pckt_car_motion_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(motion, data, sizeof(f1_2024_pckt_car_motion_t));

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2024_GetMotionEx(const void *data, size_t len, f1_telemetry_pckt_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2024_pckt_motion_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(motion, data, sizeof(f1_telemetry_pckt_motion_t));

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2024_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status)
{
  if (status == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2024_pckt_car_status_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(status, data, sizeof(f1_2024_pckt_car_status_t));
  return F1_ERR_OK;
}
