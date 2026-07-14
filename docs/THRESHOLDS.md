# Threshold profiles

Thresholds are deliberately separated by metric and device. Edit only the substitutions in `configs/esp-rack-monitor.yaml`.

## Defaults

| Metric | Warning | Critical |
|---|---:|---:|
| Rack air temperature | 30 °C | 35 °C |
| Unraid / Proxmox CPU temperature | 70 °C | 85 °C |
| NAS temperature | 55 °C | 70 °C |
| CPU utilization | 75 % | 90 % |
| RAM utilization | 80 % | 92 % |
| Used disk capacity | 80 % | 90 % |
| Total rack power | 140 W | 200 W |

Each power card also has its own low/normal boundary and graph maximum. This avoids comparing a small NAS or modem load against the same scale as the whole rack.
