/**
 * @file f1_2023.c
 * @author Bruno de Santana
 * @brief
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "f1_2023.h"

#include <string.h>

#include "f1_telemetry.h"

f1_telemetry_err_t F1_2023_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry)
{
  if (telemetry == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2023_pckt_telemetry_t))
  {
    return F1_ERR_NO_DATA;
  }

  memcpy(telemetry, data, sizeof(f1_2023_pckt_telemetry_t));
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2023_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap)
{
  if (lap == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2023_pckt_lap_t))
  {
    return F1_ERR_NO_DATA;
  }
  f1_2023_pckt_lap_t lap_tmp = {0};
  memcpy(&lap_tmp, data, sizeof(f1_2023_pckt_lap_t));
  memset(lap, 0, sizeof(f1_telemetry_pckt_lap_t));
  lap->header = lap_tmp.header;
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    lap->lapData[i].lastLapTimeInMS = lap_tmp.lapData[i].lastLapTimeInMS;
    lap->lapData[i].currentLapTimeInMS = lap_tmp.lapData[i].currentLapTimeInMS;
    lap->lapData[i].sector1TimeInMS = lap_tmp.lapData[i].sector1TimeInMS;
    lap->lapData[i].sector1TimeMinutes = lap_tmp.lapData[i].sector1TimeMinutes;
    lap->lapData[i].sector2TimeInMS = lap_tmp.lapData[i].sector2TimeInMS;
    lap->lapData[i].sector2TimeMinutes = lap_tmp.lapData[i].sector2TimeMinutes;
    lap->lapData[i].deltaToCarInFrontInMS = lap_tmp.lapData[i].deltaToCarInFrontInMS;
    lap->lapData[i].deltaToRaceLeaderInMS = lap_tmp.lapData[i].deltaToRaceLeaderInMS;
    lap->lapData[i].lapDistance = lap_tmp.lapData[i].lapDistance;
    lap->lapData[i].totalDistance = lap_tmp.lapData[i].totalDistance;
    lap->lapData[i].safetyCarDelta = lap_tmp.lapData[i].safetyCarDelta;
    lap->lapData[i].carPosition = lap_tmp.lapData[i].carPosition;
    lap->lapData[i].currentLapNum = lap_tmp.lapData[i].currentLapNum;
    lap->lapData[i].pitStatus = lap_tmp.lapData[i].pitStatus;
    lap->lapData[i].numPitStops = lap_tmp.lapData[i].numPitStops;
    lap->lapData[i].sector = lap_tmp.lapData[i].sector;
    lap->lapData[i].currentLapInvalid = lap_tmp.lapData[i].currentLapInvalid;
    lap->lapData[i].penalties = lap_tmp.lapData[i].penalties;
    lap->lapData[i].warnings = lap_tmp.lapData[i].warnings;
    lap->lapData[i].cornerCuttingWarnings = lap_tmp.lapData[i].cornerCuttingWarnings;
    lap->lapData[i].numUnservedDriveThroughPens = lap_tmp.lapData[i].numUnservedDriveThroughPens;
    lap->lapData[i].numUnservedStopGoPens = lap_tmp.lapData[i].numUnservedStopGoPens;
    lap->lapData[i].gridPosition = lap_tmp.lapData[i].gridPosition;
    lap->lapData[i].driverStatus = lap_tmp.lapData[i].driverStatus;
    lap->lapData[i].resultStatus = lap_tmp.lapData[i].resultStatus;
    lap->lapData[i].pitLaneTimerActive = lap_tmp.lapData[i].pitLaneTimerActive;
    lap->lapData[i].pitLaneTimeInLaneInMS = lap_tmp.lapData[i].pitLaneTimeInLaneInMS;
    lap->lapData[i].pitStopTimerInMS = lap_tmp.lapData[i].pitStopTimerInMS;
    lap->lapData[i].pitStopShouldServePen = lap_tmp.lapData[i].pitStopShouldServePen;
    lap->lapData[i].deltaToCarInFrontMinutes = 0; // Novo campo
    lap->lapData[i].deltaToRaceLeaderMinutes = 0; // Novo campo
    lap->lapData[i].speedTrapFastestSpeed = 0.0f; // Novo campo
    lap->lapData[i].speedTrapFastestLap = 255;    // Novo campo (255 = not set)
  }

  lap->timeTrialPersonalBestCarIdx = lap_tmp.timeTrialPersonalBestCarIdx;
  lap->timeTrialRivalCarIdx = lap_tmp.timeTrialRivalCarIdx;

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2023_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage)
{
  if (damage == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2023_pckt_car_damage_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(damage, data, sizeof(f1_2023_pckt_car_damage_t));
  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2023_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2023_pckt_car_motion_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(motion, data, sizeof(f1_2023_pckt_car_motion_t));

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2023_GetMotionEx(const void *data, size_t len, f1_telemetry_pckt_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2023_pckt_motion_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2023_pckt_motion_t motion_tmp = {0};
  memcpy(&motion_tmp, data, sizeof(f1_2023_pckt_motion_t));
  memset(motion, 0, sizeof(f1_telemetry_pckt_motion_t));

  motion->header = motion_tmp.header;
  for (int i = 0; i < F1_NUM_TIRES_4; i++)
  {
    motion->suspensionPosition[i] = motion_tmp.suspensionPosition[i];
    motion->suspensionVelocity[i] = motion_tmp.suspensionVelocity[i];
    motion->suspensionAcceleration[i] = motion_tmp.suspensionAcceleration[i];
    motion->wheelSpeed[i] = motion_tmp.wheelSpeed[i];
    motion->wheelSlipRatio[i] = motion_tmp.wheelSlipRatio[i];
    motion->wheelSlipAngle[i] = motion_tmp.wheelSlipAngle[i];
    motion->wheelLateralForce[i] = motion_tmp.wheelLateralForce[i];
    motion->wheelLongitudinalForce[i] = motion_tmp.wheelLongitudinalForce[i];
    motion->wheelVErticalForce[i] = motion_tmp.wheelVErticalForce[i];
  }

  // Copiar dados individuais
  motion->heightOfCGAboveGround = motion_tmp.heightOfCGAboveGround;
  motion->localVelocityX = motion_tmp.localVelocityX;
  motion->localVelocityY = motion_tmp.localVelocityY;
  motion->localVelocityZ = motion_tmp.localVelocityZ;
  motion->angularVelocityX = motion_tmp.angularVelocityX;
  motion->angularVelocityY = motion_tmp.angularVelocityY;
  motion->angularVelocityZ = motion_tmp.angularVelocityZ;
  motion->angularAccelerationX = motion_tmp.angularAccelerationX;
  motion->angularAccelerationY = motion_tmp.angularAccelerationY;
  motion->angularAccelerationZ = motion_tmp.angularAccelerationZ;
  motion->frontWheelsAngle = motion_tmp.frontWheelsAngle;

  // Inicializar os novos campos adicionados na estrutura f1_2024_pckt_motion_t
  motion->frontAeroHeight = 0.0f; // Novo campo
  motion->rearAeroHeight = 0.0f;  // Novo campo
  motion->frontRollAngle = 0.0f;  // Novo campo
  motion->rearRollAngle = 0.0f;   // Novo campo
  motion->chassisYaw = 0.0f;      // Novo campo

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2023_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status)
{
  if (status == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }
  if (len < sizeof(f1_2023_pckt_car_status_t))
  {
    return F1_ERR_NO_DATA;
  }
  memcpy(status, data, sizeof(f1_2023_pckt_car_status_t));
  return F1_ERR_OK;
}
