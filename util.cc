  // @file util.h
  // @brief The utility for satellite position simulation.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 17:02:36
  // Copyright 2017 Mamoru Kaminaga
#include <assert.h>
#include <cmath>
#include "./util.h"
#include "./data.h"
namespace sat {
void RotX(double t, Point3* v) {
  assert(v);
  double c = std::cos(t);
  double s = std::sin(t);
  Point3 r = *v;
  v->x = r.x;
  v->y = c * r.y - s * r.z;
  v->z = s * r.y + c * r.z;
}
void RotY(double t, Point3* v) {
  assert(v);
  double c = std::cos(t);
  double s = std::sin(t);
  Point3 r = *v;
  v->x = c * r.x + s * r.z;
  v->y = r.y;
  v->z = - s * r.x + c * r.z;
}
void RotZ(double t, Point3* v) {
  assert(v);
  double c = std::cos(t);
  double s = std::sin(t);
  Point3 r = *v;
  v->x = c * r.x - s * r.y;
  v->y = s * r.x + c * r.y;
  v->z = r.z;
}
void ECIToECEF(const Point3& r, double jd, Point3* p) {
  assert(p);
  p->x = r.x;
  p->y = r.y;
  p->z = r.z;
  RotZ(-GetGSTime(jd), p);
}
void WGS84ToECEF(const WGS84Point& w, Point3* p) {
  assert(p);
  constexpr double aa = SAT_WGS84_A * SAT_WGS84_A;
  constexpr double bb = SAT_WGS84_B * SAT_WGS84_B;
  const double cp = std::cos(w.phi);
  const double sp = std::sin(w.phi);
  const double cl = std::cos(w.lambda);
  const double sl = std::sin(w.lambda);
  const double n = aa / std::sqrt(aa * cp * cp + bb * sp * sp);
  p->x = (n + w.h) * cp * cl;
  p->y = (n + w.h) * cp * sl;
  p->z = (bb / aa * n + w.h) * sp;
}
void ViewSat(const WGS84Point& w, const Point3& ps, WiewedPoint* q) {
  assert(q);
  // The observation position in ECEF system is acquired.
  Point3 po;
  WGS84ToECEF(w, &po);
  // The direction vector in the ECEF system is acquired.
  Point3 rho;
  rho.x = ps.x - po.x;
  rho.y = ps.y - po.y;
  rho.z = ps.z - po.z;
  // The coordinate transformation is done.
  RotZ(-w.lambda, &rho);
  RotY(-(SAT_PI * 0.5 - w.phi), &rho);
  // The elevation, azimuth and the distance is acquired.
  const double xx = rho.x * rho.x;
  const double yy = rho.y * rho.y;
  q->rho = std::sqrt(xx + yy + rho.z * rho.z);
  q->az = SAT_PI - std::atan2(rho.y, rho.x);
  if ((xx + yy) < 1E-8) {
    q->el = SAT_PI / 2.0;
  } else {
    q->el = std::atan(rho.z / std::sqrt(xx + yy));
  }
}
void DaysToMonDayHourMinSec(int year, double days, int* mon, int* day,
                            int* hour, int* min, double* sec) {
  int list[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if ((year % 4) == 0) list[1] = 29;
  const int days_in_a_year = static_cast<int>(std::floor(days));
  // Month and day is acquired.
  int i = 1;
  int days_sum = 0;
  while ((days_in_a_year > (days_sum + list[i - 1])) && (i < 12)) {
    days_sum = days_sum + list[i - 1];
    i++;
  }
  *mon = i;
  *day = days_in_a_year - days_sum;
  // Hour, minute and second is acquired.
  double tmp = (days - days_in_a_year) * 24.0;
  *hour = static_cast<int>(std::floor(tmp));
  tmp = (tmp - *hour) * 60.0;
  *min = static_cast<int>(std::floor(tmp));
  *sec = (tmp - *min) * 60.0;
}
double ToJulianDay(const Calendar& cal) {
  double jd = 367.0 * cal.year;
  jd -= std::floor((7 * (cal.year + std::floor((cal.mon + 9) / 12.0))) * 0.25);
  jd += std::floor(275 * cal.mon / 9.0) + cal.day + 1721013.5;
  jd += ((cal.sec / 60.0 + cal.min) / 60.0 + cal.hour) / 24.0;
  return jd;
}
void ToCalendar(double jd, Calendar* cal) {
  // Year and days of the year.
  double tmp = jd - 2415019.5;
  double year_1900 = tmp / 365.25;
  cal->year = 1900 + static_cast<int>(std::floor(year_1900));
  int leap_years = static_cast<int>(std::floor((cal->year - 1901) * 0.25));
  double days = tmp - ((cal->year - 1900) * 365.0 + leap_years) + 1.0E-11;
  // Beginning of a year.
  if (days < 1.0) {
    cal->year = cal->year - 1;
    leap_years = static_cast<int>(std::floor((cal->year - 1901) * 0.25));
    days = tmp - ((cal->year - 1900) * 365.0 + leap_years);
  }
  DaysToMonDayHourMinSec(cal->year, days, &cal->mon, &cal->day, &cal->hour,
                         &cal->min, &cal->sec);
  cal->sec = cal->sec - 8.64E-7;  // Nudge.
}
double GetGSTime(double jd) {
  double rev = 0.671262 + SAT_REV_A_DAY * (SAT_JD_TO_MJD(jd) - 40000.0);
  return SAT_REV_TO_RADIANS(rev - std::floor(rev));
}
}  // namespace sat
