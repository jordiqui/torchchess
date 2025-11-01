# Scripts

Utility scripts that assist with development and validation of the engine.

## `check_build.sh`

Runs a clean rebuild of the engine from the `src/` directory. The script wraps
`make` to surface compilation errors quickly and warns if NNUE networks cannot
be downloaded (common on air-gapped environments). Override the default target
by passing arguments, for example `./check_build.sh profile-build`.
