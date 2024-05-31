#!/bin/bash
git clone https://github.com/dantesprk/mkl.git ./mkl_build
cd ./mkl_build/src
qmake mkl.pro
make -j4

sudo mkdir /etc/mkl -p
sudo cp ./mkl /etc/mkl/
sudo pacman -S hidapi --noconfirm
sudo /etc/mkl/mkl left green high middle green high right green high 

cd ../..
rm -rdf ./mkl_build

sudo cp ./root/lib/systemd/system/enable_mkl.service /lib/systemd/system/
sudo systemctl enable enable_mkl.service
sudo systemctl start enable_mkl.service

sudo cp ./root/lib/systemd/system/enable_mkl_sleep.service /lib/systemd/system/
sudo systemctl enable enable_mkl_sleep.service
sudo systemctl start enable_mkl_sleep.service


