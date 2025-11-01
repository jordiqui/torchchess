#!/usr/bin/env bash
set -euo pipefail

# Determine repository root from the location of this script.
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
SRC_DIR="$ROOT_DIR/src"

if [[ ! -d "$SRC_DIR" ]]; then
  echo "[error] Cannot locate src directory at $SRC_DIR" >&2
  exit 1
fi

if ! command -v make >/dev/null 2>&1; then
  echo "[error] make command not found. Install GNU make to continue." >&2
  exit 1
fi

JOBS=${JOBS:-$(nproc)}
MAKE_TARGETS=("build")
if [[ $# -gt 0 ]]; then
  MAKE_TARGETS=("$@")
fi

pushd "$SRC_DIR" >/dev/null

# Clean previous artifacts to avoid stale object files causing spurious errors.
echo "==> Cleaning previous build artifacts"
make clean >/dev/null 2>&1 || true

set +e
echo "==> Running: make -j$JOBS ${MAKE_TARGETS[*]}"
MAKE_OUTPUT=$(mktemp)
make -j"$JOBS" "${MAKE_TARGETS[@]}" | tee "$MAKE_OUTPUT"
STATUS=${PIPESTATUS[0]}
set -e

if [[ $STATUS -ne 0 ]]; then
  echo "[error] Build failed. Review the output above or in $MAKE_OUTPUT" >&2
  popd >/dev/null
  exit $STATUS
fi

if grep -q "Failed to download" "$MAKE_OUTPUT"; then
  echo "[warn] Some NNUE networks could not be downloaded. Existing local files will be used if available." >&2
fi

rm -f "$MAKE_OUTPUT"

popd >/dev/null

echo "==> Build completed successfully"
