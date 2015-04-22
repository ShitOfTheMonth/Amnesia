# Amnesia
A key/value store that forgets everything you send it

## Connecting
Start a TCP session to the connector port (default is 6789), and send one of the following commands:

* **GET** [key] - Always returns null because it doesn't exist.
* **PUT** [key] [value] - "Saves" the value
* **CLIENTS** - Lists the connected clients
* **INFO** - Displays server information

## Compiling
If you actually care enough to compile it, all you need is gcc and make.

`make` should do the trick.

The binary will be `./bin/amnesia`

## Running
Running the program without any arguments will run the server and bind it to `0.0.0.0:6789` by default.

The `-b` argument changes the hostname (`1.2.3.4`, `host.tld`, etc.)

The `-p` argument changes the port number.

# License
This piece of shit is licensed under the MIT license. (God bless anyone wanting to adapt this.)

*Copyright (C) 2015 ShitOfTheMonth*
