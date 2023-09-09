#ifndef F1_2022_H
#define F1_2022_H

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define F1_2022_ERS_MAX (4000000.0)
#define F1_2022_FULL_TANK (20)
#define F1_2022_NUM_CARS (22)
#define F1_2022_NUM_TIRES (4)

typedef enum
{
  F1_2022_OK = 0,
  F1_2022_NO_DATA,
  F1_2022_ERR_NO_MEM = 0x101,
  F1_2022_ERR_INVALID_ARG,
  F1_2022_FAIL = -1
} f1_2022_err_t;

#pragma pack(push, 1)
typedef struct
{
  uint16_t packetFormat;
  uint8_t gameMajorVersion;
  uint8_t gameMinorVersion;
  uint8_t packetVersion;

  uint8_t packetId;

  uint64_t sessionUID;
  float sessionTime;
  uint32_t frameIdentifier;

  uint8_t playerCarIndex;
  uint8_t secondaryPlayerCarIndex;
} f1_2022_header_t;

typedef struct
{
  uint16_t speedKPH;                                  // Speed of car in kilometres per hour
  float throttle;                                     // Amount of throttle applied (0.0 to 1.0)
  float steer;                                        // Steering (-1.0 (full lock left) to 1.0 (full lock right))
  float brake;                                        // Amount of brake applied (0.0 to 1.0)
  uint8_t clutch;                                     // Amount of clutch applied (0 to 100)
  int8_t gear;                                        // Gear selected (1-8, N=0, R=-1)
  uint16_t engineRPM;                                 // Engine RPM
  uint8_t drs;                                        // 0 = off, 1 = on
  uint8_t revLightsPercent;                           // Rev lights indicator (percentage)
  uint16_t revLightsBitValue;                         // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
  uint16_t brakesTemperature[F1_2022_NUM_TIRES];      // Brakes temperature (celsius)
  uint8_t tyresSurfaceTemperature[F1_2022_NUM_TIRES]; // Tyres surface temperature (celsius)
  uint8_t tyresInnerTemperature[F1_2022_NUM_TIRES];   // Tyres inner temperature (celsius)
  uint16_t engineTemperature;                         // Engine temperature (celsius)
  float tyresPressure[F1_2022_NUM_TIRES];             // Tyres pressure (PSI)
  uint8_t surfaceType[F1_2022_NUM_TIRES];             // Driving surface, see appendices
} f1_2022_telemetry_t;

typedef struct
{
  f1_2022_header_t header; // Header
  f1_2022_telemetry_t carTelemetryData[F1_2022_NUM_CARS];
  uint8_t mfdPanelIndex;                // Index of MFD panel open - 255 = MFD closed
                                        // Single player, race – 0 = Car setup, 1 = Pits
                                        //  2 = Damage, 3 =  Engine, 4 = Temperatures
                                        // May vary depending on game mode
  uint8_t mfdPanelIndexSecondaryPlayer; // See above
  int8_t suggestedGear;                 // Suggested gear for the player (1-8)
                                        // 0 if no gear suggested
} f1_2022_pckt_telemetry_t;

typedef struct
{
  uint32_t lastLapTimeInMS;            // Last lap time in milliseconds
  uint32_t currentLapTimeInMS;         // Current time around the lap in milliseconds
  uint16_t sector1TimeInMS;            // Sector 1 time in milliseconds
  uint16_t sector2TimeInMS;            // Sector 2 time in milliseconds
  float lapDistance;                   // Distance vehicle is around current lap in metres – could
                                       // be negative if line hasn’t been crossed yet
  float totalDistance;                 // Total distance travelled in session in metres – could
                                       // be negative if line hasn’t been crossed yet
  float safetyCarDelta;                // Delta in seconds for safety car
  uint8_t carPosition;                 // Car race position
  uint8_t currentLapNum;               // Current lap number
  uint8_t pitStatus;                   // 0 = none, 1 = pitting, 2 = in pit area
  uint8_t numPitStops;                 // Number of pit stops taken in this race
  uint8_t sector;                      // 0 = sector1, 1 = sector2, 2 = sector3
  uint8_t currentLapInvalid;           // Current lap invalid - 0 = valid, 1 = invalid
  uint8_t penalties;                   // Accumulated time penalties in seconds to be added
  uint8_t warnings;                    // Accumulated number of warnings issued
  uint8_t numUnservedDriveThroughPens; // Num drive through pens left to serve
  uint8_t numUnservedStopGoPens;       // Num stop go pens left to serve
  uint8_t gridPosition;                // Grid position the vehicle started the race in
  uint8_t driverStatus;                // Status of driver - 0 = in garage, 1 = flying lap
                                       // 2 = in lap, 3 = out lap, 4 = on track
  uint8_t resultStatus;                // Result status - 0 = invalid, 1 = inactive, 2 = active
                                       // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                       // 6 = not classified, 7 = retired
  uint8_t pitLaneTimerActive;          // Pit lane timing, 0 = inactive, 1 = active
  uint16_t pitLaneTimeInLaneInMS;      // If active, the current time spent in the pit lane in ms
  uint16_t pitStopTimerInMS;           // Time of the actual pit stop in ms
  uint8_t pitStopShouldServePen;       // Whether the car should serve a penalty at this stop
} f1_2022_lap_t;

