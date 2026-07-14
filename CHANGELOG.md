# Changelog

All notable changes to this project are documented here.

## 0.2.2 - 2026-07-14

### Changed

- Rack air temperature defaults now use 35 °C for warning and 40 °C for critical.
- Rack temperature graph range now extends to 45 °C.
- Remote package and helper sources now share the same configurable Git reference.

### Fixed

- B2 long press now triggers after 800 ms while the button remains held, without a three-second upper limit.
- Holding B2 longer than three seconds no longer prevents alarm acknowledgement.
- B1 previous-page long presses now accept holds up to ten seconds.

## 0.2.1 - 2026-07-14

### Added

- One-file ESPHome Dashboard installation using official Remote/Git Packages.
- Header-only `RackMonitorHelpers` PlatformIO library for automatic helper delivery.
- CI branch-ref preparation so pull requests validate their own remote package and helper sources.

### Changed

- The public `esp-rack-monitor.yaml` now downloads all implementation modules automatically.
- Secret lookups moved from remote package files into the local one-file installer.
- README installation instructions now require only copying one YAML file into ESPHome.

### Fixed

- Copying only `esp-rack-monitor.yaml` no longer fails because local `packages/` or `includes/` directories are missing.

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
- Pinned ESPHome pull-request and main-branch compile validation.
- Weekly compatibility build against the latest ESPHome release.
- GitHub Actions workflow linting and grouped Dependabot updates.
- Source-only tagged release workflow with compile validation.
- Hardware, entity and threshold documentation plus UI preview.
- MIT license.

### Changed

- Home Assistant entity IDs and all status thresholds are now substitutions.
- Auto rotation is managed by a single restorable template switch.
- Buttons now support short and long presses.
- Numeric HA sensors expire to `NaN` instead of displaying old values indefinitely.
- Web UI is authenticated, local-only and cannot perform web OTA updates.
- The canonical ESPHome entrypoint now lives at `esp-rack-monitor.yaml` in the repository root.
- Package, helper include and secrets paths now match the standard `/config/esphome` Home Assistant layout.
- CI builds the same root configuration used by the ESPHome dashboard.
- CI firmware artifacts expire after seven days and are explicitly validation-only.

### Fixed

- Fixed package lookup errors caused by `../packages/...` resolving outside `/config/esphome`.
- Fixed the helper include path that previously resolved outside the ESPHome configuration directory.

### Security

- Removed the fixed fallback access-point password from the firmware configuration.
- Added secrets for fallback Wi-Fi and the web server.
- CI and release validation now generate ephemeral random settings.
- Public releases no longer attach preconfigured firmware.

## 0.1.0 - 2026-06-02

- Initial ESPHome project for LilyGO T-Display-S3.
- Rack overview, power, temperature and CPU/RAM/disk pages.
- Auto rotation, button hints and status colors.
