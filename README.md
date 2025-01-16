# Operating Systems Directory

Welcome to the `operatingSystems` directory! This directory is organized to help you explore various topics in Operating Systems programming. Each topic is contained in its own subdirectory for better organization and easier navigation.

## Directory Structure

The `operatingSystems` directory is divided into subdirectories, each corresponding to a specific topic. For example:

```
operatingSystems/
├── topic1/
│   ├── example1.c
│   ├── example2.c
├── topic2/
│   ├── example1.c
│   ├── example2.c
...
```

Each subdirectory contains `.c` files relevant to its topic

## Compiling and Running the Programs

To compile and run a `.c` file from any subdirectory, follow these steps:

1. Navigate to the subdirectory containing the desired `.c` file. For example:
   ```bash
   cd operatingSystems/topic1
   ```

2. Compile the file using the `gcc` compiler with the following command:
   ```bash
   gcc -Wall -o app filename.c
   ```
   Replace `filename.c` with the actual name of the `.c` file you want to compile.

   - The `-Wall` flag enables all compiler warnings to help you identify potential issues.
   - The `-o app` option specifies the output file name as `app`.

3. Run the compiled program with:
   ```bash
   ./app
   ```

## Example

Suppose you want to run `example1.c` from the `topic1` subdirectory:

```bash
cd operatingSystems/topic1
gcc -Wall -o app example1.c
./app
```

## Notes

- Make sure you have `gcc` installed on your system. You can install it using your system's package manager (e.g., `apt`, `yum`, or `brew` depending on your OS)
- The output file (`app`) can be renamed as needed by changing the `-o app` argument in the `gcc` command

Feel free to explore, modify, and experiment with the provided programs to deepen your understanding of Operating Systems concepts!

---

⚡️ Happy coding by XStudio ⚡️

## Stay Connected

Support me on [Instagram](https://www.instagram.com/buildwithxstudio?utm_source=ig_web_button_share_sheet&igsh=ZDNlZDc0MzIxNw==) ❤️