typedef struct
{
  f1_2022_header_t header;                 // Header
  f1_2022_lap_t lapData[F1_2022_NUM_CARS]; // Lap data for all cars on track
} f1_2022_pckt_lap_t;

// Car Damage Packet
typedef struct
{
  float tyresWear[F1_2022_NUM_TIRES];      // Tyre wear (percentage)
  uint8_t tyresDamage[F1_2022_NUM_TIRES];  // Tyre damage (percentage)
  uint8_t brakesDamage[F1_2022_NUM_TIRES]; // Brakes damage (percentage)
  uint8_t frontLeftWingDamage;             // Front left wing damage (percentage)
  uint8_t frontRightWingDamage;            // Front right wing damage (percentage)
  uint8_t rearWingDamage;                  // Rear wing damage (percentage)
  uint8_t floorDamage;                     // Floor damage (percentage)
  uint8_t diffuserDamage;                  // Diffuser damage (percentage)
  uint8_t sidepodDamage;                   // Sidepod damage (percentage)
  uint8_t drsFault;                        // Indicator for DRS fault, 0 = OK, 1 = fault
  uint8_t gearBoxDamage;                   // Gear box damage (percentage)
  uint8_t engineDamage;                    // Engine damage (percentage)
  uint8_t engineMGUHWear;                  // Engine wear MGU-H (percentage)
  uint8_t engineESWear;                    // Engine wear ES (percentage)
  uint8_t engineCEWear;                    // Engine wear CE (percentage)
  uint8_t engineICEWear;                   // Engine wear ICE (percentage)
  uint8_t engineMGUKWear;                  // Engine wear MGU-K (percentage)
  uint8_t engineTCWear;                    // Engine wear TC (percentage)
} f1_2022_car_damage_t;

typedef struct
{
  f1_2022_header_t header; // Header
  f1_2022_car_damage_t carDamageData[F1_2022_NUM_CARS];
} f1_2022_pckt_car_damage_t;

typedef struct
{
  float worldPositionX;     // World space X position
  float worldPositionY;     // World space Y position
  float worldPositionZ;     // World space Z position
  float worldVelocityX;     // Velocity in world space X
  float worldVelocityY;     // Velocity in world space Y
  float worldVelocityZ;     // Velocity in world space Z
  int16_t worldForwardDirX; // World space forward X direction (normalised)
  int16_t worldForwardDirY; // World space forward Y direction (normalised)
  int16_t worldForwardDirZ; // World space forward Z direction (normalised)
  int16_t worldRightDirX;   // World space right X direction (normalised)
  int16_t worldRightDirY;   // World space right Y direction (normalised)
  int16_t worldRightDirZ;   // World space right Z direction (normalised)
  float gForceLateral;      // Lateral G-Force component
  float gForceLongitudinal; // Longitudinal G-Force component
  float gForceVertical;     // Vertical G-Force component
  float yaw;                // Yaw angle in radians
  float pitch;              // Pitch angle in radians
  float roll;               // Roll angle in radians
} f1_2022_car_motion_t;

