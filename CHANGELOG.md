# Changelog

All notable changes to this project are documented here.

## 0.3.2 - 2026-07-14

### Fixed

- Versioned the PlatformIO helper dependency so an older cached `rack_monitor_helpers.h` can no longer be combined with newer Remote/Git Package YAML files.
- Updated the helper library manifest from the obsolete 0.2.1 identity to the matching 0.3.2 identity.
- Changed the moving `main` package channel to refresh on every validation, preventing package/helper drift during active development.

## 0.3.1 - 2026-07-14

### Fixed

- Restored legacy `rotation_interval`, brightness and night-hour substitutions so a newly copied 0.3.x installer also validates when ESPHome still has cached 0.2.x Remote/Git Package files.
- Reduced the `main` Remote/Git Package refresh interval from one day to five minutes to avoid long-lived mixed installer/package states during active development.

## 0.3.0 - 2026-07-14

### Added

- Independent bitmask-based alarm causes with per-cause trigger and clear timers.
- Configurable startup grace, trigger delay, clear delay and metric hysteresis.
- Separate immediate warning state, count and reason entities.
- Persistent Home Assistant number controls for thresholds, timing, brightness and rotation.
- Enable switches for four generic host slots and five alarm groups.
- Automatic hiding of unavailable host cards and optional empty-page skipping.
- Configurable default page, last-page restoration and post-interaction rotation pause.
- Hardware test page and one-minute alarm-test button.
- Optional sun-based night dimming using `sun.sun`.
- Actual daily cost input plus an expanded optional Home Assistant package.
- Persistent HA alarm notifications, acknowledgement/test scripts and a Lovelace card.
- Update-ref, project-version and configuration-mismatch diagnostics.

### Changed

- Existing Unraid/Proxmox/NAS entity substitutions are retained internally but presented as generic host slots.
- Alarm acknowledgement now covers only currently active causes; a new cause reopens the alarm page.
- B2 short press no longer changes rotation while an alarm is active.
- Automatic display refresh defaults to five seconds while alarms and buttons still update immediately.
- Auto-rotation skips the hardware-test page and can skip pages without usable data.
- Cost page prefers actual integrated daily cost when the HA package is installed.
- Header badges show HA/data state and alarm/warning counts on every page.

### Fixed

- Added hysteresis and persistence delays to prevent alarms from flapping around a threshold.
- Multiple simultaneous causes are no longer hidden behind a single first-reason string.
- Manual page changes no longer get immediately overwritten by auto-rotation.
- Graph Y-grid spacing is now defined directly in the remote display package.

## 0.2.3 - 2026-07-14

### Changed

- Power and rack-temperature graphs now use explicit configurable Y-axis grid spacing.

### Fixed

- Prevented repeated `Graphing reducing y-scale to prevent too many gridlines` warnings during display updates.

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
