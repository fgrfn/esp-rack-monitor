# Thresholds and alarm timing

Most operational thresholds can be changed from Home Assistant after the first flash. Template-number values are stored on the ESP and survive restarts.

## Default thresholds

| Metric | Warning | Critical |
|---|---:|---:|
| Rack air temperature | 35 °C | 40 °C |
| Host 1 / Host 2 temperature | 70 °C | 85 °C |
| Host 3 / NAS temperature | 55 °C | 70 °C |
| CPU utilization | 75 % | 90 % |
| RAM utilization | 80 % | 92 % |
| Used disk capacity | 80 % | 90 % |
| Total rack power | 140 W | 200 W |

A value equal to a threshold enters that level.

## Alarm timing defaults

| Setting | Default | Purpose |
|---|---:|---|
| Startup grace | 60 s | Suppress connection/offline alarms while Wi-Fi, API and HA states initialize |
| Trigger delay | 20 s | Critical condition must remain active before becoming an alarm |
| Clear delay | 60 s | Condition must remain cleared before the alarm bit is removed |
| Temperature hysteresis | 2 °C | Active temperature alarms clear below critical minus hysteresis |
| Power hysteresis | 15 W | Active power alarm clears below critical minus hysteresis |
| Utilization hysteresis | 5 % | Active CPU/RAM/disk alarms clear below critical minus hysteresis |

Each alarm cause is timed independently. If a second cause appears after the first cause was acknowledged, the new bit remains unacknowledged and forces the alarm page again.

## Warnings versus alarms

Warning thresholds affect status colors, header count and warning reason text immediately. They do not force the alarm page.

Critical conditions pass through trigger delay, hysteresis and clear delay. Active critical causes remain visible in Home Assistant even after the display focus has been acknowledged.

## Graph scales

The default power graph uses a 0–250 W range with 25 W grid spacing. The rack-temperature graph uses 15–45 °C with 5 °C spacing. Explicit grid values prevent ESPHome from repeatedly reducing the graph scale.
