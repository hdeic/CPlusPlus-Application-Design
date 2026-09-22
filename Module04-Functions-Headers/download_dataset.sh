#!/usr/bin/env bash

set -euo pipefail

DATASET="nelgiriyewithana/top-spotify-songs-2023"
OUT_DIR="$(cd "$(dirname "$0")" && pwd)/data"
ZIP_FILE="$OUT_DIR/top-spotify-songs-2023.zip"

mkdir -p "$OUT_DIR"

if command -v kaggle >/dev/null 2>&1; then
    echo "[kaggle] Downloading $DATASET with the Kaggle CLI..."
    kaggle datasets download -d "$DATASET" -p "$OUT_DIR" --unzip --force
else
    echo "[curl] Kaggle CLI not found; using the Kaggle REST API..."
    API_URL="https://www.kaggle.com/api/v1/datasets/download/$DATASET"
    if [[ -n "${KAGGLE_USERNAME:-}" && -n "${KAGGLE_KEY:-}" ]]; then
        curl -L --fail -u "$KAGGLE_USERNAME:$KAGGLE_KEY" -o "$ZIP_FILE" "$API_URL"
    else
        curl -L --fail -o "$ZIP_FILE" "$API_URL"
    fi
    unzip -o -q "$ZIP_FILE" -d "$OUT_DIR"
    rm -f "$ZIP_FILE"
fi

echo
echo "Downloaded files:"
ls -l "$OUT_DIR"
echo
echo "Record count (excluding header): $(($(wc -l < "$OUT_DIR/spotify-2023.csv") - 1))"
