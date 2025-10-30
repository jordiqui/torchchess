#!/usr/bin/env bash
set -euo pipefail

NETWORK_DIR="${1:-networks}"
mkdir -p "${NETWORK_DIR}"

fetch() {
  local url="$1"
  local output="$2"

  if command -v curl >/dev/null 2>&1; then
    curl -L "$url" -o "$output"
  elif command -v wget >/dev/null 2>&1; then
    wget -O "$output" "$url"
  else
    echo "Neither curl nor wget is available. Please install one of them to download networks." >&2
    exit 1
  fi
}

NNUE_URL="https://data.stockfishchess.org/binaries/nn/nn-3475407dc199.nnue"
NNUE_FILE="$NETWORK_DIR/nn-3475407dc199.nnue"

if [ ! -f "$NNUE_FILE" ]; then
  echo "Downloading Stockfish NNUE network..."
  fetch "$NNUE_URL" "$NNUE_FILE"
else
  echo "NNUE network already downloaded at $NNUE_FILE"
fi

TRANSFORMER_URL="https://huggingface.co/datasets/jordiqui/torchchess-assets/resolve/main/transformer-small.pt?download=true"
TRANSFORMER_FILE="$NETWORK_DIR/transformer-small.pt"

if [ ! -f "$TRANSFORMER_FILE" ]; then
  echo "Downloading sample transformer weights..."
  fetch "$TRANSFORMER_URL" "$TRANSFORMER_FILE"
else
  echo "Transformer weights already downloaded at $TRANSFORMER_FILE"
fi

echo "All networks downloaded to $NETWORK_DIR"
