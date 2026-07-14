#!/usr/bin/env bash
set -euo pipefail

api_key="$(openssl rand -base64 32 | tr -d '\n')"
wifi_password="$(openssl rand -hex 16)"
fallback_password="$(openssl rand -hex 16)"
ota_password="$(openssl rand -hex 16)"
web_password="$(openssl rand -hex 16)"

cat > secrets.yaml <<SECRETS
wifi_ssid: "ci-network"
wifi_password: "${wifi_password}"
fallback_ap_password: "${fallback_password}"
api_encryption_key: "${api_key}"
ota_password: "${ota_password}"
web_server_username: "ci-user"
web_server_password: "${web_password}"
SECRETS
