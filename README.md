# ESP Rack Monitor

ESPHome rack-monitoring firmware for a **LilyGO T-Display-S3**. It presents Home Assistant metrics on a compact 320 × 170 display and exposes display controls back to Home Assistant.

![Display page overview](docs/images/display-pages.svg)

## Features

- Seven selectable pages: overview, power, temperatures, systems, one-hour trends, electricity costs and diagnostics
- Dedicated critical-alarm page with automatic focus and hardware-button acknowledgement
- Per-device power limits and separate rack/CPU/NAS temperature profiles
- `STALE`, offline and unavailable handling rather than silently showing old measurements
- One-hour in-memory graphs for total power and rack temperature
- Electricity price, hourly cost and day/month projections, including negative prices
- Auto rotation, direct page select, backlight entity and automatic night dimming
- Diagnostic data: HA API state, heartbeat freshness, Wi-Fi RSSI, IP, uptime, heap, PSRAM, loop time, firmware version and reset reason
- Authenticated local web UI, native encrypted API and password-protected native OTA
- One-file installation through the ESPHome dashboard
- Pinned ESPHome builds, weekly compatibility checks, workflow linting and automated dependency updates

## Installation through Home Assistant

Only **one YAML file** must be copied into ESPHome:

1. In Home Assistant, open **ESPHome**.
2. Create a new device or open the YAML editor of the existing Rack Monitor.
3. Copy the complete contents of [`esp-rack-monitor.yaml`](esp-rack-monitor.yaml) into the editor.
4. Adjust the Home Assistant entity IDs in the `substitutions` section when necessary.
5. Validate and install the configuration.

ESPHome downloads the implementation files and the display-helper library automatically from this GitHub repository during validation. No local `packages/`, `includes/` or repository checkout is required. Internet access is therefore required while compiling.

The following entries must exist in the normal global ESPHome `secrets.yaml`:

```yaml
wifi_ssid: "YOUR_WIFI"
wifi_password: "YOUR_WIFI_PASSWORD"
fallback_ap_password: "A_LONG_FALLBACK_PASSWORD"
api_encryption_key: "YOUR_DEVICE_API_KEY"
ota_password: "A_LONG_OTA_PASSWORD"
web_server_username: "admin"
web_server_password: "A_LONG_WEB_PASSWORD"
```

A matching template is available in [`secrets.example.yaml`](secrets.example.yaml).

The optional [`home-assistant/esp-rack-monitor-package.yaml`](home-assistant/esp-rack-monitor-package.yaml) Home Assistant package enables reliable heartbeat-based stale-feed detection. The display still compiles without it.

## How the one-file installer works

The public `esp-rack-monitor.yaml` contains your substitutions and local secret references. ESPHome then loads these implementation files as an official Remote/Git Package:

```text
packages/base.yaml
packages/connectivity.yaml
packages/entities.yaml
packages/controls.yaml
packages/display.yaml
```

The header-only display helper is fetched as the `RackMonitorHelpers` PlatformIO library from the same repository. Remote implementation files never perform their own `!secret` lookups; all credentials remain in your local ESPHome configuration.

By default the installer follows `main`. Set both the package `ref` and `rack_monitor_library_ref` to a release tag when you want to keep a fixed version.

## Controls

| Control | Behavior |
|---|---|
| Button 1 short | Next page |
| Button 1 long | Previous page |
| Button 2 short | Toggle auto rotation |
| Button 2 long | Acknowledge automatic alarm-page focus |
| HA page select | Jump directly to a page |
| HA auto-rotation switch | Enable or disable rotation |
| HA night-mode switch | Enable or disable scheduled dimming |
| HA backlight light | Set the display brightness manually |

## Configuration

- [Home Assistant entities](docs/ENTITIES.md)
- [Thresholds and scales](docs/THRESHOLDS.md)
- [Hardware and pinout](docs/PINOUT.md)

The initial defaults preserve the existing rack entity IDs where they were already known. Placeholder entities do not prevent compilation; missing optional online sensors are ignored until they report a state.

## Data freshness

Every numeric Home Assistant input has a timeout filter. A timed-out value becomes `NaN`, and the display renders `STALE` or `--`. For reliable whole-connection freshness, the optional Home Assistant package updates `sensor.esp_rack_monitor_heartbeat` every minute; the display raises an alarm when that heartbeat expires.

## CI and releases

Pull requests compile the exact one-file installer against the pull-request branch. This verifies both Remote/Git Package loading and the helper-library download. A scheduled workflow compiles against the latest ESPHome release every Monday. Workflow files are checked with `actionlint`, and Dependabot proposes grouped GitHub Actions updates each week.

Tags such as `v0.2.1` are compiled for validation and create a source-only GitHub Release. Prebuilt public firmware is intentionally not attached because every installation uses individual credentials and Home Assistant entities.

## License

MIT — see [LICENSE](LICENSE).
