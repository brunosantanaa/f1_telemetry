#ifndef F1_2024_H_
#define F1_2024_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "f1_telemetry_common.h"
#include "f1_2023.h"

typedef f1_2023_header_t f1_2024_header_t;

typedef f1_2023_telemetry_t f1_2024_telemetry_t;
typedef f1_2023_pckt_telemetry_t f1_2024_pckt_telemetry_t;

typedef struct __attribute__((packed))
{
    uint32_t lastLapTimeInMS;            ///< Last lap time in milliseconds
    uint32_t currentLapTimeInMS;         ///< Current time around the lap in milliseconds
    uint16_t sector1TimeInMS;            ///< Sector 1 time in milliseconds
    uint8_t sector1TimeMinutes;          ///< Sector 1 time in minutes
    uint16_t sector2TimeInMS;            ///< Sector 2 time in milliseconds
    uint8_t sector2TimeMinutes;          ///< Sector 2 time in minutes
    uint16_t deltaToCarInFrontInMS;      ///< Delta in milliseconds for car in front
    uint8_t deltaToCarInFrontMinutes;    ///< Delta in minutes for car in front
    uint16_t deltaToRaceLeaderInMS;      ///< Delta in milliseconds for fastest race lap
    uint8_t deltaToRaceLeaderMinutes;    ///< Delta in minutes for fastest race lap
    float lapDistance;                   ///< Distance vehicle is around current lap in metres – could
                                         ///< be negative if line hasn’t been crossed yet
    float totalDistance;                 ///< Total distance travelled in session in metres – could
                                         ///< be negative if line hasn’t been crossed yet
    float safetyCarDelta;                ///< Delta in seconds for safety car
    uint8_t carPosition;                 ///< Car race position
    uint8_t currentLapNum;               ///< Current lap number
    uint8_t pitStatus;                   ///< 0 = none, 1 = pitting, 2 = in pit area
    uint8_t numPitStops;                 ///< Number of pit stops taken in this race
    uint8_t sector;                      ///< 0 = sector1, 1 = sector2, 2 = sector3
    uint8_t currentLapInvalid;           ///< Current lap invalid - 0 = valid, 1 = invalid
    uint8_t penalties;                   ///< Accumulated time penalties in seconds to be added
    uint8_t warnings;                    ///< Accumulated number of warnings issued
    uint8_t cornerCuttingWarnings;       ///< Accumulated number of corner cutting warnings issued
    uint8_t numUnservedDriveThroughPens; ///< Num drive through pens left to serve
    uint8_t numUnservedStopGoPens;       ///< Num stop go pens left to serve
    uint8_t gridPosition;                ///< Grid position the vehicle started the race in
    uint8_t driverStatus;                ///< Status of driver - 0 = in garage, 1 = flying lap
                                         ///< 2 = in lap, 3 = out lap, 4 = on track
    uint8_t resultStatus;                ///< Result status - 0 = invalid, 1 = inactive, 2 = active
                                         ///< 3 = finished, 4 = didnotfinish, 5 = disqualified
                                         ///< 6 = not classified, 7 = retired
    uint8_t pitLaneTimerActive;          ///< Pit lane timing, 0 = inactive, 1 = active
    uint16_t pitLaneTimeInLaneInMS;      ///< If active, the current time spent in the pit lane in ms
    uint16_t pitStopTimerInMS;           ///< Time of the actual pit stop in ms
    uint8_t pitStopShouldServePen;       ///< Whether the car should serve a penalty at this stop
    float speedTrapFastestSpeed;         ///< Speed trap speed of fastest speed trap achieved in kmph
    uint8_t speedTrapFastestLap;         ///< Lap number of the fastest speed trap achieved, 255 = not set
} f1_2024_lap_t;

typedef struct __attribute__((packed))
{
    f1_2024_header_t header;               ///< Header
    f1_2024_lap_t lapData[F1_NUM_CARS_22]; ///< Lap data for all cars on track
    uint8_t timeTrialPersonalBestCarIdx;   ///< Index of personal best vehicle in time trial
    uint8_t timeTrialRivalCarIdx;          ///< Index of fastest car in time trial
} f1_2024_pckt_lap_t;

///< Car Damage Packet
typedef f1_2023_car_damage_t f1_2024_car_damage_t;
typedef f1_2023_pckt_car_damage_t f1_2024_pckt_car_damage_t;

typedef f1_2023_car_motion_t f1_2024_car_motion_t;
typedef f1_2023_pckt_car_motion_t f1_2024_pckt_car_motion_t;

typedef struct __attribute__((packed))
{
    f1_2024_header_t header;                      // Header
    float suspensionPosition[F1_NUM_TIRES_4];     ///< Note: All wheel arrays have the following order:
    float suspensionVelocity[F1_NUM_TIRES_4];     ///< RL, RR, FL, FR
    float suspensionAcceleration[F1_NUM_TIRES_4]; ///< RL, RR, FL, FR
    float wheelSpeed[F1_NUM_TIRES_4];             ///< Speed of each wheel
    float wheelSlipRatio[F1_NUM_TIRES_4];         ///< Slip ratio for each wheel
    float wheelSlipAngle[F1_NUM_TIRES_4];         ///< Slip angle for each wheel
    float wheelLateralForce[F1_NUM_TIRES_4];      ///< Lateral force for each wheel
    float wheelLongitudinalForce[F1_NUM_TIRES_4]; ///< Longitudinal force for each wheel

    float heightOfCGAboveGround; ///< Height of the CG above the ground
    float localVelocityX;        ///< Velocity in local space
    float localVelocityY;        ///< Velocity in local space
    float localVelocityZ;        ///< Velocity in local space
    float angularVelocityX;      ///< Angular velocity x-component
    float angularVelocityY;      ///< Angular velocity y-component
    float angularVelocityZ;      ///< Angular velocity z-component
    float angularAccelerationX;  ///< Angular acceleration x-component
    float angularAccelerationY;  ///< Angular acceleration y-component
    float angularAccelerationZ;  ///< Angular acceleration z-component

    float frontWheelsAngle;                   ///< Current front wheels angle in radians
    float wheelVErticalForce[F1_NUM_TIRES_4]; ///< Vertical G-Force for each wheel

    float frontAeroHeight; ///< Front plank edge height above road surface
    float rearAeroHeight;  ///< Rear wing edge height above road surface
    float frontRollAngle;  ///< Front roll angle in radians of the front suspension
    float rearRollAngle;   ///< Rear roll angle in radians of the rear suspension
    float chassisYaw;      ///< Yaw angle of the chassis relative to the direction of motion - radians
} f1_2024_pckt_motion_t;

typedef f1_2023_car_status_t f1_2024_car_status_t;
typedef f1_2023_pckt_car_status_t f1_2024_pckt_car_status_t;

#endif // F1_2024_H_
