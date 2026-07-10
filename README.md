# ADC Coursework

## Overview

This project processes ADC sensor data stored in a binary file. The program reads the file, validates the header, converts raw ADC values into voltages, calculates statistical information for each channel, detects sensor faults, checks sampling integrity, and exports the analysis to a structured results file.

---

## Features

- Read and validate the binary file header
- Read all ADC samples
- Convert raw ADC values to voltages
- Calculate per-channel statistics
    - Mean
    - Minimum
    - Maximum
    - Standard Deviation
- Detect:
    - Over-voltage faults
    - Under-voltage faults
    - Sensor faults
- Check sampling integrity
- Export analysis to `results.txt`

---

## Project Structure

```
main.c - Program entry point
adc.c/.h - ADC conversion functions
io.c/.h - File input/output
stats.c/.h - Statistical calculations and fault detection
CMakeLists.txt - Build configuration
```

---

## Building with CLion

1. Open the project in CLion.
2. Allow CMake to configure the project.
3. Click **Build**.
4. Click **Run**.
5. The program will generate `results.txt`.

---

## Building with GCC

Compile:

```bash
gcc main.c adc.c io.c stats.c -o adc_coursework -lm
```

Run on Linux/macOS:

```bash
./adc_coursework
```

Run on Windows:

```bash
adc_coursework.exe
```

---

## Output

The program displays:

- Header information
- First ADC sample
- Channel statistics
- Fault counts
- Sampling integrity results

A structured report is also written to:

```
results.txt
```

---

## GitHub Repository

https://github.com/mahbub23307/adc-coursework