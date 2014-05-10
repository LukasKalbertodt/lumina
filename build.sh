clear
cd lumina && make -j8 DEBUG=1 ASAN=1 && cd ..
make clean
make -j8 DEBUG=1 ASAN=1
echo "----------------------------------------"
echo ""
optirun ./test