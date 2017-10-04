  // @file data.h
  // @brief The common constants and macros.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 17:29:46
  // Copyright 2017 Mamoru Kaminaga
#ifndef DATA_H_
#define DATA_H_
  // The basic constants and macros.
#define SAT_PI                (3.14159265358979)
#define SAT_DAY_TO_MIN(n)     ((n) * 1440.0)
#define SAT_MIN_TO_DAY(n)     ((n) / 1440.0)
#define SAT_TO_DEGREES(n)     ((n) * 180.0 / SAT_PI)
#define SAT_TO_RADIANS(n)     ((n) * SAT_PI / 180.0)
#define SAT_REV_TO_RADIANS(n) ((n) * SAT_PI * 2.0)
#define SAT_REV_TO_DEGREES(n) ((n) * 360.0)
#define SAT_RADIANS_TO_REV(n) ((n) / (SAT_PI * 2.0))
#define SAT_DEGREES_TO_REV(n) ((n) / 360.0)
  // Constants for WGS-84.
#define SAT_WGS84_A           (6378137.00000)  // Unit: m
#define SAT_WGS84_B           (6356752.31425)  // Unit: m
#define SAT_WGS84_F           (3.35281066474E-3)
#define SAT_WGS84_E2          (6.69437999013E-3)
#define SAT_WGS84_E3          (6.73949674226E-3)
#define SAT_WGS84_OMEGA       (7292115.1467E-11)  // Unit: rad/s
#define SAT_WGS84_GM          (3.98600441E+14)  // Unit: m^3/s^2
#define SAT_WGS84_C           (299792458)  // Unit: m/s
  // The scientific values.
#define SAT_J2                (0.00108262998905)  // The zonal harmonic values
#define SAT_KJ2               (2.06474E+14)  // The zonal harmonic values
  // The conversion between MJD and JD.
#define SAT_JD_TO_MJD(n)      ((n)-2400000.5)
#define SAT_MJD_TO_JD(n)      ((n)+2400000.5)
  // The constants used to get the ascending node of the Greenwich meridian.
#define SAT_REV_A_DAY         (1.002737909)
  // SGP4 error messages.
#define SAT_ERR_1 L"mean elements, ecc >= 1.0 or ecc < -0.001 or a < 0.95 er"
#define SAT_ERR_2 L"mean motion less than 0.0"
#define SAT_ERR_3 L"pert elements, ecc < 0.0  or  ecc > 1.0"
#define SAT_ERR_4 L"semi-latus rectum < 0.0"
#define SAT_ERR_5 L"epoch elements are sub-orbital"
#define SAT_ERR_6 L"satellite has decayed"
#endif  // DATA_H_
