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
#include "f1_telemetry.h"

#include <string.h>

enum
{
  // 2022
  F1_TELEMETRY_PACKETMOTIONDATA,
  F1_TELEMETRY_PACKETSESSIONDATA,
  F1_TELEMETRY_PACKETLAPDATA,
  F1_TELEMETRY_PACKETEVENTDATA,
  F1_TELEMETRY_PACKETPARTICIPANTSDATA,
  F1_TELEMETRY_PACKETCARSETUPDATA,
  F1_TELEMETRY_PACKETCARTELEMETRYDATA,
  F1_TELEMETRY_PACKETCARSTATUSDATA,
  F1_TELEMETRY_PACKETFINALCLASSIFICATIONDATA,
  F1_TELEMETRY_PACKETLOBBYINFODATA,
  F1_TELEMETRY_PACKETCARDAMAGEDATA,
  F1_TELEMETRY_PACKETSESSIONHISTORYDATA,
  // 2023
  F1_TELEMETRY_PACKETTYRESETSDATA,
  // 2024
  F1_TELEMETRY_PACKETMOTIONEXDATA,
  F1_TELEMETRY_PACKETTIMETRIALDATA,
};

static f1_telemetry_err_t SetHeaderVersion(const void *data, size_t len);

static f1_telemetry_header_t header = {0};
static f1_telemetry_pckt_telemetry_t pckt_telemetry = {0};
static f1_telemetry_pckt_lap_t pckt_lap = {0};
static f1_telemetry_pckt_car_damage_t pckt_car_damage = {0};
static f1_telemetry_pckt_car_motion_t pckt_car_motion = {0};
static f1_telemetry_pckt_car_status_t pckt_car_status = {0};

f1_telemetry_err_t F1_TELEMETRY_PacketParser(const void *data, size_t len)
{
  f1_telemetry_err_t err = F1_ERR_INVALID_ARG;
  if (data == NULL)
  {
    return err;
  }
  err = SetHeaderVersion(data, len);
  if (err != F1_ERR_OK)
  {
    return err;
  }

  return err;
}

f1_telemetry_err_t F1_TELEMETRY_GetTelemetry(f1_telemetry_pckt_telemetry_t *telemetry)
{
  if (telemetry == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  *telemetry = pckt_telemetry;
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_TELEMETRY_GetLap(f1_telemetry_pckt_lap_t *lap)
{
  if (lap == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  *lap = pckt_lap;
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_TELEMETRY_GetCarDamage(f1_telemetry_pckt_car_damage_t *damage)
{
  if (damage == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  *damage = pckt_car_damage;
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_TELEMETRY_GetCarMotion(f1_telemetry_pckt_car_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  *motion = pckt_car_motion;
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_TELEMETRY_GetCarStatus(f1_telemetry_pckt_car_status_t *status)
{
  if (status == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  *status = pckt_car_status;
  return F1_ERR_OK;
}

static f1_telemetry_err_t SetHeaderVersion(const void *data, size_t len)
{
  if (data == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(uint16_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(&header.packetFormat, data, sizeof(uint16_t));
  if (header.packetFormat == 2022)
  {
    f1_2022_header_t header2022 = {0};
    memcpy(&header2022, data, sizeof(f1_2022_header_t));
    memcpy(&header.gameMajorVersion, &header2022.gameMajorVersion, sizeof(f1_2022_header_t) - sizeof(uint16_t));

    return F1_ERR_OK;
  }

  memcpy(&header, data, sizeof(f1_telemetry_header_t));

  return F1_ERR_OK;
}