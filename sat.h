  // @file sat.h
  // @brief The satellite simulation functions.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 17:02:36
  // Copyright 2017 Mamoru Kaminaga
#ifndef SAT_H_
#define SAT_H_
#include <tle/v2.1.0/tle.h>
#include "./util.h"
namespace sat {
struct SatData {
  int error;
  // Basic elements in the epoch.
  double jdepoch;  // The original epoch of the TLE (JD).
  double argpo;  // The original argument of perigee (rad).
  double inclo;  // The original inclination angle (rad).
  double nodeo;  // The original right ascension of ascending node (rad).
  double ecco;  // The original eccentricity.
  double mo;  // The original mean anomaly (rev).
  double no;  // The original mean motion (rev/day).
  double ndoto;  // The original mean motion deferential (rev/day^2).
  double nddoto;  // The original mean motion deferential (rev/day^3).
  double ao;  // The semi-major axis (m).
  double argp1;  // The precession rate due to J2 for argp (rad/day).
  double node1;  // The precession rate due to J2 for node (rad/day).
  // Basic elements at given JD.
  double jd;  // The epoch of the data (JD).
  double m;  // The mean anomaly (rev).
  double n;  // The mean motion (rev/day).
  double argp;  // The argument of perigee (rad).
  double node;  // The right ascension of ascending node (rad).
  // Other information.
  double e;  // The eccentric anomaly (rad).
  Point3 u;  // The position in the orbit plane (m).
  Point3 r;  // The position in the ECI system (m).
  Point3 p;  // The velocity in the ECEF system (m).
};
bool InitSat(const TLEData& tle, SatData* sat);
bool GetSatPos(double jd, SatData* sat);
}  // namespace sat
#endif  // SAT_H_
