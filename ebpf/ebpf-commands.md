
# eBPF commands

## First program

```
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

int counter = 0;
SEC("xdp")
int hello(struct xdp_md *ctx) {
    bpf_printk("Hello World %d", counter);
    counter++;
    return XDP_PASS;
}
char LICENSE[] SEC("license") = "Dual BSD/GPL";
```

## Compilation and disassembly

```
clang -target bpf -I/usr/include/$(uname -m)-linux-gnu -g -O2 -c hello.bpf.c  -o hello.bpf.o
llvm-objdump -S hello.bpf.o
```

## Loading program

Load the eBPF program from our compiled object file and 'pin' it to the location '/sys/fs/bpf/hello'

```
sudo bpftool prog load hello.bpf.o /sys/fs/bpf/hello
ls /sys/fs/bpf
```

## Inspecting programs

List of all bpf programs
```
sudo bpftool prog list
sudo bpftool prog list --pretty
```

Inspect program 'hello'

```
id=$(sudo bpftool prog list| grep hello | awk '{ print $1 }' | cut -d: -f1)
sudo bpftool prog show id $id --pretty
```

Dump translated bytecode

```
sudo bpftool prog dump xlated name hello
```

Dump JIT-ed code

```
sudo bpftool prog dump jited name hello
```

Check kernel support
```
cat /proc/sys/net/core/bpf_jit_enable
```

Note: You may have to recompile 'bpftool' with JIT disassembly support.

## BPF Program Tag

The tag is a sha sum of the program's instructions.

```
id=$(sudo bpftool prog list| grep hello | awk '{ print $1 }' | cut -d: -f1)
tag=$(sudo bpftool prog list| grep hello | awk '{ print $6 }')

sudo bpftool prog show id $id
sudo bpftool prog show name hello
sudo bpftool prog show tag $tag
sudo bpftool prog show pinned /sys/fs/bpf/hello
```

## Attaching to an event

Attach a program with ID '$id' to the XDP event on the eth0 interface.

```
sudo bpftool net attach xdp id $id dev eth0
```

List all the network-attached eBPF programs:

```
sudo bpftool net list
```

See attached program via 'ip'

```
ip link show dev eth0
```

## Trace output

The 'bpf_trace_printk' when used within an XDP program will produce
trace output each time a packet is received.
```
cat /sys/kernel/debug/tracing/trace_pipe
```

It can also be seen via bpftool

```
sudo bpftool prog tracelog
```

## eBPF Maps

```
sudo bpftool map list
sudo bpftool map list --pretty
```

List maps from a specific program

```
mid=$(sudo bpftool map list | grep hello | awk '{ print $1}' | cut -d: -f1)
sudo bpftool map show id $mid
```

Dump map by name

```
sudo bpftool map dump name hello.bss
```

Dump map by id

```
mid=$(sudo bpftool map list | grep hello | awk '{ print $1}' | cut -d: -f1)
sudo bpftool map dump id $mid
```

Dump read only data

```
sudo bpftool map dump name hello.rodata
```


## Detaching the program

Detach the program from the network interface:

```
sudo bpftool net detach xdp dev eth0
```

Note: The xdp program is still loaded in the kernel.

## Unloading the program

```
sudo rm /sys/fs/bpf/hello
sudo bpftool prog show name hello
```

## BPF to BPF Calls

Function that extracts the syscall
opcode from the tracepoint arguments:
```
static __attribute((noinline)) int get_opcode(struct bpf_raw_tracepoint_args *ctx) {
    return ctx->args[1];
}
```

BPF program that calls this function

```
SEC("raw_tp")
    int hello(struct bpf_raw_tracepoint_args *ctx) {
    int opcode = get_opcode(ctx);
    bpf_printk("Syscall: %d", opcode);
    return 0;
}
```

Compile and load
```
clang -target bpf -I/usr/include/$(uname -m)-linux-gnu -g -O2 -o hello-func.bpf.o -c hello-func.bpf.c
sudo bpftool prog load hello-func.bpf.o /sys/fs/bpf/hello
```

Inspect:
```
sudo bpftool prog list name hello
sudo bpftool prog dump xlated name hello
```

The call to get_opcode looks like this:

```
; int opcode = get_opcode(ctx);
   0: (85) call pc+12#bpf_prog_cbacc90865b1b9a5_get_opcode
```

