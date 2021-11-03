# Flow C++ SDK
Flow C++ SDK For Flow Hackathon

## Steps to compile and build the FlowClient

1. Ensure that the required libraries are present and installed.

      ```
      gcc==9.3.0
      g++==9.3.0
      cmake==3.16.3
      protobuf==3.15.8
      grpc==1.40.0
      OpenSSL 1.1.1l
      ```
       
2. Set environment variables in `~/.bashrc`. Ensure that this is the same directory used during the installation of `grpc`.

      ```
      export MY_INSTALL_DIR=$HOME/.local
      export PATH="$MY_INSTALL_DIR/bin:$PATH"
      ```
      
3. Copy the `absl` directory to the install directory.

      ```
      cd grpc
      sudo cp -r third_party/abseil-cpp/absl $HOME/.local/include
      ```
      
4. Clone the project.

      ```
      git clone https://github.com/QMrpy/flow-cpp-sdk.git
      ```
      
5. Build the Flow C++ client. Use `make` if `make -j` fails due to out of memory error. 

      ```
      cd flow-cpp-sdk
      mkdir -p cmake/build
      pushd cmake/build
      cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
      make -j
      ```
     
     The above steps lead to a successful build on Ubuntu WSL2 and Mac OSX Big Sur 11.5. The executable `main` will be created in the `cmake/build` directory.

## Steps to run the FlowClient

1. Start the flow emulator from a terminal.

      ```
      flow emulator
      ```
      
2. From another terminal, run the binary `main`, using the URL of the `host` Flow network.

      ```
      ./main <host>[flow-emulator|flow-mainnet|flow-testnet]
      ```
    
       

