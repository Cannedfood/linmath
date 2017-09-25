#pragma once

/* This header converts a variety of units into SI units and constants.
 * It does NOT use any compile time type checks
 * Usage examples:
 *    1 Nautical mile in the base unit (meters)
 *          float f = 1.0_nmi;
 *      or
 *          float f = 1.0_nautical_mile;
 *    Converting between units:
 *          float cm, inch = 15;
 *          cm = inch * (1.0_inch / 1.0_cm);
 * !!!! This conversion does not work for Temperature (Mostly because 0° is not the same over all units)
 */

namespace stx {

using unit_t    = long double;

// =============================================================
// == Constants =============================================
// =============================================================

namespace constants {

constexpr static unit_t G_earth   = static_cast<unit_t>(9.80665L);
constexpr static unit_t G_moon    = static_cast<unit_t>(1.622L);
constexpr static unit_t G_mars    = static_cast<unit_t>(3.711L);
constexpr static unit_t G_jupiter = static_cast<unit_t>(24.79L);

constexpr static unit_t G = static_cast<unit_t>(6.67408e-11L);

constexpr static unit_t c = 299792458.0;

constexpr static unit_t pi = 3.14159265359L;

} // namespace constants

// =============================================================
// == SI units =============================================
// =============================================================

// -- Mass -- Base unit: kilogram (kg) ------------------------------------------------------
constexpr inline
unit_t operator "" _megatons(long double d) noexcept { return static_cast<unit_t>(d * 1.0e6L); }
constexpr inline
unit_t operator "" _kilotons(long double d) noexcept { return static_cast<unit_t>(d * 1000.0L); }
constexpr inline // SI Tons
unit_t operator "" _tons(long double d) noexcept { return static_cast<unit_t>(d * 1000.0L); }
constexpr inline // Kilogram
unit_t operator "" _kilograme(long double d) noexcept { return static_cast<unit_t>(d); }
constexpr inline // Kilogram
unit_t operator "" _kg(long double d) noexcept { return static_cast<unit_t>(d); }
constexpr inline // Gram
unit_t operator "" _gram(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline // Gram
unit_t operator "" _g(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline // Milligram
unit_t operator "" _milligram(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline // Milligram
unit_t operator "" _mg(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline // Microgram
unit_t operator "" _microgram(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline // Microgram
unit_t operator "" _ug(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline // Nanogram
unit_t operator "" _nanogram(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-12L); }
constexpr inline // Nanogram
unit_t operator "" _ng(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-12L); }

// -- Distance -- Base unit: meter (m)-------------------------------------------------------
constexpr inline
unit_t operator "" _millimeter(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline
unit_t operator "" _mm(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline
unit_t operator "" _centimeter(long double d) noexcept { return static_cast<unit_t>(d * 0.01L); }
constexpr inline
unit_t operator "" _cm(long double d) noexcept { return static_cast<unit_t>(d * 0.01L); }
constexpr inline
unit_t operator "" _decimeter(long double d) noexcept { return static_cast<unit_t>(d * 0.1L); }
constexpr inline
unit_t operator "" _dm(long double d) noexcept { return static_cast<unit_t>(d * 0.1L); }
constexpr inline
unit_t operator "" _meter(long double d)  noexcept { return static_cast<unit_t>(d); }
constexpr inline
unit_t operator "" _m(long double d)  noexcept { return static_cast<unit_t>(d); }
constexpr inline
unit_t operator "" _kilometer(long double d) noexcept { return static_cast<unit_t>(d * 1000.0L); }
constexpr inline
unit_t operator "" _km(long double d) noexcept { return static_cast<unit_t>(d * 1000.0L); }

// -- Time -- Base unit: seconds (s) ------------------------------------------------------
constexpr inline
unit_t operator "" _hours(long double d) noexcept { return static_cast<unit_t>(d * 60.0L * 60.0L); }
constexpr inline
unit_t operator "" _h(long double d) noexcept { return static_cast<unit_t>(d * 60.0L * 60.0L); }
constexpr inline
unit_t operator "" _minutes(long double d) noexcept { return static_cast<unit_t>(d * 60.0L); }
constexpr inline
unit_t operator "" _min(long double d) noexcept { return static_cast<unit_t>(d * 60.0L); }
constexpr inline
unit_t operator "" _seconds(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline
unit_t operator "" _s(long double d) noexcept { return static_cast<unit_t>(d * 0.001L); }
constexpr inline
unit_t operator "" _milliseconds(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline
unit_t operator "" _ms(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline
unit_t operator "" _microseconds(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline
unit_t operator "" _us(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-6L); }
constexpr inline
unit_t operator "" _nanoseconds(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-12L); }
constexpr inline
unit_t operator "" _ns(long double d) noexcept { return static_cast<unit_t>(d * 1.0e-12L); }

// -- Speed -- Base unit: meters per second (m/s or mps)----------------------------------------------------
constexpr inline
unit_t operator "" _meters_per_second(long double d) noexcept { return static_cast<unit_t>(d); }
constexpr inline
unit_t operator "" _mps(long double d) noexcept { return static_cast<unit_t>(d); }
constexpr inline
unit_t operator "" _kilometers_per_hour(long double d) noexcept { return static_cast<unit_t>(d * (1.0_km / 1.0_h)); }
constexpr inline
unit_t operator "" _kmh(long double d) noexcept { return static_cast<unit_t>(d * (1.0_km / 1.0_h)); }

// -- Temperature -------------------------------------------------------
constexpr inline
unit_t operator "" _kelvin(long double d) noexcept { return static_cast<unit_t>(d); }
constexpr inline
unit_t operator "" _k(long double d) noexcept { return static_cast<unit_t>(d); }

constexpr inline
unit_t operator "" _degree_celsius(long double d) noexcept { return static_cast<unit_t>(d + 273.15L); }
constexpr inline
unit_t operator "" _C(long double d) noexcept { return static_cast<unit_t>(d + 273.15L); }

// =============================================================
// == US units =============================================
// =============================================================

// -- Mass -------------------------------------------------------
constexpr inline
unit_t operator "" _ounce(long double d) noexcept { return static_cast<unit_t>(d * 28.349523125_g); }
constexpr inline
unit_t operator "" _oz(long double d)    noexcept { return static_cast<unit_t>(d * 28.349523125_g); }
constexpr inline
unit_t operator "" _pound(long double d) noexcept { return static_cast<unit_t>(d * 453.59237_g); }
constexpr inline
unit_t operator "" _lb(long double d) noexcept { return static_cast<unit_t>(d * 453.59237_g); }

// -- Distance -------------------------------------------------------
constexpr inline
unit_t operator "" _inch(long double d) noexcept { return static_cast<unit_t>(d * 25.4_mm); }
constexpr inline
unit_t operator "" _in(long double d) noexcept { return static_cast<unit_t>(d * 25.4_mm); }
constexpr inline
unit_t operator "" _foot(long double d) noexcept { return static_cast<unit_t>(d * 0.304_m); }
constexpr inline
unit_t operator "" _ft(long double d) noexcept { return static_cast<unit_t>(d * 0.304_m); }
constexpr inline
unit_t operator "" _yard(long double d) noexcept { return static_cast<unit_t>(d * 0.9144_m); }
constexpr inline
unit_t operator "" _yd(long double d) noexcept { return static_cast<unit_t>(d * 0.9144_m); }
constexpr inline // International mile
unit_t operator "" _mile(long double d) noexcept { return static_cast<unit_t>(d * 1.609344_km); }
constexpr inline // International mile
unit_t operator "" _mi(long double d) noexcept { return static_cast<unit_t>(d * 1.609344_km); }

// -- Speed -------------------------------------------------------
constexpr inline
unit_t operator "" _miles_per_hour(long double d) noexcept { return static_cast<unit_t>(d * (1.0_mile / 1.0_h)); }
constexpr inline
unit_t operator "" _mph(long double d) noexcept { return static_cast<unit_t>(d * (1.0_mile / 1.0_h)); }

// -- Temperature -------------------------------------------------------
constexpr inline
unit_t operator "" _degree_fahrenheit(long double d) noexcept { return static_cast<unit_t>((d + 459.67L) * 5.0L / 9.0L); }
constexpr inline
unit_t operator "" _F(long double d) noexcept { return static_cast<unit_t>(d); }

// =============================================================
// == Nautical units =============================================
// =============================================================

// -- Distance -------------------------------------------------------
constexpr inline // Nautical mile
unit_t operator "" _nautical_mile(long double d) noexcept { return static_cast<unit_t>(d * 1.609344_km); }
constexpr inline // Nautical mile
unit_t operator "" _nmi(long double d) noexcept { return static_cast<unit_t>(d * 1.609344_km); }
// -- Speeds -------------------------------------------------------
constexpr inline // Nautical mile
unit_t operator "" _nautical_mile_per_hour(long double d) noexcept { return static_cast<unit_t>(d * 1.0_nmi / 1.0_hours); }
constexpr inline // Nautical mile
unit_t operator "" _nmiph(long double d) noexcept { return static_cast<unit_t>(d * 1.0_nmi / 1.0_hours); }

// =============================================================
// == Memory units =============================================
// =============================================================

using byte_unit_t = size_t;

constexpr inline
byte_unit_t operator "" _byte(unsigned long long n) { return n; }

// Higher units (1000 base)
constexpr inline
byte_unit_t operator "" _kilobyte(unsigned long long n) { return n * 1000_byte; }
constexpr inline
byte_unit_t operator "" _megabyte(unsigned long long n) { return n * 1000_kilobyte; }
constexpr inline
byte_unit_t operator "" _gigabyte(unsigned long long n) { return n * 1000_megabyte; }
constexpr inline
byte_unit_t operator "" _terabyte(unsigned long long n) { return n * 1000_gigabyte; }

// Higher units (1024 base)
constexpr inline
byte_unit_t operator "" _kibibyte(unsigned long long n) { return n * 1024_byte; }
constexpr inline
byte_unit_t operator "" _mebibyte(unsigned long long n) { return n * 1024_kibibyte; }
constexpr inline
byte_unit_t operator "" _gibibyte(unsigned long long n) { return n * 1024_mebibyte; }
constexpr inline
byte_unit_t operator "" _tebibyte(unsigned long long n) { return n * 1024_gibibyte; }

// =============================================================
// == Angles =============================================
// =============================================================

unit_t operator "" _deg(long double d) noexcept { return static_cast<unit_t>(d * M_PI / 180); }

} // namespace stx
