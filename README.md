# Castlevania (Nintendo 64) Save Editor

## Overview

This tool allows you to edit Castlevania (Nintendo 64) save files.

Supported files include:
* `.note`: Single note files obtained via [MPKEdit](https://github.com/bryc/mpkedit) from a Controller Pak.
* `.eep`: Cartridge saves (Japanese-version only).

> [!NOTE]
> `.mpk`, `.pak`, `.n64`, and `.t64` files are supported for opening and subsequently saving.
> However, there's currently no support for saving brand-new files of these formats using "Save As...".

## Development

This project is actively developed using C/C++ and [Qt](https://www.qt.io/product/development-tools).

More specifically:

```
Qt Creator 15.0.1
Based on Qt 6.8.1 (MSVC 2022, x86_64)

Built on Jan 22 2025 13:47:55
```

## Credits

* [Castlevania 64 Decompilation](https://github.com/k64ret/cv64): Game's code and data structure documentation.
* [N64brew](https://n64brew.dev/wiki/Controller_Pak/Filesystem): Controller Pak format.
* [MPKEdit](https://github.com/bryc/mpkedit): Controller Pak and custom `.note` format.
