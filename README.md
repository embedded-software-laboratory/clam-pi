# Clam: LLVM front-end for Crab #

Clam is an [Abstract Interpretation](https://en.wikipedia.org/wiki/Abstract_interpretation)-based static analyzer that computes inductive invariants for
LLVM bitcode based on
the [Crab](https://github.com/seahorn/crab) library. This branch supports LLVM 14.

The available documentation can be found in both
Clam [wiki](https://github.com/seahorn/clam/wiki/Home) and Crab [wiki](https://github.com/seahorn/crab/wiki).

# Docker #

You can get Clam from [Docker Hub](https://hub.docker.com/) (nightly built) using the
command:

     docker pull seahorn/clam-llvm14:nightly

# Requirements #

Clam is written in C++ and uses heavily the Boost library. The
main requirements are:

- Modern C++ compiler supporting c++14 
- Boost >= 1.65
- GMP 
- MPFR (only if `-DCRAB_USE_APRON=ON` or `-DCRAB_USE_ELINA=ON`)
- FLINT (only if `-DCRAB_USE_PPLITE=ON`) 
- Python >= 3.6

In linux, you can install requirements typing the commands:

     sudo apt-get install libboost-all-dev libboost-program-options-dev
     sudo apt-get install libgmp-dev
     sudo apt-get install libmpfr-dev	
     sudo apt-get install libflint-dev

## Tests ##

Testing infrastructure depends on several Python packages. 
To run tests you need to install `lit` and `OutputCheck`:

     pip3 install lit
     pip3 install OutputCheck

# Compilation and installation # 

The basic compilation steps are:

    1. mkdir build && cd build
    2. cmake -DCMAKE_INSTALL_PREFIX=$DIR ../
    3. cmake --build . --target crab && cmake ..   
    4. cmake --build . --target extra && cmake ..                  
    5. cmake --build . --target install 

The command at line 2 will try to find LLVM 14 from standard paths.
If you installed LLVM 14 in a non-standard path, then add option
`-DLLVM_DIR=$LLVM-14_INSTALL_DIR/lib/cmake/llvm` to line 2.  The
command at line 3 will download Crab and compile it from sources.
Clam uses two external components that are installed via the `extra`
target at line 4. These components are:
  
* [sea-dsa](https://github.com/seahorn/sea-dsa) is the heap analysis used to translate LLVM memory
  instructions. Details can be
  found [here](https://jorgenavas.github.io/papers/sea-dsa-SAS17.pdf)
  and [here](https://jorgenavas.github.io/papers/tea-dsa-fmcad19.pdf).
  
* [llvm-seahorn](https://github.com/seahorn/llvm-seahorn) provides specialized versions of LLVM components to make them more amenable for verification. `llvm-seahorn` is optional but hightly recommended.  

The Boxes/Apron/Elina/PPLite domains require third-party libraries. To avoid
the burden to users who are not interested in those domains, the
installation of the libraries is optional.

- If you want to use the Boxes domain then add `-DCRAB_USE_LDD=ON` option.

- If you want to use the Apron library domains then add
  `-DCRAB_USE_APRON=ON` option.

- If you want to use the Elina library domains then add
  `-DCRAB_USE_ELINA=ON` option.

- If you want to use the PPLite library domains then add
  `-DCRAB_USE_APRON=ON -DCRAB_USE_PPLITE=ON` options.

**Important:** Apron and Elina are currently not compatible so you
cannot enable `-DCRAB_USE_APRON=ON` and `-DCRAB_USE_ELINA=ON` at the same time. 

For instance, to install Clam with Boxes and Apron:

    1. mkdir build && cd build
    2. cmake -DCMAKE_INSTALL_PREFIX=$DIR -DCRAB_USE_LDD=ON -DCRAB_USE_APRON=ON ../
    3. cmake --build . --target crab && cmake ..
    4. cmake --build . --target extra && cmake ..                
    5. cmake --build . --target ldd && cmake ..
    6. cmake --build . --target apron && cmake ..             
    7. cmake --build . --target install 

For instance, lines 5 and 6 will download, compile and install the
Boxes and Apron libraries, respectively.  If you have already compiled
and installed these libraries in your machine then skip commands at
line 5 and 6 and add the following options at line 2.

- For Apron: `-DAPRON_ROOT=$APRON_INSTALL_DIR`
- For Elina: `-DELINA_ROOT=$ELINA_INSTALL_DIR`
- For Boxes: `-DCUDD_ROOT=$CUDD_INSTALL_DIR -DLDD_ROOT=$LDD_INSTALL_DIR`
- For PPLite: `-DPPLITE_ROOT=$PPLITE_INSTALL_DIR -DFLINT_ROOT=$FLINT_INSTALL_DIR`

## Checking installation ## 

To run some regression tests:

     cmake --build . --target test-simple

# Usage #

Clam provides a Python script called `clam.py` (located at `$DIR/bin` where `$DIR` is the directory where Clam was installed) to interact with
users. The simplest command is `clam.py test.c`. Type `clam.py --help`
for all options and read
our [wiki](https://github.com/seahorn/clam/wiki/ClamUsage).
