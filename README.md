# libsvm DEMO

Use libsvm to implement simple classification problems.

## Development

1. download the libsvm:
   ```bash
   wget https://github.com/cjlin1/libsvm/archive/v324.tar.gz

   tar xf v324.tar.gz
   ```

2. build the libsvm.so.2
   ```bash
   cd libsvm-324
   make lib
   ```

3. copy the libsvm to this project
   ```bash
   cp libsvm.so.2 path/to/this/project/
   ```

4. create a symbolic link
   ```bash
   ln -s libsvm.so.2 libsvm.so
   ```

5. run demo
   ```bash
   make
   ./demo
   ```
