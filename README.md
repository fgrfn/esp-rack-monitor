# ESP Rack Monitor

ESPHome-Projekt für ein LilyGO T-Display-S3 als Rack-Monitoring-Display.

## Features

- Rack-Übersicht mit Gesamtverbrauch und Rack-Temperatur
- Stromverbrauchsseite für:
  - Unraid
  - Proxmox
  - NAS
  - JetKVM+Modem
- Temperaturseite im 2x2-Kartenlayout:
  - Rack
  - Unraid
  - Proxmox
  - NAS
- CPU/RAM/DISK-Seite mit 3 Spalten:
  - Unraid
  - Proxmox
  - NAS
- Auto-Rotation
- Button-Hinweise links am Display
- Farbige Statusanzeige für Strom, Temperatur, CPU, RAM und Speicherplatz

## Dateien

```text
configs/esp-rack-monitor.yaml   ESPHome-Hauptkonfiguration
secrets.example.yaml            Beispiel für ESPHome-Secrets
.gitignore                      Ignoriert lokale Secrets und Build-Dateien
CHANGELOG.md                    Änderungsverlauf
```

## Installation

1. ESPHome in Home Assistant öffnen.
2. Neues Gerät anlegen oder bestehendes Gerät bearbeiten.
3. Inhalt aus `configs/esp-rack-monitor.yaml` übernehmen.
4. Secrets aus `secrets.example.yaml` in deine ESPHome-Secrets übertragen.
5. Entity-IDs mit `# ← ANPASSEN` auf deine Home-Assistant-Entitäten ändern.
6. Flashen.

## Wichtige Platzhalter-Entitäten

Diese Entity-IDs musst du ggf. anpassen:

```yaml
sensor.proxmox_power
sensor.jetkvm_modem_power
sensor.nas_cpu_usage
sensor.nas_ram_usage
sensor.unraid_disk_usage
sensor.proxmox_disk_usage
sensor.nas_disk_usage
```

## Status-Schwellen

### Strom

- `< 100 W` = niedrig / grün
- `100–139 W` = normal / blau
- `140–199 W` = hoch / gelb
- `ab 200 W` = kritisch / rot

### Temperatur

- `< 55 °C` = normal / grün
- `55–69 °C` = hoch / gelb
- `ab 70 °C` = kritisch / rot

### CPU/RAM/DISK

- `< 75 %` = grün
- `75–89 %` = gelb
- `ab 90 %` = rot
