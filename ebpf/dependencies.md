# Dependencies

### Install clang

Ubuntu:
```
sudo apt update
sudo apt install clang
```

### Install 'libbpf-dev'

```
sudo apt-get install libbpf-dev
```

### bpftool

https://github.com/libbpf/bpftool/releases

Compile bpftool from source.
This is helpful if the official tool does not support JIT-ed disassembly.

```
git clone --recurse-submodules git@github.com:libbpf/bpftool.git
cd bpftool/src
make
sudo make install
```
