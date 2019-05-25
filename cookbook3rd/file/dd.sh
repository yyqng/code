#Root Be carefull : of=
#dd of=/tmp/junk.data bs=1c count=3
#dd if=/dev/zero of=/tmp/junk.data bs=1c count=2
#dd if=/dev/zero of=/tmp/junk.data bs=1w count=2
#dd if=/dev/zero of=/tmp/junk.data bs=1B count=2
#dd if=/dev/zero of=/tmp/junk.data bs=1K count=2
#dd if=/dev/zero of=/tmp/junk.data bs=1M count=2
#dd if=/dev/zero of=/dev/null bs=1G count=1
#dd if=/dev/zero of=/dev/null bs=5M count=5
dd if=/dev/zero of=loopbackfile.img bs=5M count=1
#ls -l /tmp/junk.data
