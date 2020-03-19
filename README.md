# HW3: Testy cache

**Authors: David Tamas-Parris, Hien Nguyen**

To execute all tests, first [install Catch2 from git repository](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository), then from the command line, run:

```
g++ -std=c++17 -Wall -o test_cache_lib test_cache_lib.cc && ./test_cache_lib --success

```
## Part 1

We crafted tests for the following desired functionality for both the cases where Evictor is a *nullptr* evictor and when it is a FIFO Evictor. The statuses reflect the result when run on our own code: 

Test name |  Description | Status
 --- | --- | ---

Get Nothing |  Assuring that `get` should not retreive a key that wasn't inserted. | PASSED
Insertions without Crashing | Assuring that the cache should handle 100 insertions without crashing. | PASSED
Deletions without Crashing | Assuring that the cache should handle 100 deletions without crashing. | PASSED
Set/Get 1 | `get` should retreive an inserted key and modify `size` appropriately (with 1 item in cache). | PASSED
Set/Get 2 |  `get` should retreive an inserted key and modify `size` appropriately (with 2 items in cache). | PASSED
Set/Get 3 |  `get` should retreive an inserted key and modify `size` appropriately (with 3 items in cache). | PASSED
Tracking Memory | Assuring that `space_used()` responds appropriately to new insertions. | PASSED
Modification | `get` should retreive a key that was inserted and modified. | PASSED
Proper Deletion |  `get` should not retreive a key that was inserted and deleted. | PASSED
Proper Resetting | resetting should result in an empty cache. | PASSED

The following test was crafted for the case of a *nullptr* evictor: 
Test name |  Description | Status
 --- | --- | ---

Null Eviction Policy | Eviction policy with nullptr evictor should not allow an insertion that would cause an overflow. | PASSED

The following tests were crafted for the case of a FifoEvictor evictor: 
Test name |  Description | Status
 --- | --- | ---

`touch_key` without Crashing | Assure that the FIFO evictor can handle 100 key touches without crashing. | PASSED
FIFO 1 | FIFO evictor displays FIFO functionality with unique keys. | PASSED
FIFO 2 | FIFO evictor displays FIFO functionality with nonunique keys. | PASSED
FIFO Set/Get |  Inserting works with FIFO eviction. | PASSED

It should be noted that these tests pass when compiled and run on a Mac. When compiled in the virtual machine, the tests stop due to an instance of `std::length_error`. After running our original tests in valgrind, we believe this is due to a memory error.

## Part 2

### Aaron/Alex

[Project repo](https://gitlab.com/InternetUnexplorer/CSCI_389_HW2)

We ran into a small compilation error. Adding `#pragma once` to `fifo_evictor.hh` fixed it. Most tests pass, but several tests fail due to incorrect values for `size` after running get. Additonally, the evictor fails the "FIFO evictor displays FIFO functionality with nonunique keys" and "FIFO evictor displays FIFO functionality with unique keys" tests.


### Jonah/Elijah

[Project repo](https://github.com/TheReverb/hash_it_out/tree/master)


The tests hault due to a **segmentation fault** when attempting to test the FIFO evictor by repeatedly touching keys. Otherwise, the only assertions that fail have to do with incorrect values for `size` after retreiving a key.
### Aryeh/Connor

[Project repo](https://github.com/astah100/HW2AryehStahlAndConnorDeiparine)


This group seems to have modified the header file and used a nonstandard interface, causing compilation issues. They can be fixed by renaming their FIFO evictor class from `FIFO` to `FifoEvictor`. Tests halt on this code due to a SIGABORT on the "Cache should handle 100 insertions without crashing" test.
