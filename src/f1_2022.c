/**
 * @file f1_2022.c
 * @author Bruno Santana (bruno.sant.a)
 * @brief Implementação das funções de conversão de dados F1 2022
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "f1_2022.h"

#include <string.h>

#include "f1_telemetry.h"

static void ConvertHeaderF1_2022_To_2024(const f1_2022_header_t *src, f1_2024_header_t *dst);

f1_telemetry_err_t F1_2022_GetTelemetry(const void *data, size_t len, f1_telemetry_pckt_telemetry_t *telemetry)
{
  if (telemetry == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2022_pckt_telemetry_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2022_pckt_telemetry_t telemetry_tmp = {0};
  memcpy(&telemetry_tmp, data, sizeof(f1_2022_pckt_telemetry_t));
  memset(telemetry, 0, sizeof(f1_telemetry_pckt_telemetry_t));

  // Converter o cabeçalho
  ConvertHeaderF1_2022_To_2024(&telemetry_tmp.header, &telemetry->header);

  // Converter dados de telemetria para cada carro
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    telemetry->carTelemetryData[i].speedKPH = telemetry_tmp.carTelemetryData[i].speedKPH;
    telemetry->carTelemetryData[i].throttle = telemetry_tmp.carTelemetryData[i].throttle;
    telemetry->carTelemetryData[i].steer = telemetry_tmp.carTelemetryData[i].steer;
    telemetry->carTelemetryData[i].brake = telemetry_tmp.carTelemetryData[i].brake;
    telemetry->carTelemetryData[i].clutch = telemetry_tmp.carTelemetryData[i].clutch;
    telemetry->carTelemetryData[i].gear = telemetry_tmp.carTelemetryData[i].gear;
    telemetry->carTelemetryData[i].engineRPM = telemetry_tmp.carTelemetryData[i].engineRPM;
    telemetry->carTelemetryData[i].drs = telemetry_tmp.carTelemetryData[i].drs;
    telemetry->carTelemetryData[i].revLightsPercent = telemetry_tmp.carTelemetryData[i].revLightsPercent;
    telemetry->carTelemetryData[i].revLightsBitValue = telemetry_tmp.carTelemetryData[i].revLightsBitValue;

    // Copiar arrays de temperatura e dados dos pneus
    for (int j = 0; j < F1_NUM_TIRES_4; j++)
    {
      telemetry->carTelemetryData[i].brakesTemperature[j] = telemetry_tmp.carTelemetryData[i].brakesTemperature[j];
      telemetry->carTelemetryData[i].tyresSurfaceTemperature[j] = telemetry_tmp.carTelemetryData[i].tyresSurfaceTemperature[j];
      telemetry->carTelemetryData[i].tyresInnerTemperature[j] = telemetry_tmp.carTelemetryData[i].tyresInnerTemperature[j];
      telemetry->carTelemetryData[i].tyresPressure[j] = telemetry_tmp.carTelemetryData[i].tyresPressure[j];
      telemetry->carTelemetryData[i].surfaceType[j] = telemetry_tmp.carTelemetryData[i].surfaceType[j];
    }

    telemetry->carTelemetryData[i].engineTemperature = telemetry_tmp.carTelemetryData[i].engineTemperature;
  }

  // Copiar dados MFD e sugestão de marcha
  telemetry->mfdPanelIndex = telemetry_tmp.mfdPanelIndex;
  telemetry->mfdPanelIndexSecondaryPlayer = telemetry_tmp.mfdPanelIndexSecondaryPlayer;
  telemetry->suggestedGear = telemetry_tmp.suggestedGear;

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2022_GetLap(const void *data, size_t len, f1_telemetry_pckt_lap_t *lap)
{
  if (lap == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2022_pckt_lap_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2022_pckt_lap_t lap_tmp = {0};
  memcpy(&lap_tmp, data, sizeof(f1_2022_pckt_lap_t));
  memset(lap, 0, sizeof(f1_telemetry_pckt_lap_t));

  // Converter o cabeçalho
  ConvertHeaderF1_2022_To_2024(&lap_tmp.header, &lap->header);

  // Converter dados de volta para cada carro
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    lap->lapData[i].lastLapTimeInMS = lap_tmp.lapData[i].lastLapTimeInMS;
    lap->lapData[i].currentLapTimeInMS = lap_tmp.lapData[i].currentLapTimeInMS;
    lap->lapData[i].sector1TimeInMS = lap_tmp.lapData[i].sector1TimeInMS;
    lap->lapData[i].sector1TimeMinutes = 0; // Campo novo em 2023/2024
    lap->lapData[i].sector2TimeInMS = lap_tmp.lapData[i].sector2TimeInMS;
    lap->lapData[i].sector2TimeMinutes = 0;       // Campo novo em 2023/2024
    lap->lapData[i].deltaToCarInFrontInMS = 0;    // Campo novo em 2023/2024
    lap->lapData[i].deltaToCarInFrontMinutes = 0; // Campo novo em 2024
    lap->lapData[i].deltaToRaceLeaderInMS = 0;    // Campo novo em 2023/2024
    lap->lapData[i].deltaToRaceLeaderMinutes = 0; // Campo novo em 2024
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
    lap->lapData[i].cornerCuttingWarnings = 0; // Campo novo em 2023/2024
    lap->lapData[i].numUnservedDriveThroughPens = lap_tmp.lapData[i].numUnservedDriveThroughPens;
    lap->lapData[i].numUnservedStopGoPens = lap_tmp.lapData[i].numUnservedStopGoPens;
    lap->lapData[i].gridPosition = lap_tmp.lapData[i].gridPosition;
    lap->lapData[i].driverStatus = lap_tmp.lapData[i].driverStatus;
    lap->lapData[i].resultStatus = lap_tmp.lapData[i].resultStatus;
    lap->lapData[i].pitLaneTimerActive = lap_tmp.lapData[i].pitLaneTimerActive;
    lap->lapData[i].pitLaneTimeInLaneInMS = lap_tmp.lapData[i].pitLaneTimeInLaneInMS;
    lap->lapData[i].pitStopTimerInMS = lap_tmp.lapData[i].pitStopTimerInMS;
    lap->lapData[i].pitStopShouldServePen = lap_tmp.lapData[i].pitStopShouldServePen;
    lap->lapData[i].speedTrapFastestSpeed = 0.0f; // Campo novo em 2024
    lap->lapData[i].speedTrapFastestLap = 255;    // Campo novo em 2024 (255 = not set)
  }

  // Definir os índices para o time trial (novos em 2023/2024)
  lap->timeTrialPersonalBestCarIdx = 0;
  lap->timeTrialRivalCarIdx = 0;

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2022_GetCarDamage(const void *data, size_t len, f1_telemetry_pckt_car_damage_t *damage)
{
  if (damage == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2022_pckt_car_damage_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2022_pckt_car_damage_t damage_tmp = {0};
  memcpy(&damage_tmp, data, sizeof(f1_2022_pckt_car_damage_t));
  memset(damage, 0, sizeof(f1_telemetry_pckt_car_damage_t));

  // Converter o cabeçalho
  ConvertHeaderF1_2022_To_2024(&damage_tmp.header, &damage->header);

  // Converter dados de dano para cada carro
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    // Copiar arrays de desgaste e dano dos pneus e freios
    for (int j = 0; j < F1_NUM_TIRES_4; j++)
    {
      damage->carDamageData[i].tyresWear[j] = damage_tmp.carDamageData[i].tyresWear[j];
      damage->carDamageData[i].tyresDamage[j] = damage_tmp.carDamageData[i].tyresDamage[j];
      damage->carDamageData[i].brakesDamage[j] = damage_tmp.carDamageData[i].brakesDamage[j];
    }

    // Copiar demais dados de dano
    damage->carDamageData[i].frontLeftWingDamage = damage_tmp.carDamageData[i].frontLeftWingDamage;
    damage->carDamageData[i].frontRightWingDamage = damage_tmp.carDamageData[i].frontRightWingDamage;
    damage->carDamageData[i].rearWingDamage = damage_tmp.carDamageData[i].rearWingDamage;
    damage->carDamageData[i].floorDamage = damage_tmp.carDamageData[i].floorDamage;
    damage->carDamageData[i].diffuserDamage = damage_tmp.carDamageData[i].diffuserDamage;
    damage->carDamageData[i].sidepodDamage = damage_tmp.carDamageData[i].sidepodDamage;
    damage->carDamageData[i].drsFault = damage_tmp.carDamageData[i].drsFault;
    damage->carDamageData[i].ersFault = 0; // Campo novo em 2023/2024
    damage->carDamageData[i].gearBoxDamage = damage_tmp.carDamageData[i].gearBoxDamage;
    damage->carDamageData[i].engineDamage = damage_tmp.carDamageData[i].engineDamage;
    damage->carDamageData[i].engineMGUHWear = damage_tmp.carDamageData[i].engineMGUHWear;
    damage->carDamageData[i].engineESWear = damage_tmp.carDamageData[i].engineESWear;
    damage->carDamageData[i].engineCEWear = damage_tmp.carDamageData[i].engineCEWear;
    damage->carDamageData[i].engineICEWear = damage_tmp.carDamageData[i].engineICEWear;
    damage->carDamageData[i].engineMGUKWear = damage_tmp.carDamageData[i].engineMGUKWear;
    damage->carDamageData[i].engineTCWear = damage_tmp.carDamageData[i].engineTCWear;
    damage->carDamageData[i].engineBlown = 0;  // Campo novo em 2023/2024
    damage->carDamageData[i].engineSeized = 0; // Campo novo em 2023/2024
  }

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2022_GetCarMotion(const void *data, size_t len, f1_telemetry_pckt_car_motion_t *motion)
{
  if (motion == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2022_pckt_car_motion_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2022_pckt_car_motion_t motion_tmp = {0};
  memcpy(&motion_tmp, data, sizeof(f1_2022_pckt_car_motion_t));
  memset(motion, 0, sizeof(f1_telemetry_pckt_car_motion_t));

  // Converter o cabeçalho
  ConvertHeaderF1_2022_To_2024(&motion_tmp.header, &motion->header);

  // Converter dados de movimento para cada carro
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    motion->carMotionData[i].worldPositionX = motion_tmp.carMotionData[i].worldPositionX;
    motion->carMotionData[i].worldPositionY = motion_tmp.carMotionData[i].worldPositionY;
    motion->carMotionData[i].worldPositionZ = motion_tmp.carMotionData[i].worldPositionZ;
    motion->carMotionData[i].worldVelocityX = motion_tmp.carMotionData[i].worldVelocityX;
    motion->carMotionData[i].worldVelocityY = motion_tmp.carMotionData[i].worldVelocityY;
    motion->carMotionData[i].worldVelocityZ = motion_tmp.carMotionData[i].worldVelocityZ;
    motion->carMotionData[i].worldForwardDirX = motion_tmp.carMotionData[i].worldForwardDirX;
    motion->carMotionData[i].worldForwardDirY = motion_tmp.carMotionData[i].worldForwardDirY;
    motion->carMotionData[i].worldForwardDirZ = motion_tmp.carMotionData[i].worldForwardDirZ;
    motion->carMotionData[i].worldRightDirX = motion_tmp.carMotionData[i].worldRightDirX;
    motion->carMotionData[i].worldRightDirY = motion_tmp.carMotionData[i].worldRightDirY;
    motion->carMotionData[i].worldRightDirZ = motion_tmp.carMotionData[i].worldRightDirZ;
    motion->carMotionData[i].gForceLateral = motion_tmp.carMotionData[i].gForceLateral;
    motion->carMotionData[i].gForceLongitudinal = motion_tmp.carMotionData[i].gForceLongitudinal;
    motion->carMotionData[i].gForceVertical = motion_tmp.carMotionData[i].gForceVertical;
    motion->carMotionData[i].yaw = motion_tmp.carMotionData[i].yaw;
    motion->carMotionData[i].pitch = motion_tmp.carMotionData[i].pitch;
    motion->carMotionData[i].roll = motion_tmp.carMotionData[i].roll;
  }

  return F1_ERR_OK;
}

f1_telemetry_err_t F1_2022_GetCarStatus(const void *data, size_t len, f1_telemetry_pckt_car_status_t *status)
{
  if (status == NULL)
  {
    return F1_ERR_INVALID_ARG;
  }

  if (len < sizeof(f1_2022_pckt_car_status_t))
  {
    return F1_ERR_NO_DATA;
  }

  f1_2022_pckt_car_status_t status_tmp = {0};
  memcpy(&status_tmp, data, sizeof(f1_2022_pckt_car_status_t));
  memset(status, 0, sizeof(f1_telemetry_pckt_car_status_t));

  // Converter o cabeçalho
  ConvertHeaderF1_2022_To_2024(&status_tmp.header, &status->header);

  // Converter dados de status para cada carro
  for (int i = 0; i < F1_NUM_CARS_22; i++)
  {
    status->carStatusData[i].tractionControl = status_tmp.carStatusData[i].tractionControl;
    status->carStatusData[i].antiLockBrakes = status_tmp.carStatusData[i].antiLockBrakes;
    status->carStatusData[i].fuelMix = status_tmp.carStatusData[i].fuelMix;
    status->carStatusData[i].frontBrakeBias = status_tmp.carStatusData[i].frontBrakeBias;
    status->carStatusData[i].pitLimiterStatus = status_tmp.carStatusData[i].pitLimiterStatus;
    status->carStatusData[i].fuelInTank = status_tmp.carStatusData[i].fuelInTank;
    status->carStatusData[i].fuelCapacity = status_tmp.carStatusData[i].fuelCapacity;
    status->carStatusData[i].fuelRemainingLaps = status_tmp.carStatusData[i].fuelRemainingLaps;
    status->carStatusData[i].maxRPM = status_tmp.carStatusData[i].maxRPM;
    status->carStatusData[i].idleRPM = status_tmp.carStatusData[i].idleRPM;
    status->carStatusData[i].maxGears = status_tmp.carStatusData[i].maxGears;
    status->carStatusData[i].drsAllowed = status_tmp.carStatusData[i].drsAllowed;
    status->carStatusData[i].drsActivationDistance = status_tmp.carStatusData[i].drsActivationDistance;
    status->carStatusData[i].actualTyreCompound = status_tmp.carStatusData[i].actualTyreCompound;
    status->carStatusData[i].visualTyreCompound = status_tmp.carStatusData[i].visualTyreCompound;
    status->carStatusData[i].tyresAgeLaps = status_tmp.carStatusData[i].tyresAgeLaps;
    status->carStatusData[i].vehicleFiaFlags = status_tmp.carStatusData[i].vehicleFiaFlags;
    status->carStatusData[i].enginePowerICE = 0.0f;  // Campo novo em 2023/2024
    status->carStatusData[i].enginePowerMGUK = 0.0f; // Campo novo em 2023/2024
    status->carStatusData[i].ersStoreEnergy = status_tmp.carStatusData[i].ersStoreEnergy;
    status->carStatusData[i].ersDeployMode = status_tmp.carStatusData[i].ersDeployMode;
    status->carStatusData[i].ersHarvestedThisLapMGUK = status_tmp.carStatusData[i].ersHarvestedThisLapMGUK;
    status->carStatusData[i].ersHarvestedThisLapMGUH = status_tmp.carStatusData[i].ersHarvestedThisLapMGUH;
    status->carStatusData[i].ersDeployedThisLap = status_tmp.carStatusData[i].ersDeployedThisLap;
    status->carStatusData[i].networkPaused = status_tmp.carStatusData[i].networkPaused;
  }

  return F1_ERR_OK;
}

/**
 * @brief Função auxiliar para converter cabeçalho do formato 2022 para o formato 2024
 *
 * @param src Cabeçalho de origem (formato 2022)
 * @param dst Cabeçalho de destino (formato 2024)
 */
static void ConvertHeaderF1_2022_To_2024(const f1_2022_header_t *src, f1_2024_header_t *dst)
{
  dst->packetFormat = src->packetFormat;
  dst->gameYear = 22; // Versão 2022
  dst->gameMajorVersion = src->gameMajorVersion;
  dst->gameMinorVersion = src->gameMinorVersion;
  dst->packetVersion = src->packetVersion;
  dst->packetId = src->packetId;
  dst->sessionUID = src->sessionUID;
  dst->sessionTime = src->sessionTime;
  dst->frameIdentifier = src->frameIdentifier;
  dst->overallFrameIdentifier = src->frameIdentifier; // Mesmo valor para 2022
  dst->playerCarIndex = src->playerCarIndex;
  dst->secondaryPlayerCarIndex = src->secondaryPlayerCarIndex;
}
