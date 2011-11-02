all: mslip 

clean:
	rm -f mslip *.o *.log

mslip: mslip.cpp
	g++ -Wall -g mslip.cpp -o mslip
	sudo chown root.root mslip && sudo chmod 4555 mslip

