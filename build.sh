clear
cd lumina && make -j8 ASAN=1 && cd ..
make clean
make -j8 ASAN=1 test.bin
echo "----------------------------------------"
echo ""
optirun ./test.bin