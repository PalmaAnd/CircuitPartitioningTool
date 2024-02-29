# Circuit Decomposer

The Circuit Decomposer is a tool designed to partition given circuit schematics into minimal unconnected subcircuits. This project implements an algorithm based on a set of provided guidelines.

## Usage

To use this tool, follow these steps:

1. Prepare input files:
    - `gate.dat`: Information about gates in the circuit.
    - `connection.dat`: Details of connections between gates.
    - `type.dat`: Types of gates.
    - `function.dat`: Functions performed by gates.

2. Run the program with the appropriate command:

```bash
programm gate.dat connection.dat type.dat function.dat
```

3. The program will process the inputs and generate the correct output.

## Algorithm

The algorithm employed by the Circuit Decomposer follows these steps:

1. Mark all gates with 0 (unmarked).
2. Set n = 1.
3. Mark any unmarked gate with n.
4. Mark all gates with n connected to an input or output pin of a gate marked with n.
5. Repeat step 4 until there are no changes.
6. Increment n by 1.
7. Repeat steps 3-6 until all elements are marked.

## Contributing

Contributions to this project are welcome! If you have any suggestions, bug reports, or feature requests, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
