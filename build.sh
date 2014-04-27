clear
make clean
make -j8 DEBUG=1 ASAN=1
echo "----------------------------------------"
echo ""
./test