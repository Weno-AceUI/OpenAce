# OpenAce

OpenAce is a lightweight, modular base operating system developed by Weno. Designed to replace Android on AceUI-powered devices, OpenAce provides a secure, efficient, and customizable platform for embedded and mobile systems.

## What's new in OpenAce 0.5 Popcorn
- TV, Tablet, Watch? OpenAce has it all, in a fully conected experience.
- Introducing the new App Icon design, redesigned to be more appealing, flat and less busy.

## Features
- Minimal, fast, and resource-efficient core
- Modular architecture for easy customization
- Secure kernel and system services
- Integrated with AceUI for a modern user experience
- Support for a wide range of hardware via device drivers

## Development Roadmap
We have provided a development Roadmap below:
![OpenAce Project Roadmap](roadmap.png)

## Getting Started
1. **Build OpenAce**
   - Follow the instructions in the `build/` directory to compile the OS for your target device.
2. **Device Integration**
   - Configure your device in the `device/` directory. Reference examples under `device/weno/`.
3. **Boot Process**
   - The bootloader and kernel sources are in `kernel/`. See `arch/aarch64/` for ARM64 support.
4. **UI Layer**
   - AceUI is the default user interface. Customize it in the `ui/` directory.

## Directory Structure
- `aceboot/` — Bootloader and initialization
- `base/` — Core system libraries
- `build/` — Build scripts and configuration
- `device/` — Device-specific configuration and code
- `drivers/` — Hardware drivers
- `kernel/` — Kernel source code
- `packages/` — Optional system packages
- `system/` — System services and daemons
- `tools/` — Development and debugging tools
- `ui/` — AceUI user interface

## Documentation
See the `docs/` directory and in-source comments for further documentation.

## License
OpenAce is released under the MIT License. See `LICENSE` for details.

