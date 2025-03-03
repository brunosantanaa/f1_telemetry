#ifndef F1_2023_H_
#define F1_2023_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "f1_telemetry_common.h"
#include "f1_2022.h"

typedef struct __attribute__((packed))
{
    uint16_t packetFormat;           ///< Packet Format e.g. 2023
    uint8_t gameYear;                ///< Year of game e.g. 23
    uint8_t gameMajorVersion;        ///< Game major version - "X.00"
    uint8_t gameMinorVersion;        ///< Game minor version - "0.XX"
    uint8_t packetVersion;           ///< Version of this packet type, all start from 1
    uint8_t packetId;                ///< Packet ID
    uint64_t sessionUID;             ///< Unique identifier for the session
    float sessionTime;               ///< Session timestamp
    uint32_t frameIdentifier;        ///< Identifier for the frame the data was retrieved on
    uint32_t overallFrameIdentifier; ///< Overall identifier for the frame the data was retrieved on, doesn't go back after flashbacks
    uint8_t playerCarIndex;          ///< Index of player's car in the array
    uint8_t secondaryPlayerCarIndex; ///< Index of secondary player's car in the array (splitscreen)
} f1_2023_header_t;

typedef f1_2022_telemetry_t f1_2023_telemetry_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header; // Header
    f1_2023_telemetry_t carTelemetryData[F1_NUM_CARS_22];
    uint8_t mfdPanelIndex;                // Index of MFD panel open - 255 = MFD closed
                                          // Single player, race – 0 = Car setup, 1 = Pits
                                          //  2 = Damage, 3 =  Engine, 4 = Temperatures
                                          // May vary depending on game mode
    uint8_t mfdPanelIndexSecondaryPlayer; // See above
    int8_t suggestedGear;                 // Suggested gear for the player (1-8)
                                          // 0 if no gear suggested
} f1_2023_pckt_telemetry_t;

typedef struct __attribute__((packed))
{
    uint32_t lastLapTimeInMS;            ///< Last lap time in milliseconds
    uint32_t currentLapTimeInMS;         ///< Current time around the lap in milliseconds
    uint16_t sector1TimeInMS;            ///< Sector 1 time in milliseconds
    uint8_t sector1TimeMinutes;          ///< Sector 1 time in minutes
    uint16_t sector2TimeInMS;            ///< Sector 2 time in milliseconds
    uint8_t sector2TimeMinutes;          ///< Sector 2 time in minutes
    uint16_t deltaToCarInFrontInMS;      ///< Delta in milliseconds for car in front
    uint16_t deltaToRaceLeaderInMS;      ///< Delta in milliseconds for fastest race lap
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
} f1_2023_lap_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header;               ///< Header
    f1_2023_lap_t lapData[F1_NUM_CARS_22]; ///< Lap data for all cars on track
    uint8_t timeTrialPersonalBestCarIdx;   ///< Index of personal best vehicle in time trial
    uint8_t timeTrialRivalCarIdx;          ///< Index of fastest car in time trial
} f1_2023_pckt_lap_t;

///< Car Damage Packet
typedef struct __attribute__((packed))
{
    float tyresWear[F1_NUM_TIRES_4];      ///< Tyre wear (percentage)
    uint8_t tyresDamage[F1_NUM_TIRES_4];  ///< Tyre damage (percentage)
    uint8_t brakesDamage[F1_NUM_TIRES_4]; ///< Brakes damage (percentage)
    uint8_t frontLeftWingDamage;          ///< Front left wing damage (percentage)
    uint8_t frontRightWingDamage;         ///< Front right wing damage (percentage)
    uint8_t rearWingDamage;               ///< Rear wing damage (percentage)
    uint8_t floorDamage;                  ///< Floor damage (percentage)
    uint8_t diffuserDamage;               ///< Diffuser damage (percentage)
    uint8_t sidepodDamage;                ///< Sidepod damage (percentage)
    uint8_t drsFault;                     ///< Indicator for DRS fault, 0 = OK, 1 = fault
    uint8_t ersFault;                     ///< Indicator for ERS fault, 0 = OK, 1 = fault
    uint8_t gearBoxDamage;                ///< Gear box damage (percentage)
    uint8_t engineDamage;                 ///< Engine damage (percentage)
    uint8_t engineMGUHWear;               ///< Engine wear MGU-H (percentage)
    uint8_t engineESWear;                 ///< Engine wear ES (percentage)
    uint8_t engineCEWear;                 ///< Engine wear CE (percentage)
    uint8_t engineICEWear;                ///< Engine wear ICE (percentage)
    uint8_t engineMGUKWear;               ///< Engine wear MGU-K (percentage)
    uint8_t engineTCWear;                 ///< Engine wear TC (percentage)
    uint8_t engineBlown;                  ///< Engine blown, 0 = OK, 1 = fault
    uint8_t engineSeized;                 ///< Engine seized, 0 = OK, 1 = fault
} f1_2023_car_damage_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header; // Header
    f1_2023_car_damage_t carDamageData[F1_NUM_CARS_22];
} f1_2023_pckt_car_damage_t;

