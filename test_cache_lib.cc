// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <iostream>
#include <cassert>
#include <typeinfo>
#include <cstring>

#include "evictor.hh"
#include "cache.hh"
#include "fifo_evictor.hh"

#include "cache_lib.cc"   // for testing purpose
#include "fifo_evictor.cc"  // for testing purpose



TEST_CASE ("Cache with nullptr Evictor", "[cache]") {
  Cache cache(8, 0.75, nullptr);
  REQUIRE(cache.space_used() == 0);

  const Cache::val_type val1 = "1";
  const Cache::val_type val2 = "2";
  const Cache::val_type val3 = "16";
  const Cache::val_type val4 = "17";

  Cache::size_type size;

  SECTION( "should not get a key that wasn't inserted" ) {
    REQUIRE(cache.get("k1", size) == NULL);
    REQUIRE(size == 0);
  }

  SECTION( "should get a key that was inserted" ) {
    cache.set("k1", val1, strlen(val1)+1);

    REQUIRE(strcmp(cache.get("k1", size), val1) == 0);   // string comparision
    REQUIRE(size == strlen(val1)+1);

    // inserting extra keys should increment memory used correctly
    cache.set("k2", val2, strlen(val2)+1);

    REQUIRE(strcmp(cache.get("k2", size), val2) == 0);
    REQUIRE(size == strlen(val2)+1);
    REQUIRE(cache.space_used() == 4);

    // should not insert any more key when maxmem has been exceeded
    cache.set("k3", val3, strlen(val3)+1);

    REQUIRE(strcmp(cache.get("k3", size), val3) == 0);
    REQUIRE(size == strlen(val3)+1);
    REQUIRE(cache.space_used() == 7);

    cache.set("k4", val4, strlen(val4)+1);

    REQUIRE(cache.get("k4", size) == NULL);
    REQUIRE(size == 0);
    REQUIRE(cache.space_used() == 7);
  }

  SECTION( "should get a key that was inserted and modified" ) {
    cache.set("k3", val3, strlen(val3)+1);

    REQUIRE(strcmp(cache.get("k3", size), val3) == 0);
    REQUIRE(size == strlen(val3)+1);
    REQUIRE(cache.space_used() == size);

    // modify value of key 3
    cache.set("k3", val4, strlen(val4)+1);

    REQUIRE(strcmp(cache.get("k3", size), val4) == 0);
    REQUIRE(size == strlen(val4)+1);
    REQUIRE(cache.space_used() == strlen(val4)+1);
  }

  SECTION( "should not get a key that was inserted and deleted" ) {
    cache.set("k1", val1, strlen(val1)+1);

    REQUIRE(strcmp(cache.get("k1", size), val1) == 0);   // string comparision
    REQUIRE(size == strlen(val1)+1);
    REQUIRE(cache.space_used() == 2);

    cache.del("k1");
    REQUIRE(cache.get("k1", size) == NULL);
    REQUIRE(size == 0);
    REQUIRE(cache.space_used() == 0);
  }

  SECTION( "resetting should return empty cache" ) {
    cache.set("k1", val1, strlen(val1)+1);
    cache.set("k2", val2, strlen(val2)+1);

    cache.reset();
    REQUIRE(cache.space_used() == 0);
  }
}


TEST_CASE ("Cache with FIFO Evictor", "[evictor]") {
  FifoEvictor* evictor= new FifoEvictor();
  Cache cache(8, 0.75, evictor);
  REQUIRE(cache.space_used() == 0);

  const Cache::val_type val1 = "1";
  const Cache::val_type val2 = "2";
  const Cache::val_type val3 = "16";
  const Cache::val_type val4 = "17";

  Cache::size_type size;

  SECTION( "should not get a key that wasn't inserted" ) {
    REQUIRE(cache.get("k1", size) == NULL);
    REQUIRE(size == 0);
  }

  SECTION( "should get a key that was inserted" ) {
    cache.set("k1", val1, strlen(val1)+1);

    REQUIRE(strcmp(cache.get("k1", size), val1) == 0);   // string comparision
    REQUIRE(size == strlen(val1)+1);

    // inserting extra keys should increment memory used correctly
    cache.set("k2", val2, strlen(val2)+1);

    REQUIRE(strcmp(cache.get("k2", size), val2) == 0);
    REQUIRE(size == strlen(val2)+1);
    REQUIRE(cache.space_used() == 4);

    // when maxmem has been exceeded, should evict existing keys in FIFO order to make space for the new key
    cache.set("k3", val3, strlen(val3)+1);

    REQUIRE(strcmp(cache.get("k3", size), val3) == 0);
    REQUIRE(size == strlen(val3)+1);
    REQUIRE(cache.space_used() == 7);

    cache.set("k4", val4, strlen(val4)+1);

    // successfully inserted key 4
    REQUIRE(strcmp(cache.get("k4", size), val4) == 0);
    REQUIRE(size == strlen(val4)+1);

    // key 1 should be evicted
    REQUIRE(cache.get("k1", size) == NULL);
    REQUIRE(size == 0);

    // total memory used is occupied by key 2->4
    REQUIRE(cache.space_used() == 8);
  }

  SECTION( "should get a key that was inserted and modified" ) {
    cache.set("k3", val3, strlen(val3)+1);

    REQUIRE(strcmp(cache.get("k3", size), val3) == 0);
    REQUIRE(size == strlen(val3)+1);
    REQUIRE(cache.space_used() == size);

    // modify value of key 3
    cache.set("k3", val4, strlen(val4)+1);

    REQUIRE(strcmp(cache.get("k3", size), val4) == 0);
    REQUIRE(size == strlen(val4)+1);
    REQUIRE(cache.space_used() == strlen(val4)+1);
  }

  SECTION( "should not get a key that was inserted and deleted" ) {
    cache.set("k1", val1, strlen(val1)+1);

    REQUIRE(strcmp(cache.get("k1", size), val1) == 0);   // string comparision
    REQUIRE(size == strlen(val1)+1);
    REQUIRE(cache.space_used() == 2);

    cache.del("k1");
    REQUIRE(cache.get("k1", size) == NULL);
    REQUIRE(size == 0);
    REQUIRE(cache.space_used() == 0);
  }

  SECTION( "resetting should return empty cache" ) {
    cache.set("k1", val1, strlen(val1)+1);
    cache.set("k2", val2, strlen(val2)+1);

    cache.reset();
    REQUIRE(cache.space_used() == 0);
  }
}
