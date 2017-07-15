# contic-osgpb

The Contic OSGPb has two operation modes:
 
* **Data Concentrator:** Commands a Smart Meter network
* **Unit:** Acts as a Smart Meter device

## Data Concentrator
1. `make dc`
1.  `bin/dc --key <KEY> --node <HOST-NAME> --port <PORT-NUMBER> [--in <INPUT>] [--out <OUTPUT>]`

## Unit
1. `make unit`
1.  `bin/unit --key <KEY> --node <HOST-NAME> --port <PORT-NUMBER> [--clear]`
