Netinvert: Example POCO Server
=====================================


#   Description

    This program starts a TCP server on the port 28888 ( or any other,
if supplied ), accepts an external connection, reverses any received input
and sends it back to the client.


#   How to build

    The apllication is supposed to be built in the Linux environment
with libpoco-dev package preinstalled.

    To build the apllication, extract the program archive to the chosen
directory, change the directory to the one that was just unpacked, and type:

        make


#   Usage

    To run the application from its directory, just type:

        ./netinvert
    
    If there is any need to change the server port number, use
corresponding option:

        ./netinvert -p<port>
        ./netinvert --port=<port>
