#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp $SYSROOT/boot/blueberry.kernel isodir/boot/blueberry.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "blueberry" {
	multiboot /boot/blueberry.kernel
}
EOF
grub-mkrescue -o blueberry.iso isodir
