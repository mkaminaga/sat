  // @brief The test program for this library.
  // TLE comes from http://www.celestrak.com/publications/AIAA/2006-6753/.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 16:05:35
  // Copyright 2017 Mamoru Kaminaga
#include <tle/v2.1.0/tle.h>
#include "./data.h"
#include "./sat.h"
#include "./util.h"
#ifdef WIN32
int wmain(int argc, char* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif

  sat::TLEDesc desc;
  desc.line_0 = L"FO-29                   ";
  desc.line_1 = L"1 24278U 96046B   03232.95303700 -.00000056  00000-0 -24068-4 0 06270";  // NOLINT
  desc.line_2 = L"2 24278 098.5660 359.5477 0351513 101.3348 262.7487 13.52885302346104";  // NOLINT

  wprintf(L"TLE used for the calculation.\n");
  wprintf(L"%ls\n", desc.line_0.c_str());
  wprintf(L"%ls\n", desc.line_1.c_str());
  wprintf(L"%ls\n", desc.line_2.c_str());

  sat::TLEData tle;
  sat::ReadTLE(desc, &tle);

  // The satellite orbit information is acquired.
  sat::SatData sat;
  sat::InitSat(tle, &sat);

  // The observation point data is set.
  sat::WGS84Point wo;  // WGS-84.
  wo.lambda = SAT_TO_RADIANS(139.634385);
  wo.phi = SAT_TO_RADIANS(35.7760287);
  wo.h = 40.0;

  const double mjd[3] = {
    52871.953037,  // The epoch.
    52872.453037,  // The epoch + 12h.
    52875.233037,  // The epoch + 3days.
  };
  double jd = 0.0;
  sat::WiewedPoint q;  // The position of the satellite in the HCS system.
  for (int i = 0; i < 3; ++i) {
    jd = SAT_MJD_TO_JD(mjd[i]);
    if (!sat::GetSatPos(jd, &sat)) {
      wprintf(L"Failure... Newton methot not converged");
      continue;
    }
    wprintf(L"\n");
    wprintf(L"--------------------\n");
    wprintf(L"MJD(epoch) %.8f\n", SAT_JD_TO_MJD(sat.jd));
    wprintf(L"incl(rad) %.8f\n", sat.inclo);
    wprintf(L"ennc %.8f\n", sat.ecco);
    wprintf(L"n(rev/day) %.8f\n", sat.n);
    wprintf(L"n(rad) %.8f\n", SAT_REV_TO_RADIANS(sat.m));
    wprintf(L"a(m) %.8f\n", sat.ao);
    wprintf(L"node(rad) %.8f\n", sat.node);
    wprintf(L"argp(rad) %.8f\n", sat.argp);

    wprintf(L"\n");
    wprintf(L"E(rad) %.8f\n", sat.e);
    wprintf(L"orbit plane X(m) %.8f\n", sat.u.x);
    wprintf(L"orbit plane Y(m) %.8f\n", sat.u.y);

    wprintf(L"\n");
    wprintf(L"ECI X(m) %.8f\n", sat.r.x);
    wprintf(L"ECI Y(m) %.8f\n", sat.r.y);
    wprintf(L"ECI Z(m) %.8f\n", sat.r.z);

    wprintf(L"\n");
    wprintf(L"theta g(rad) %.8f\n", sat::GetGSTime(jd));
    wprintf(L"ECEF X(m) %.8f\n", sat.p.x);
    wprintf(L"ECEF Y(m) %.8f\n", sat.p.y);
    wprintf(L"ECEF Z(m) %.8f\n", sat.p.z);

    // The satellite position in the HCS system is derived.
    sat::ViewSat(wo, sat.p, &q);
    wprintf(L"\n");
    wprintf(L"lambda(deg) %.8f\n", SAT_TO_DEGREES(wo.lambda));
    wprintf(L"phi(deg) %.8f\n", SAT_TO_DEGREES(wo.phi));
    wprintf(L"dist(m) %.8f\n", q.rho);
    wprintf(L"az(deg) %.8f\n", SAT_TO_DEGREES(q.az));
    wprintf(L"el(deg) %.8f\n", SAT_TO_DEGREES(q.el));

    wprintf(L"\n");
  }
  return 0;
}
