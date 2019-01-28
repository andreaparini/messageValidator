# See README.txt.

TEST_DIR = test
SRC_DIR = src
PROTO_DIR = proto

.PHONY: all 

all:    $(TEST_DIR)/test_main
	

clean:
	rm -f $(TEST_DIR)/test_main
	rm -f $(PROTO_DIR)/protoc_middleman $(PROTO_DIR)/*.pb.cc $(PROTO_DIR)/*.pb.h
	rm -f $(TEST_DIR)/*.o 
	rm -f $(SRC_DIR)/validator.o
	
	
	
cleandata: clean
	rm -f *.data 


# test_main takes the .o files and builds the test executable
$(TEST_DIR)/test_main: $(TEST_DIR)/test.o $(SRC_DIR)/validator.o $(PROTO_DIR)/protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(TEST_DIR)/test_main.cc -c -o $(TEST_DIR)/test_main.o `pkg-config --cflags --libs protobuf`
	c++ -Wall -g -o $(TEST_DIR)/test_main $(TEST_DIR)/test_main.o $(TEST_DIR)/test.o \
	$(PROTO_DIR)/test1.pb.o $(PROTO_DIR)/test2.pb.o $(PROTO_DIR)/validate.pb.o \
	$(SRC_DIR)/validator.o `pkg-config --cflags --libs protobuf`


# protoc_middleman compiles the protos
$(PROTO_DIR)/protoc_middleman: $(PROTO_DIR)/test1.proto $(PROTO_DIR)/test2.proto $(PROTO_DIR)/validate.proto
	protoc -I=$(PROTO_DIR) --cpp_out=$(PROTO_DIR)  $(PROTO_DIR)/*.proto
	@touch $(PROTO_DIR)/protoc_middleman

	
$(TEST_DIR)/test.o: $(TEST_DIR)/test.cc $(PROTO_DIR)/protoc_middleman 
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(TEST_DIR)/test.cc -c -o $(TEST_DIR)/test.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/test1.pb.cc -c -o $(PROTO_DIR)/test1.pb.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/validate.pb.cc -c -o $(PROTO_DIR)/validate.pb.o `pkg-config --cflags --libs protobuf`

	
$(SRC_DIR)/validator.o:  $(SRC_DIR)/validator.cc $(PROTO_DIR)/protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(SRC_DIR)/validator.cc -c -o $(SRC_DIR)/validator.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/validate.pb.cc -c -o $(PROTO_DIR)/validate.pb.o `pkg-config --cflags --libs protobuf`
	
	
	
	
	