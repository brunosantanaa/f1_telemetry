/**
 * @file f1_2022.c
 * @author Bruno Santana (bruno.sant.a)
 * @brief
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "f1_2022.h"

static f1_2022_pckt_telemetry_t pckt_telemetry = {0};
static f1_2022_pckt_lap_t pckt_lap = {0};
static f1_2022_pckt_car_damage_t pckt_car_damage = {0};
static f1_2022_pckt_car_motion_t pckt_car_motion = {0};
static f1_2022_pckt_car_status_t pckt_car_status = {0};

#define PCKT_TELEMETRY_SIZE (sizeof(f1_2022_pckt_telemetry_t))
#define PCKT_LAP_SIZE (sizeof(f1_2022_pckt_lap_t))
#define PCKT_DAMAGE_SIZE (sizeof(f1_2022_pckt_car_damage_t))
#define PCKT_MOTION_SIZE (sizeof(f1_2022_pckt_car_motion_t))
#define PCKT_STAUS_SIZE (sizeof(f1_2022_pckt_car_status_t))

f1_2022_err_t F1_2022_PacketParser(const void *data, size_t len)
{
  if (data == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }

  switch (len)
  {
  case PCKT_TELEMETRY_SIZE:
    memcpy(&pckt_telemetry, data, PCKT_TELEMETRY_SIZE);
    break;
  case PCKT_LAP_SIZE:
    memcpy(&pckt_lap, data, PCKT_LAP_SIZE);
    break;
  case PCKT_DAMAGE_SIZE:
    memcpy(&pckt_car_damage, data, PCKT_DAMAGE_SIZE);
    break;
  case PCKT_MOTION_SIZE:
    memcpy(&pckt_car_motion, data, PCKT_MOTION_SIZE);
    break;
  case PCKT_STAUS_SIZE:
    memcpy(&pckt_car_status, data, PCKT_STAUS_SIZE);
    break;
  default:
    return F1_2022_NO_DATA;
    break;
  }
  return F1_2022_OK;
}

f1_2022_err_t F1_2022_GetTelemetry(f1_2022_pckt_telemetry_t *telemetry)
{
  if (telemetry == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }
  *telemetry = pckt_telemetry;
  return F1_2022_OK;
}

f1_2022_err_t F1_2022_GetLap(f1_2022_pckt_lap_t *lap)
{
  if (lap == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }
  *lap = pckt_lap;
  return F1_2022_OK;
}

f1_2022_err_t F1_2022_GetCarDamage(f1_2022_pckt_car_damage_t *damage)
{
  if (damage == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }
  *damage = pckt_car_damage;
  return F1_2022_OK;
}

f1_2022_err_t F1_2022_GetCarMotion(f1_2022_pckt_car_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }
  *motion = pckt_car_motion;
  return F1_2022_OK;
}

f1_2022_err_t F1_2022_GetCarStatus(f1_2022_pckt_car_status_t *status)
{
  if (status == NULL)
  {
    return F1_2022_ERR_INVALID_ARG;
  }
  *status = pckt_car_status;
  return F1_2022_OK;
}