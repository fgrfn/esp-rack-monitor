#!/usr/bin/env bash
set -euo pipefail

ref="${1:?Git ref is required}"

python3 - "${ref}" <<'PY'
from pathlib import Path
import sys

ref = sys.argv[1]
path = Path("esp-rack-monitor.yaml")
text = path.read_text(encoding="utf-8")
text = text.replace("  rack_monitor_library_ref: main", f'  rack_monitor_library_ref: "{ref}"', 1)
text = text.replace("    ref: main", f'    ref: "{ref}"', 1)
path.write_text(text, encoding="utf-8")
PY
