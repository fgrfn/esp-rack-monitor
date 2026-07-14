# Update strategy

`rack_monitor_library_ref` controls both the Remote/Git Packages and the header-only helper library.

## Channels

### Development channel

```yaml
rack_monitor_library_ref: main
```

This receives the newest merged and CI-tested changes on the next clean compile.

### Stable release

```yaml
project_version: "0.3.0"
rack_monitor_library_ref: v0.3.0
```

A release tag keeps the implementation fixed. The diagnostic entities show both values. When a tag does not match `v${project_version}`, the monitor raises a non-critical configuration warning.

## Recommended update procedure

1. Read the changelog and migration notes.
2. Replace the local one-file installer when substitutions were added.
3. Select **Clean Build Files** in ESPHome.
4. Validate and install.
5. Check the test page and the diagnostic page.
6. Trigger **Alarm testen** and verify acknowledgement with B2.

## Why public firmware binaries are not released

Wi-Fi credentials, API encryption keys, OTA passwords and Home Assistant entity IDs are installation-specific. Releases therefore contain source code only; firmware is compiled locally through ESPHome.
