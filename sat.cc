  // @file sat.cc
  // @brief The satellite simulation functions.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 17:02:36
  // Copyright 2017 Mamoru Kaminaga
#include <assert.h>
#include <tle/v2.1.0/tle.h>
#include <cmath>
#include "./data.h"
#include "./sat.h"
#include "./util.h"
namespace {
bool Newton(double m, double eccn, double* e) {
  assert(e);
  m = SAT_REV_TO_RADIANS(m);
  double eo = 0.0;  // The original value.
  *e = m;  // The new value.
  for (int i = 0; std::fabs(*e - eo) > 1.0E-8; ++i) {
    eo = *e;
    if (i > 10000) return false;  // The newton method is failed.
    *e = eo - (eo - eccn * std::sin(eo) - m) / (1.0 - eccn * std::cos(eo));
  }
  return true;
}
}  // namespace
namespace sat {
bool InitSat(const TLEData& tle, SatData* sat) {
  assert(sat);
  sat->error = 0;
  // The epoch is set in JD.
  Calendar cal;
  if (tle.epoch_year < 57) {
    cal.year = tle.epoch_year + 2000;
  } else {
    cal.year = tle.epoch_year + 1900;
  }
  DaysToMonDayHourMinSec(cal.year, tle.epoch_days, &cal.mon, &cal.day,
                         &cal.hour, &cal.min, &cal.sec);
  sat->jdepoch = ToJulianDay(cal);

  // Units are converted.
  sat->argpo = SAT_TO_RADIANS(tle.argpo);
  sat->inclo = SAT_TO_RADIANS(tle.inclo);
  sat->nodeo = SAT_TO_RADIANS(tle.nodeo);
  sat->mo = SAT_DEGREES_TO_REV(tle.mo);
  sat->ecco = tle.ecco;
  sat->no = tle.no;
  sat->ndoto = tle.ndot;
  sat->nddoto = tle.nddot;
  // The semi-major axis is derived.
  constexpr double gm = SAT_WGS84_GM * 7464960000.0;  // To m^3/day^3.
  sat->ao = std::pow(gm / (4.0 * SAT_PI * SAT_PI * sat->no * sat->no),
                     1.0 / 3.0);
  // The initial values are set.
  if (!GetSatPos(sat->jdepoch, sat)) return false;
  return true;
}
bool GetSatPos(double jd, SatData* sat) {
  assert(sat);
  sat->jd = jd;
  double t = jd - sat->jdepoch;
  // The mean motion is derived.
  sat->n = sat->no + sat->ndoto * t;
  // The mean anomaly is derived.
  sat->m = sat->mo + sat->no * t + 0.5 * sat->ndoto * t * t;
  sat->m = sat->m - std::floor(sat->m);  // Decimals are removed.
  // The eccentric anomaly is derived.
  if (!Newton(sat->m, sat->ecco, &sat->e)) {
    sat->error = 1;
    return false;
  }
  // The position in the orbit plane is derived.
  sat->u.x = sat->ao * (std::cos(sat->e) - sat->ecco);
  sat->u.y = sat->ao * std::sqrt(1.0 - sat->ecco * sat->ecco) * std::sin(sat->e);
  sat->u.z = 0.0;
  // The precession rate due to J2 for node and argp is derived.
  const double n = SAT_REV_TO_RADIANS(sat->n);
  const double c = std::cos(sat->inclo);
  const double s = std::sin(sat->inclo);
  const double cnst = 1.5 * SAT_J2 * n * SAT_WGS84_A * SAT_WGS84_A /
    (sat->ao * sat->ao * (1.0 - sat->ecco * sat->ecco) *
     (1.0 - sat->ecco * sat->ecco));
  sat->node1 = -cnst * c;
  sat->argp1 = cnst * (2.0 - 2.5 * s * s);
  // The precession rate due to J2 for node and argp.
  sat->node = sat->nodeo + sat->node1 * t;
  sat->argp = sat->argpo + sat->argp1 * t;
  // The values are 0-2pi.
  if (sat->argp > (SAT_PI * 2.0)) sat->argp -= SAT_PI * 2.0;
  if (sat->argp < 0.0) sat->argp += SAT_PI * 2.0;
  if (sat->node > (SAT_PI * 2.0)) sat->node -= SAT_PI * 2.0;
  if (sat->node < 0.0) sat->node += SAT_PI * 2.0;
  // The position in the ECI system is derived.
  sat->r = sat->u;
  RotZ(sat->argp, &sat->r);
  RotX(sat->inclo, &sat->r);
  RotZ(sat->node, &sat->r);
  // The position in the ECEF system is derived.
  sat->p = sat->r;
  RotZ(-GetGSTime(jd), &sat->p);
  return true;
}
}  // namespace sat
