# Contic OSGPb

The Contic OSGPb is a small Smart Grid application to deploy and manage a network of Smart Meter devices. It has two operation modes:
 
* **Data Concentrator:** Commands a Smart Meter network
* **Unit:** Acts as a Smart Meter device

A Data Concentrator works by issuing write and read operations to one or more Units on the network. Each Unit has a local database to store the data it generates (e.g. data from energy consumption). Commands from a Data Concentrator are used to write to/read from this database, possibly triggering events on the given unit.

## Build and Run
A C99 compiler and a POSIX.1-2008 compliant system are needed to build and run this project. An executable is created for each operation mode (Data Concentrator or Unit), and the [Makefile](Makefile) can be used to build both applications. Once the applications are built, they are ready to be run/deployed.

#### To build and run the Data Concentrator:
```sh
make dc
bin/dc --key <KEY> --node <HOST-NAME> --port <PORT-NUMBER> [--in <INPUT-FIFO>] [--out <OUTPUT-FIFO>]
```

#### To build and run the Unit:

```sh
make unit
bin/unit --key <KEY> --node <HOST-NAME> --port <PORT-NUMBER> [--clear]
```

## License

This project in licensed under the terms of the [MIT License](LICENSE.md).
