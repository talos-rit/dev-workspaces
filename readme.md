# GRPC spike

## Goal

The goal of this project is not to make a complete implementation, but a proof of concept for how grpc would interact with our current architecture.

## Current issue we are trying to resolve:

We currently use sockets to handle our communication from our external compute or client interface to our robot running the operator. 
While socket currently works fine with the feature sets we have, it can prove to be difficult moving forward due to several reasons.

1. Wrong architecture

The socket is well suited for an application that is event driven where we want our robot to be notified when a user clicks on a button on the interface. While this could work, our intuition when implementing new features is thought of as a request response architecture where we want our robot to listen to requests that users make on the interface and potentially respond back. 

2. Serialization and deserialization of byte data

Sending minimal byte data caused several pain points on both operator and commander applications. For commander using python, we were making byte conversions with little gurantee of correct package delivery and forced byte logic to be handled in python. With operator using cpp, we needed to cast the byte into correct type as well as correctly revalidate data payload. This especially was a problem for cpp as we were forced to either write twice as much code for more robust and secure implementation or write several dangerous operations and bad software practices to allow functionality.

3. Several pitfalls for poor quality software implementation for future developers

This is a more detailed point of the mark made in the last sentence of problem 2. We were making several bad decisions on the operator application, that could potentially give excuse for future devs to allow bad practices in cpp that opens us to miss management of code and degrade software quality. With current socket implementation we need to read byte and convert to proper structs in cpp that forces us to trust on the sender to properly send the correct data length and reinterpret or cast the byte data into the correct data type before accepting the request from client which also added more custom implementation.

## Solution

With this repository, I want to attempt to solve all pain points of current implementation by using grpc. To mimic the original project, I have set up this monolith architecture with two client applications. 
- cpp-ws or server side application: This represents the cpp implementation of grpc using cpp that is going to mimic the job of the operator.
- python-ws or client side application: This represents the python implementation of grpc using python that is going to mimic the job of the commander.

While I am not going to fully mimic the job of the two applications I want to acomplish two things, fully implement the logic for sending and receiving messages from both ends, and also mimic the icd spec that we currently have for our robotic application.

## Buf CLI integration

- **Module file**: `proto/buf.yaml` — declares the proto module used by Buf.
- **Workspace file**: `buf.work.yaml` — includes the `proto` directory as a module.
- **Generate template**: `buf.gen.yaml` — a template showing example plugin outputs.

Locally run to generate protobuf script for each workspace:
```bash
buf generate
```

## Compiling code and test scripts

To work on the cpp workspace open the devcontainer and run the following scripts:
```
./scripts/install.sh
./scripts/build.sh
```
Then to run the cpp server
```
./cpp-ws/build/talos
```

To test using the python workspace run
```
uv run python-ws/main.py
```
This will make all of the grpc endpoint request to the cpp server.