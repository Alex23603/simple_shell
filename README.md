# Simple Shell Project

The Simple Shell Project is a basic shell implementation in C. It provides a simple command-line interface to execute commands on a Linux-based system.

## Features

- Interactive and non-interactive modes
- Basic built-in commands (exit and cd)
- Execution of external commands using `execve`
- Support for pipes and file redirection in non-interactive mode

## Requirements

- GCC (GNU Compiler Collection)
- Linux-based operating system

## Usage

- To run the shell interactively: `./hsh`
- To run the shell non-interactively: `echo "/bin/ls" | ./hsh`

## Supported Commands

- External commands: Any valid Linux command
- Built-in commands: `exit`, `cd [directory]`

## Bugs and Limitations

- May not handle all edge cases or complex commands
- Basic error messages

## Contributing

- Contributions are welcome! Open an issue or create a pull request.

## License

- Open-source under the MIT License.

## Author

- Group project Alex & Yemi
