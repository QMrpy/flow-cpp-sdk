# Flow C++ SDK
Flow C++ SDK For Flow Hackathon

## Steps to compile and build the FlowClient

1. Ensure that the required libraries are present and installed

      ```
      gcc==9.3.0
      g++==9.3.0
      cmake==3.16.3
      protobuf==3.15.8
      grpc==1.40.0
      ```
       
2. Set environment variables in `~/.bashrc`

      ```
      export MY_INSTALL_DIR=$HOME/.local
      export PATH="$MY_INSTALL_DIR/bin:$PATH"
      ```
      
3. Clone the project

      ```
      git clone https://github.com/QMrpy/flow-cpp-sdk.git
      ```
      
4. Build the Flow C++ client. Use `make` if `make -j` fails due to out of memory error. 

      ```
      cd flow-cpp-sdk
      mkdir -p cmake/build
      pushd cmake/build
      cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
      make -j
      popd
      ```
      
     Currently, the `main` function is included in `client/client.cc`, to generate the `client` binary. However, this should not be the case, and it will be later removed. The `client.o` object should be linked to the `testClient` binary, so as to test the SDK on the Flow Emulator.
     
     The above steps lead to a successful build on Ubuntu WSL2.
    
       

