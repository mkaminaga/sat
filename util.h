  // @file util.h
  // @brief The utility for satellite position simulation.
  // @author Mamoru Kaminaga
  // @date 2017-09-08 17:02:36
  // Copyright 2017 Mamoru Kaminaga
#ifndef UTIL_H_
#define UTIL_H_
namespace sat {
struct Point3 {
  double x;
  double y;
  double z;
};
struct WGS84Point {
  double lambda;  // The longitude (rad).
  double phi;  // The latitude (rad).
  double h;  // The height from the sea level (m).
};
struct WiewedPoint {
  double rho;  // The distance the satellite (m).
  double az;  // The azimuth of the satellite (rad).
  double el;  // The elevation of the satellite (rad).
};
struct Calendar {
  int year;  // The value of year.
  int mon;  // The value of month.
  int day;  // The value of date.
  int hour;  // The value of hour.
  int min;  // The value of minute.
  double sec;  // The value of second.
};
void RotX(double t, Point3* v);
void RotY(double t, Point3* v);
void RotZ(double t, Point3* v);
void ECIToECEF(const Point3& r, double jd, Point3* p);
void WGS84ToECEF(const WGS84Point& w, Point3* p);
void ViewSat(const WGS84Point& w, const Point3& ps, WiewedPoint* q);
void DaysToMonDayHourMinSec(int year, double days, int* mon, int* day,
                            int* hour, int* min, double* sec);
double ToJulianDay(const Calendar& cal);
void ToCalendar(double jd, Calendar* cal);
double GetGSTime(double jd);
}  // namespace sat
#endif  // UTIL_H_
