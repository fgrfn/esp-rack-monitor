# Changelog

All notable changes to this project are documented here.

## 0.2.0 - 2026-07-14

### Added

- Modular ESPHome package structure and shared display helpers.
- Direct page selector with seven regular pages.
- One-hour power and rack-temperature graphs.
- Electricity-price and cost projection page.
- Diagnostics page with API, heartbeat, network, uptime and memory information.
- Critical alarm page, Home Assistant alarm entities and button acknowledgement.
- Automatic day/night brightness and temporary button wake-up.
- Optional Home Assistant heartbeat package for stale-feed detection.
- Per-device power profiles and separate rack, CPU and NAS temperature thresholds.
- GitHub Actions compile validation and tagged firmware release workflow.
- Hardware, entity and threshold documentation plus UI preview.
- MIT license.

### Changed

- Home Assistant entity IDs and all status thresholds are now substitutions.
- Auto rotation is managed by a single restorable template switch.
- Buttons now support short and long presses.
- Numeric HA sensors expire to `NaN` instead of displaying old values indefinitely.
- Web UI is authenticated, local-only and cannot perform web OTA updates.

### Security

- Removed the fixed fallback access-point password from the firmware configuration.
- Added secrets for fallback Wi-Fi and the web server.

## 0.1.0 - 2026-06-02

- Initial ESPHome project for LilyGO T-Display-S3.
- Rack overview, power, temperature and CPU/RAM/disk pages.
- Auto rotation, button hints and status colors.
