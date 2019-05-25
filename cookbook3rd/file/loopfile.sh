dd if=/dev/zero of=loopbackfile.img bs=5M count=1
ls -lh loopbackfile.img

mkfs.ext4 loopbackfile.img
ls -lh loopbackfile.img

#if [ -d "/mnt/loopback" ]; then
#    rm -rf /mnt/loopback
#fi
#mkdir /mnt/loopback
#mount -o loop loopbackfile.img /mnt/loopback
#ls -alh /mnt/loopback
#umount /mnt/loopback
#ls -alh /mnt/loopback

losetup /dev/loop1 loopbackfile.img
fdisk /dev/loop1
