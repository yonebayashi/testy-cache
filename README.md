# HW3: Testy cache

**Authors: David Tamas-Parris, Hien Nguyen**

To execute all tests, first [install Catch2 from git repository](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository), then from the command line, run:

```
g++ -std=c++17 -Wall -o test_cache_lib test_cache_lib.cc && ./test_cache_lib --success

```
## Part 1

We test the following cases for when the Evictor is a nullptr Evictor and when it is a FIFO evictor.

Test name | Description | Status
--- | --- | ---
Set/Get | Getting a key that wasn't inserted | PASSED
Set/Get | Getting a key that was inserted | PASSED
Set/Get | Getting a key that was inserted and modified | PASSED
Set/Get | Getting a key that was inserted and deleted | PASSED
Space used | Memory used is initially empty and should be updated correctly when new keys are inserted or removed | PASSED
Reset | Calling `reset` returns an empty cache | PASSED

## Part 2

### Aaron/Alex

[Project repo](https://gitlab.com/InternetUnexplorer/CSCI_389_HW2)

Test name | Status
--- | ---


### Jonah/Elijah

[Project repo](https://github.com/TheReverb/hash_it_out/tree/master)

Test name | Status
--- | ---

### Aryeh/Connor

[Project repo](https://github.com/astah100/HW2AryehStahlAndConnorDeiparine)

Test name | Status
--- | ---
