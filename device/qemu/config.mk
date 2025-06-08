# QEMU configuration for OpenAce

# Architecture
ARCH := aarch64
QEMU_ARCH := aarch64

# QEMU executable
QEMU := qemu-system-$(QEMU_ARCH)

# QEMU options
QEMU_OPTS := \
    -machine virt \
    -cpu cortex-a53 \
    -m 2G \
    -smp 4 \
    -nographic \
    -drive file=openace.img,format=raw,if=virtio \
    -drive file=userdata.img,format=raw,if=virtio \
    -net nic,model=virtio \
    -net user \
    -device virtio-gpu-pci \
    -device virtio-keyboard-pci \
    -device virtio-mouse-pci

# Build targets
.PHONY: qemu-run qemu-debug

qemu-run: $(QEMU_IMAGE)
	$(QEMU) $(QEMU_OPTS)

qemu-debug: $(QEMU_IMAGE)
	$(QEMU) $(QEMU_OPTS) -s -S 