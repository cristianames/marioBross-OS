cd ../../../
apt-get install libssl-dev
curl -L https://github.com/sisoputnfrba/massive-file-
creator/tarball/master -o mfc.tar.gz && tar xvfz mfc.tar.gz
cd xvfz
gcc massive-file-creator.c -o mfc -lcrypto -lpthread
./mfc 10 1024 tmp test_
