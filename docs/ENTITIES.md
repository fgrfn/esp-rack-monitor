# Home Assistant entities

All entity IDs are substitutions in `configs/esp-rack-monitor.yaml`; no package file needs to be edited.

| Substitution | Expected value | Unit | Default |
|---|---|---:|---|
| `entity_power_total` | Current total rack power | W | `sensor.homelab_rack_power` |
| `entity_power_unraid` | Current Unraid power | W | `sensor.unraid_tower_power` |
| `entity_power_proxmox` | Current Proxmox power | W | `sensor.proxmox_power` |
| `entity_power_nas` | Current NAS power | W | `sensor.ugreen_dh2300_nas_power` |
| `entity_power_jetkvm_modem` | Current JetKVM + modem power | W | `sensor.jetkvm_modem_power` |
| `entity_temp_rack` | Rack air temperature | °C | `sensor.rack_temperatursensor_temperature` |
| `entity_temp_unraid` | Unraid CPU temperature | °C | `sensor.unraid_cpu_temp` |
| `entity_temp_proxmox` | Proxmox CPU temperature | °C | `sensor.proxmox_cpu_temp` |
| `entity_temp_nas` | NAS temperature | °C | `sensor.nas_temperature` |
| `entity_cpu_*` | CPU utilization | % | See configuration |
| `entity_ram_*` | RAM utilization | % | See configuration |
| `entity_disk_*` | Used disk capacity | % | See configuration |
| `entity_electricity_price` | Current electricity price | EUR/kWh or ct/kWh | Tibber sensor default |
| `entity_rack_energy_today` | Rack energy today | kWh | `sensor.homelab_rack_energy_today` |
| `entity_heartbeat` | Changing timestamp heartbeat | s | `sensor.esp_rack_monitor_heartbeat` |
| `entity_*_online` | Optional host reachability | on/off | Placeholder binary sensors |

Set `electricity_price_divisor` to `1.0` for EUR/kWh or `100.0` for ct/kWh.

## Freshness behavior

Numeric Home Assistant sensors receive a configurable timeout filter. After `sensor_stale_timeout`, the value becomes `NaN` and the UI shows `STALE` instead of continuing to present old data. The optional heartbeat package provides reliable whole-feed detection even when a monitored metric remains constant.

Optional online binary sensors are ignored until they have produced a valid state. Once available, an offline host activates the alarm page.
