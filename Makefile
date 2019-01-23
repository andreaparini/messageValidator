# See README.txt.

.PHONY: all 

all:    test_validation  
	

clean:
	rm -f test_validation 
	rm -f protoc_middleman person.pb.cc person.pb.h validate.pb.cc validate.pb.h
	rm -f test_validation.o person.pb.o validate.pb.o validator.o
	rm -f *.pyc
	rmdir tutorial 2>/dev/null || true
	rmdir com/example/tutorial 2>/dev/null || true
	rmdir com/example 2>/dev/null || true
	rmdir com 2>/dev/null || true
	
cleandata: clean
	rm -f *.data 

protoc_middleman: person.proto validate.proto
	protoc $$PROTO_PATH --cpp_out=.  *.proto
	@touch protoc_middleman
	
test_validation: test_validation.o validator.o protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -Wall -g -o test_validation test_validation.o person.pb.o validate.pb.o validator.o `pkg-config --cflags --libs protobuf`
	
test_validation.o: test_validation.cc protoc_middleman 
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ test_validation.cc -c -o test_validation.o `pkg-config --cflags --libs protobuf`
	c++ person.pb.cc -c -o person.pb.o `pkg-config --cflags --libs protobuf`
	c++ validate.pb.cc -c -o validate.pb.o `pkg-config --cflags --libs protobuf`
	
	
validator.o:  validator.cc protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ validator.cc -c -o validator.o `pkg-config --cflags --libs protobuf`
	c++ person.pb.cc -c -o person.pb.o `pkg-config --cflags --libs protobuf`
	c++ validate.pb.cc -c -o validate.pb.o `pkg-config --cflags --libs protobuf`
	
	
	
	
	