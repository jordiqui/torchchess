# TorchChess - A Hybrid Neural Chess Engine

TorchChess combines classical alpha-beta search with modern neural evaluation. The project is written in C++ and integrates both an NNUE evaluator and a Transformer-based model implemented with LibTorch.

## Features
- UCI protocol support
- Hybrid evaluation pipeline (NNUE + Transformer)
- SIMD-accelerated evaluation and multi-threaded search

## Building from Source

### Prerequisites
- CMake 3.18 or newer
- A LibTorch distribution matching your compiler (CPU-only is sufficient)
- OpenMP support in your toolchain

### Build Steps
```bash
git clone https://github.com/jordiqui/torchchess.git
cd torchchess
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/path/to/libtorch ..
make -j$(nproc)
```

## Downloading Evaluation Networks
Binary artifacts cannot be stored directly in this repository, so the NNUE and Transformer weights are downloaded on demand.

Run the helper script to fetch the pretrained files:
```bash
./scripts/download_networks.sh
```
By default the files are placed under `networks/`. You can provide a custom target directory as the first argument.

The script works with either `curl` or `wget`. If neither tool is available, install one of them before running the script.

## Continuous Integration
A GitHub Actions workflow in `.github/workflows/build_linux.yml` shows how to configure a Linux build: install dependencies, download LibTorch, and compile the project. Similar workflows can be created for other platforms.

## License
TorchChess is distributed under the GPL v3.
