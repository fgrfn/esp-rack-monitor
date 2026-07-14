#pragma once

#include "esphome.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>

namespace rack_monitor {

inline bool valid(float value) { return std::isfinite(value); }

inline int bar_width(float value, float maximum, int width) {
  if (!valid(value) || maximum <= 0.0f || width <= 0) return 0;
  const float ratio = std::clamp(value / maximum, 0.0f, 1.0f);
  return static_cast<int>(std::round(ratio * width));
}

inline esphome::Color threshold_color(float value, float warn, float critical,
                                      esphome::Color ok, esphome::Color warning,
                                      esphome::Color danger) {
  if (!valid(value)) return warning;
  if (value >= critical) return danger;
  if (value >= warn) return warning;
  return ok;
}

inline esphome::Color power_color(float value, float low, float warn, float critical,
                                  esphome::Color ok, esphome::Color normal,
                                  esphome::Color warning, esphome::Color danger) {
  if (!valid(value)) return warning;
  if (value >= critical) return danger;
  if (value >= warn) return warning;
  if (value >= low) return normal;
  return ok;
}

inline const char *power_status(float value, float low, float warn, float critical) {
  if (!valid(value)) return "STALE";
  if (value >= critical) return "KRITISCH";
  if (value >= warn) return "HOCH";
  if (value >= low) return "NORMAL";
  return "NIEDRIG";
}

inline const char *threshold_status(float value, float warn, float critical) {
  if (!valid(value)) return "STALE";
  if (value >= critical) return "KRITISCH";
  if (value >= warn) return "HOCH";
  return "NORMAL";
}

inline bool in_night_window(int hour, int start_hour, int end_hour) {
  if (start_hour == end_hour) return true;
  if (start_hour < end_hour) return hour >= start_hour && hour < end_hour;
  return hour >= start_hour || hour < end_hour;
}

inline std::string uptime_text(float seconds) {
  if (!valid(seconds) || seconds < 0.0f) return "--";
  const unsigned long total = static_cast<unsigned long>(seconds);
  const unsigned long days = total / 86400UL;
  const unsigned long hours = (total % 86400UL) / 3600UL;
  const unsigned long minutes = (total % 3600UL) / 60UL;
  char buffer[24];
  if (days > 0) {
    std::snprintf(buffer, sizeof(buffer), "%lud %02luh", days, hours);
  } else {
    std::snprintf(buffer, sizeof(buffer), "%02luh %02lum", hours, minutes);
  }
  return std::string(buffer);
}

template<typename DisplayT, typename LargeFontT, typename SmallFontT, typename TimeT>
inline void draw_header(DisplayT &it, LargeFontT large_font, SmallFontT small_font,
                        esphome::Color background, esphome::Color foreground,
                        const char *title, const TimeT &now, bool auto_rotate,
                        bool alarm_active) {
  it.filled_rectangle(0, 0, 320, 28, background);
  it.print(8, 5, large_font, foreground, title);
  if (now.is_valid()) {
    it.strftime(248, 7, small_font, foreground, "%H:%M", now);
  } else {
    it.print(248, 7, small_font, foreground, "--:--");
  }
  if (auto_rotate) it.print(294, 7, small_font, foreground, "A");
  if (alarm_active) it.print(309, 7, small_font, foreground, "!");
}

template<typename DisplayT, typename FontT>
inline void draw_button_hints(DisplayT &it, FontT font, esphome::Color color,
                              bool auto_rotate, bool alarm_active) {
  it.print(3, 34, font, color, ">");
  it.print(3, 154, font, color, auto_rotate ? "A" : "-");
  if (alarm_active) it.print(3, 94, font, color, "!");
}

template<typename DisplayT>
inline void draw_bar(DisplayT &it, int x, int y, int width, int height,
                     float value, float maximum, esphome::Color border,
                     esphome::Color fill) {
  it.rectangle(x, y, width, height, border);
  const int filled = bar_width(value, maximum, width);
  if (filled > 0) it.filled_rectangle(x, y, filled, height, fill);
}

}  // namespace rack_monitor
