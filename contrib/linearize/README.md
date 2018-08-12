### Linearize ###
Construct a linear, no-fork, best version of the blockchain.

compress for distribution:
tar -cvJf bootstrap.dat.xz ./bootstrap.dat

provide a sha265 hash:
sha256sum bootstrap.dat.xz > SHA256SUM.asc