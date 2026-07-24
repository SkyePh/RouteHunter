<p align="center">
  <img src="assets/RouteHunter.png" alt="RouteHunter" width="420"/>
</p>

<h1 align="center">RouteHunter</h1>

<p align="center">
  <strong>FUZZ without the command-line fuss.</strong><br/>
  A native desktop GUI for <a href="https://github.com/ffuf/ffuf">ffuf</a> — point, click, hunt routes.
</p>

<p align="center">
  <a href="https://github.com/SkyePh/RouteHunter/releases/latest"><img src="https://img.shields.io/github/v/release/SkyePh/RouteHunter?style=for-the-badge&color=2F6FED&labelColor=0b0b0b" alt="Release"/></a>
  <a href="https://github.com/SkyePh/RouteHunter/releases/latest"><img src="https://img.shields.io/github/downloads/SkyePh/RouteHunter/total?style=for-the-badge&color=2F6FED&labelColor=0b0b0b" alt="Downloads"/></a>
  <img src="https://img.shields.io/badge/Qt-6-2F6FED?style=for-the-badge&labelColor=0b0b0b&logo=qt&logoColor=white" alt="Qt 6"/>
  <img src="https://img.shields.io/badge/C%2B%2B-20-2F6FED?style=for-the-badge&labelColor=0b0b0b&logo=cplusplus&logoColor=white" alt="C++20"/>
  <a href="https://github.com/SkyePh/RouteHunter/stargazers"><img src="https://img.shields.io/github/stars/SkyePh/RouteHunter?style=for-the-badge&color=2F6FED&labelColor=0b0b0b" alt="Stars"/></a>
</p>

---

## Why RouteHunter?

`ffuf` is incredible. Memorizing every flag is not.

RouteHunter wraps ffuf in a clean desktop UI so you can use it quickly and easily

Built for bug bounty hunters, pentesters, and anyone who wants speed without living in a terminal.

## Features

| | |
|---|---|
| **Bundled ffuf** | Platform binaries ship with the app — no PATH wrestling |
| **Wordlists included** | `common`, `big`, `megabeast`, admin panels, extensions, and more |
| **Real ffuf power** | Redirects, auto-calibrate, recursion, HTTP/2, status filters, extensions, timeouts |
| **Results table** | URL · Status · Size · Words · Lines parsed from JSON output |
| **Cross-platform** | macOS (Apple Silicon), Linux, Windows — AMD64 & ARM64 |

## Download

Grab the latest build from **[Releases](https://github.com/SkyePh/RouteHunter/releases/latest)**:

| Platform | Package |
|----------|---------|
| macOS Apple Silicon | `RouteHunter-*-macos-arm64.zip` |
| Linux x64 | `RouteHunter-*-linux-amd64.tar.gz` |
| Linux ARM64 | `RouteHunter-*-linux-arm64.tar.gz` |
| Windows x64 | `RouteHunter-*-windows-amd64.zip` |
| Windows ARM64 | `RouteHunter-*-windows-arm64.zip` |

<details>
<summary><strong>Run tips</strong></summary>

- **macOS:** unzip → open `RouteHunter.app`. If Gatekeeper complains: right-click → Open (or allow in System Settings).
- **Linux:** extract the archive and run `./RouteHunter.sh` (sets library + plugin paths).
- **Windows:** unzip and run `RouteHunter.exe`.

</details>

## Quick start (from source)

**Needs:** CMake ≥ 3.21, Qt 6 (Widgets), a C++20 compiler.

```bash
git clone https://github.com/SkyePh/RouteHunter.git
cd RouteHunter
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Then launch the binary from `build/` (on macOS: `build/RouteHunter.app`).

## Contributing

**Open source contributions are very welcome.**  
RouteHunter is built to grow with the community.

Whether you want to:

- Fix a bug or polish the UI  
- Add ffuf options / export formats  
- Improve packaging or CI  
- Write docs

…jump in.

### How to contribute

1. **Fork** the repo  
2. **Create a branch:** `git checkout -b feature/your-idea`  
3. **Make your change** (keep PRs focused)  
4. **Open a Pull Request** and tell us what / why  

Ideas & bugs → [Issues](https://github.com/SkyePh/RouteHunter/issues)  
PRs → [Pull requests](https://github.com/SkyePh/RouteHunter/pulls)

> First time contributing to open source? Perfect. Small PRs are great PRs. Ask questions in the issue or PR — we’re happy to help.

## Project layout

```
RouteHunter/
├── src/           # Qt UI + ffuf runner
├── tools/         # Bundled ffuf per OS/arch
├── wordlists/     # Ready-to-hunt lists
├── assets/        # Icons + demo media
└── .github/       # Release workflow
```

## Credits

- Powered by **[ffuf](https://github.com/ffuf/ffuf)** — the fast web fuzzer  
- UI built with **Qt 6**

## Disclaimer

RouteHunter is for **authorized security testing and educational use only**.  
Only scan systems you own or have explicit permission to test.

---

<p align="center">
  <sub>Thanks for coming here <3.</sub><br/>
  <a href="https://github.com/SkyePh/RouteHunter">★ Star the repo</a> if RouteHunter saved you a flag (or a headache).
</p>
