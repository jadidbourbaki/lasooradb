# lasooradb

A write-optimized key value store.

LasooraDB uses a variant of an LSM tree that has
two levels (one memory level and one disk level).
The runs in this LSM tree variant are not sorted
in order to have O(1) writes instead of O(logN)
writes. Further, compaction is not done.

The goal here is to design a very write-optimized
key value store at the expense of reads.

The implementation is not currently thread-safe.

## Building 

```
meson setup builddir
cd builddir
meson compile
```

## Testing

```
meson setup builddir
cd builddir
meson test -v
```

