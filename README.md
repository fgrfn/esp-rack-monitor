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
- Modular ESPHome packages and shared C++ display helpers
- Pinned ESPHome builds, weekly compatibility checks, workflow linting and automated dependency updates

## Repository layout

```text
esp-rack-monitor.yaml               Main substitutions and package imports
packages/base.yaml                  Board, project and diagnostics base
packages/connectivity.yaml          Wi-Fi, API, OTA and protected web UI
packages/entities.yaml              HA inputs, local diagnostics and alarms
packages/controls.yaml              Page, rotation, buttons and night mode
packages/display.yaml               Fonts, graphs and all display pages
includes/display_helpers.h          Shared validation, colors, bars and header helpers
secrets.example.yaml                Required secret keys without real credentials
home-assistant/                     Optional HA heartbeat package
docs/                               Pinout, entities and thresholds
.github/workflows/                  Compile, compatibility, lint and release automation
```

## Installation

1. Copy or clone the repository contents directly into the ESPHome configuration directory, normally `/config/esphome`.
2. Keep `esp-rack-monitor.yaml`, `packages/`, `includes/` and `secrets.yaml` on the same directory level.
3. Add the values listed in `secrets.example.yaml` to the normal ESPHome `secrets.yaml` file.
4. Edit the substitutions in `esp-rack-monitor.yaml`, especially entity IDs and thresholds.
5. Optionally install `home-assistant/esp-rack-monitor-package.yaml` as a Home Assistant package and restart Home Assistant. This enables reliable stale-feed detection.
6. Validate and flash `esp-rack-monitor.yaml` from ESPHome.

Expected Home Assistant layout:

```text
/config/esphome/
├── esp-rack-monitor.yaml
├── secrets.yaml
├── packages/
│   ├── base.yaml
│   ├── connectivity.yaml
│   ├── controls.yaml
│   ├── display.yaml
│   └── entities.yaml
└── includes/
    └── display_helpers.h
```

The web server is deliberately restricted to a local asset bundle, has HTTP authentication enabled and has web-based OTA disabled. Do not expose it to the internet.

## Migrating from the former `configs/` layout

Move `configs/esp-rack-monitor.yaml` to `/config/esphome/esp-rack-monitor.yaml`. Remove `../` from all five package include paths and use `packages/...`. In `packages/base.yaml`, use `includes/display_helpers.h` instead of `../includes/display_helpers.h`. The repository now already contains this corrected layout.

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

Pull requests compile with the pinned ESPHome version declared in `.github/workflows/esphome.yml`. Direct `main` pushes compile only when firmware-related files change. Validation artifacts expire after seven days and are not intended for installation.

A scheduled workflow compiles with the latest ESPHome release every Monday. Workflow files are checked with `actionlint`, and Dependabot proposes grouped GitHub Actions updates each week.

Tags such as `v0.2.0` are compiled for validation and create a source-only GitHub Release. Prebuilt public firmware is intentionally not attached because each installation requires its own configuration.

## License

MIT — see [LICENSE](LICENSE).