typedef f1_2022_car_motion_t f1_2023_car_motion_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header;                            ///< Header
    f1_2023_car_motion_t carMotionData[F1_NUM_CARS_22]; ///< Data for all cars on track
                                                        ///< Extra player car ONLY data
} f1_2023_pckt_car_motion_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header;                      // Header
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
} f1_2023_pckt_motion_t;

typedef struct __attribute__((packed))
{
    uint8_t tractionControl;        ///< Traction control - 0 = off, 1 = medium, 2 = full
    uint8_t antiLockBrakes;         ///< 0 (off) - 1 (on)
    uint8_t fuelMix;                ///< Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    uint8_t frontBrakeBias;         ///< Front brake bias (percentage)
    uint8_t pitLimiterStatus;       ///< Pit limiter status - 0 = off, 1 = on
    float fuelInTank;               ///< Current fuel mass
    float fuelCapacity;             ///< Fuel capacity
    float fuelRemainingLaps;        ///< Fuel remaining in terms of laps (value on MFD)
    uint16_t maxRPM;                ///< Cars max RPM, point of rev limiter
    uint16_t idleRPM;               ///< Cars idle RPM
    uint8_t maxGears;               ///< Maximum number of gears
    uint8_t drsAllowed;             ///< 0 = not allowed, 1 = allowed
    uint16_t drsActivationDistance; ///< 0 = DRS not available, non-zero - DRS will be available
                                    ///< in [X] metres
    uint8_t actualTyreCompound;     ///< F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
                                    ///< 7 = inter, 8 = wet
                                    ///< F1 Classic - 9 = dry, 10 = wet
                                    ///< F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
                                    ///< 15 = wet
    uint8_t visualTyreCompound;     ///< F1 visual (can be different from actual compound)
                                    ///< 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                    ///< F1 Classic – same as above
                                    ///< F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                    ///< 21 = medium , 22 = hard
    uint8_t tyresAgeLaps;           ///< Age in laps of the current set of tyres
    int8_t vehicleFiaFlags;         ///< -1 = invalid/unknown, 0 = none, 1 = green
                                    ///< 2 = blue, 3 = yellow, 4 = red
    float enginePowerICE;           ///< Engine power output of ICE (W)
    float enginePowerMGUK;          ///< Engine power output of MGU-K (W)
    float ersStoreEnergy;           ///< ERS energy store in Joules
    uint8_t ersDeployMode;          ///< ERS deployment mode, 0 = none, 1 = medium
                                    ///< 2 = hotlap, 3 = overtake
    float ersHarvestedThisLapMGUK;  ///< ERS energy harvested this lap by MGU-K
    float ersHarvestedThisLapMGUH;  ///< ERS energy harvested this lap by MGU-H
    float ersDeployedThisLap;       ///< ERS energy deployed this lap
    uint8_t networkPaused;          ///< Whether the car is paused in a network game
} f1_2023_car_status_t;

typedef struct __attribute__((packed))
{
    f1_2023_header_t header; ///< Header
    f1_2023_car_status_t carStatusData[F1_NUM_CARS_22];
} f1_2023_pckt_car_status_t;

#endif // F1_2023_H_
