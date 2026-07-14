#pragma once

#include "esphome.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>

namespace rack_monitor {

enum AlarmBit : uint32_t {
  ALARM_API_OFFLINE       = 1u << 0,
  ALARM_DATA_STALE        = 1u << 1,
  ALARM_HOST1_OFFLINE     = 1u << 2,
  ALARM_HOST2_OFFLINE     = 1u << 3,
  ALARM_HOST3_OFFLINE     = 1u << 4,
  ALARM_POWER_TOTAL       = 1u << 5,
  ALARM_TEMP_RACK         = 1u << 6,
  ALARM_TEMP_HOST1        = 1u << 7,
  ALARM_TEMP_HOST2        = 1u << 8,
  ALARM_TEMP_HOST3        = 1u << 9,
  ALARM_CPU_HOST1         = 1u << 10,
  ALARM_CPU_HOST2         = 1u << 11,
  ALARM_CPU_HOST3         = 1u << 12,
  ALARM_RAM_ANY           = 1u << 13,
  ALARM_DISK_ANY          = 1u << 14,
  ALARM_TEST              = 1u << 15,
  WARNING_CONFIG_MISMATCH = 1u << 16,
};

inline bool valid(float value) { return std::isfinite(value); }

inline bool elapsed(uint32_t now, uint32_t since, uint32_t duration_ms) {
  return since != 0 && static_cast<uint32_t>(now - since) >= duration_ms;
}

inline bool before_deadline(uint32_t now, uint32_t deadline) {
  return deadline != 0 && static_cast<int32_t>(deadline - now) > 0;
}

inline int count_bits(uint32_t value) {
  int count = 0;
  while (value != 0) {
    value &= value - 1;
    ++count;
  }
  return count;
}

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
  if (value >= warn) return "WARNUNG";
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

inline void append_reason(std::string &result, const std::string &reason, int &count, int max_items) {
  if (count >= max_items) return;
  if (!result.empty()) result += "; ";
  result += reason;
  ++count;
}

inline std::string mask_reasons(uint32_t mask, const char *host1, const char *host2,
                                const char *host3, int max_items = 6) {
  std::string result;
  int count = 0;
  if (mask & ALARM_API_OFFLINE) append_reason(result, "Home Assistant offline", count, max_items);
  if (mask & ALARM_DATA_STALE) append_reason(result, "Datenfeed veraltet", count, max_items);
  if (mask & ALARM_HOST1_OFFLINE) append_reason(result, std::string(host1) + " offline", count, max_items);
  if (mask & ALARM_HOST2_OFFLINE) append_reason(result, std::string(host2) + " offline", count, max_items);
  if (mask & ALARM_HOST3_OFFLINE) append_reason(result, std::string(host3) + " offline", count, max_items);
  if (mask & ALARM_POWER_TOTAL) append_reason(result, "Rack-Verbrauch", count, max_items);
  if (mask & ALARM_TEMP_RACK) append_reason(result, "Rack-Temperatur", count, max_items);
  if (mask & ALARM_TEMP_HOST1) append_reason(result, std::string(host1) + " Temperatur", count, max_items);
  if (mask & ALARM_TEMP_HOST2) append_reason(result, std::string(host2) + " Temperatur", count, max_items);
  if (mask & ALARM_TEMP_HOST3) append_reason(result, std::string(host3) + " Temperatur", count, max_items);
  if (mask & ALARM_CPU_HOST1) append_reason(result, std::string(host1) + " CPU", count, max_items);
  if (mask & ALARM_CPU_HOST2) append_reason(result, std::string(host2) + " CPU", count, max_items);
  if (mask & ALARM_CPU_HOST3) append_reason(result, std::string(host3) + " CPU", count, max_items);
  if (mask & ALARM_RAM_ANY) append_reason(result, "RAM-Auslastung", count, max_items);
  if (mask & ALARM_DISK_ANY) append_reason(result, "Speicherplatz", count, max_items);
  if (mask & ALARM_TEST) append_reason(result, "Testalarm", count, max_items);
  if (mask & WARNING_CONFIG_MISMATCH) append_reason(result, "Version/Ref stimmt nicht", count, max_items);
  const int total = count_bits(mask);
  if (total > count) {
    result += "; +" + std::to_string(total - count);
  }
  return result.empty() ? "Keine" : result;
}

inline std::string primary_reason(uint32_t mask, const char *host1, const char *host2,
                                  const char *host3) {
  return mask_reasons(mask, host1, host2, host3, 1);
}

template<typename DisplayT, typename LargeFontT, typename SmallFontT, typename TimeT>
inline void draw_header(DisplayT &it, LargeFontT large_font, SmallFontT small_font,
                        esphome::Color background, esphome::Color foreground,
                        const char *title, const TimeT &now, bool auto_rotate,
                        bool alarm_active) {
  it.filled_rectangle(0, 0, 320, 28, background);
  it.printf(8, 5, large_font, foreground, "%.18s", title);
  if (now.is_valid()) {
    it.strftime(246, 7, small_font, foreground, "%H:%M", now);
  } else {
    it.print(246, 7, small_font, foreground, "--:--");
  }
  if (auto_rotate) it.print(294, 7, small_font, foreground, "A");
  if (alarm_active) it.print(309, 7, small_font, foreground, "!");
}

template<typename DisplayT, typename FontT>
inline void draw_status_badges(DisplayT &it, FontT font, int warnings, int alarms,
                               bool api_online, bool data_fresh,
                               esphome::Color ok, esphome::Color warning,
                               esphome::Color danger) {
  it.print(203, 7, font, api_online ? ok : danger, "H");
  it.print(215, 7, font, data_fresh ? ok : warning, "D");
  if (alarms > 0) {
    it.printf(300, 7, font, danger, "%d", std::min(alarms, 9));
  } else if (warnings > 0) {
    it.printf(300, 7, font, warning, "%d", std::min(warnings, 9));
  }
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
