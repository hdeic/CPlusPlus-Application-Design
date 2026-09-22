#!/usr/bin/env bash
#
# Course: CIS-25 - Programming Using C++
# Student: H Cheng
# Module: Module 4 - Datasets, Arrays, and Pointers
#
# Pulls the "Top Spotify Songs 2023" dataset from Kaggle and unpacks
# data/spotify-2023.csv so that main.cpp can read it at runtime.
#
# Dataset page: https://www.kaggle.com/datasets/nelgiriyewithana/top-spotify-songs-2023
#
# Two ways to pull the dataset:
#   1. Official Kaggle CLI (pip install kaggle, then place ~/.kaggle/kaggle.json)
#   2. Kaggle REST API via curl (works for public datasets; if KAGGLE_USERNAME
#      and KAGGLE_KEY are set they are used for authentication)
#
# Usage:  ./download_dataset.sh

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