typedef struct
{
  f1_2022_header_t header;                              // Header
  f1_2022_car_motion_t carMotionData[F1_2022_NUM_CARS]; // Data for all cars on track
                                                        // Extra player car ONLY data
  float suspensionPosition[F1_2022_NUM_TIRES];          // Note: All wheel arrays have the following order:
  float suspensionVelocity[F1_2022_NUM_TIRES];          // RL, RR, FL, FR
  float suspensionAcceleration[F1_2022_NUM_TIRES];      // RL, RR, FL, FR
  float wheelSpeed[F1_2022_NUM_TIRES];                  // Speed of each wheel
  float wheelSlip[F1_2022_NUM_TIRES];                   // Slip ratio for each wheel
  float localVelocityX;                                 // Velocity in local space
  float localVelocityY;                                 // Velocity in local space
  float localVelocityZ;                                 // Velocity in local space
  float angularVelocityX;                               // Angular velocity x-component
  float angularVelocityY;                               // Angular velocity y-component
  float angularVelocityZ;                               // Angular velocity z-component
  float angularAccelerationX;                           // Angular velocity x-component
  float angularAccelerationY;                           // Angular velocity y-component
  float angularAccelerationZ;                           // Angular velocity z-component
  float frontWheelsAngle;                               // Current front wheels angle in radians
} f1_2022_pckt_car_motion_t;
typedef struct
{
  uint8_t tractionControl;        // Traction control - 0 = off, 1 = medium, 2 = full
  uint8_t antiLockBrakes;         // 0 (off) - 1 (on)
  uint8_t fuelMix;                // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
  uint8_t frontBrakeBias;         // Front brake bias (percentage)
  uint8_t pitLimiterStatus;       // Pit limiter status - 0 = off, 1 = on
  float fuelInTank;               // Current fuel mass
  float fuelCapacity;             // Fuel capacity
  float fuelRemainingLaps;        // Fuel remaining in terms of laps (value on MFD)
  uint16_t maxRPM;                // Cars max RPM, point of rev limiter
  uint16_t idleRPM;               // Cars idle RPM
  uint8_t maxGears;               // Maximum number of gears
  uint8_t drsAllowed;             // 0 = not allowed, 1 = allowed
  uint16_t drsActivationDistance; // 0 = DRS not available, non-zero - DRS will be available
                                  // in [X] metres
  uint8_t actualTyreCompound;     // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
                                  // 7 = inter, 8 = wet
                                  // F1 Classic - 9 = dry, 10 = wet
                                  // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
                                  // 15 = wet
  uint8_t visualTyreCompound;     // F1 visual (can be different from actual compound)
                                  // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                  // F1 Classic – same as above
                                  // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                  // 21 = medium , 22 = hard
  uint8_t tyresAgeLaps;           // Age in laps of the current set of tyres
  int8_t vehicleFiaFlags;         // -1 = invalid/unknown, 0 = none, 1 = green
                                  // 2 = blue, 3 = yellow, 4 = red
  float ersStoreEnergy;           // ERS energy store in Joules
  uint8_t ersDeployMode;          // ERS deployment mode, 0 = none, 1 = medium
                                  // 2 = hotlap, 3 = overtake
  float ersHarvestedThisLapMGUK;  // ERS energy harvested this lap by MGU-K
  float ersHarvestedThisLapMGUH;  // ERS energy harvested this lap by MGU-H
  float ersDeployedThisLap;       // ERS energy deployed this lap
  uint8_t networkPaused;          // Whether the car is paused in a network game
} f1_2022_car_status_t;

typedef struct
{
  f1_2022_header_t header; // Header
  f1_2022_car_status_t carStatusData[F1_2022_NUM_CARS];
} f1_2022_pckt_car_status_t;
#pragma pack(pop)

f1_2022_err_t F1_2022_PacketParser(const void *data, size_t len);
f1_2022_err_t F1_2022_GetTelemetry(f1_2022_pckt_telemetry_t *telemetry);
f1_2022_err_t F1_2022_GetLap(f1_2022_pckt_lap_t *lap);
f1_2022_err_t F1_2022_GetCarDamage(f1_2022_pckt_car_damage_t *damage);
f1_2022_err_t F1_2022_GetCarMotion(f1_2022_pckt_car_motion_t *motion);
f1_2022_err_t F1_2022_GetCarStatus(f1_2022_pckt_car_status_t *status);

#endif // F1_2022_H
