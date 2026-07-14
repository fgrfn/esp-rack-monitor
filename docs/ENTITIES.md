# Home Assistant entities

All source entity IDs and host labels are substitutions in `esp-rack-monitor.yaml`; package files do not need to be edited.

## Source entities

| Substitution | Expected value | Unit | Default |
|---|---|---:|---|
| `entity_power_total` | Current total rack power | W | `sensor.homelab_rack_power` |
| `entity_power_unraid` | Host 1 power | W | `sensor.unraid_tower_power` |
| `entity_power_proxmox` | Host 2 power | W | `sensor.proxmox_power` |
| `entity_power_nas` | Host 3 power | W | `sensor.ugreen_dh2300_nas_power` |
| `entity_power_jetkvm_modem` | Host 4 / auxiliary power | W | `sensor.jetkvm_modem_power` |
| `entity_temp_rack` | Rack air temperature | °C | `sensor.rack_temperatursensor_temperature` |
| `entity_temp_unraid` | Host 1 temperature | °C | `sensor.unraid_cpu_temp` |
| `entity_temp_proxmox` | Host 2 temperature | °C | `sensor.proxmox_cpu_temp` |
| `entity_temp_nas` | Host 3 temperature | °C | `sensor.nas_temperature` |
| `entity_cpu_*` | CPU utilization | % | See installer |
| `entity_ram_*` | RAM utilization | % | See installer |
| `entity_disk_*` | Used disk capacity | % | See installer |
| `entity_electricity_price` | Current electricity price | EUR/kWh or ct/kWh | Tibber sensor |
| `entity_rack_energy_today` | Rack energy today | kWh | `sensor.homelab_rack_energy_today` |
| `entity_rack_cost_today` | Actual integrated rack cost today | € | `sensor.esp_rack_monitor_cost_today` |
| `entity_heartbeat` | Changing Unix timestamp | s | `sensor.esp_rack_monitor_heartbeat` |
| `entity_sun` | Home Assistant sun state | text | `sun.sun` |
| `entity_*_online` | Optional host reachability | on/off | Host binary sensors |

Set `electricity_price_divisor` to `1.0` for EUR/kWh or `100.0` for ct/kWh.

## Entities created by ESPHome

0.3.0 adds configuration entities for:

- threshold and hysteresis values
- alarm trigger, clear and startup delays
- brightness and night hours
- rotation interval and manual pause
- host visibility and alarm-group switches
- last-page restoration, default page and empty-page skipping
- alarm test and acknowledgement

It also exposes active alarm/warning counts, all reason strings, an unacknowledged-alarm binary sensor, data age, project version and configured update ref.

## Freshness behavior

Numeric Home Assistant inputs receive a timeout filter. After `sensor_stale_timeout`, the state becomes `NaN` and the UI shows `STALE` or hides the corresponding card. The optional heartbeat package provides whole-feed detection even when monitored metrics remain constant.

Optional online binary sensors are ignored until they have produced a state. Once available, an offline state enters the delayed alarm state machine after the startup grace period.
