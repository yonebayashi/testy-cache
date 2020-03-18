# HW3: Testy cache

**Authors: David Tamas-Parris, Hien Nguyen**

To execute all tests, first [install Catch2 from git repository](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository), then from the command line, run:

```
g++ -std=c++17 -Wall -o test_cache_lib test_cache_lib.cc && ./test_cache_lib --success

```
## Part 1

We test the following cases for when the Evictor is a nullptr Evictor:

Test name/ Description | Status
 --- | --- | ---
Set/Get | Getting a key that wasn't inserted | PASSED
Set/Get | Getting a key that was inserted | PASSED
Set/Get | Getting a key that was inserted and modified | PASSED
Set/Get | Getting a key that was inserted and deleted | PASSED
Space used | Memory used is initially empty and should be updated correctly when new keys are inserted or removed | PASSED
Reset | Calling `reset` returns an empty cache | PASSED

It should be noted that these tests were compiled and run on a Mac. When compiled in the virtual machine, the tests stop due to an instance of `std::length_error`. After running our original tests in valgrind, we believe this is due to a memory error.

## Part 2

### Aaron/Alex

[Project repo](https://gitlab.com/InternetUnexplorer/CSCI_389_HW2)

We ran into a small compilation error. Adding `#pragma once` to `fifo_evictor.hh` fixed it. Most tests pass, but several tests fail due to incorrect values for `size` after running get. Additonally, the evictor fails the "FIFO evictor displays FIFO functionality with nonunique keys" and "FIFO evictor displays FIFO functionality with unique keys" tests.

Test name | Status
--- | ---
Set/Get | PASSED
Set/Get | PASSED
Set/Get | PASSED
Set/Get | PASSED
Space used | **FAILED**
Reset | PASSED

### Jonah/Elijah

[Project repo](https://github.com/TheReverb/hash_it_out/tree/master)

Test name | Status
--- | ---

The tests hault due to a segmentation fault when attempting to test the FIFO evictor by repeatedly touching keys. Otherwise, the only assertions that fail have to do with incorrect values for `size` after retreiving a key.
### Aryeh/Connor

[Project repo](https://github.com/astah100/HW2AryehStahlAndConnorDeiparine)


Test name | Status
--- | ---

This group seems to have modified the header file and used a nonstandard interface, causing compilation issues. They can be fixed by renaming their FIFO evictor class from `FIFO` to `FifoEvictor`. Tests halt on this code due to a SIGABORT on the "Cache should handle 100 insertions without crashing" test.
