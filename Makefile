# See README.txt.

TEST_DIR = test
SRC_DIR = src
PROTO_DIR = proto

.PHONY: all 

all:    $(TEST_DIR)/test_validation  $(TEST_DIR)/test_failures
	

clean:
	rm -f $(TEST_DIR)/test_validation $(TEST_DIR)/test_failures
	rm -f $(PROTO_DIR)/protoc_middleman $(PROTO_DIR)/*.pb.cc $(PROTO_DIR)/*.pb.h
	rm -f $(TEST_DIR)/*.o 
	rm -f $(SRC_DIR)/validator.o
	
	
	
cleandata: clean
	rm -f *.data 

$(PROTO_DIR)/protoc_middleman: $(PROTO_DIR)/test1.proto $(PROTO_DIR)/test2.proto $(PROTO_DIR)/validate.proto
	protoc -I=$(PROTO_DIR) --cpp_out=$(PROTO_DIR)  $(PROTO_DIR)/*.proto
	@touch $(PROTO_DIR)/protoc_middleman
	
$(TEST_DIR)/test_validation: $(TEST_DIR)/test_validation.o $(SRC_DIR)/validator.o $(PROTO_DIR)/protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -Wall -g -o $(TEST_DIR)/test_validation $(TEST_DIR)/test_validation.o $(PROTO_DIR)/test1.pb.o  \
	       $(PROTO_DIR)/validate.pb.o $(SRC_DIR)/validator.o `pkg-config --cflags --libs protobuf`
	
$(TEST_DIR)/test_validation.o: $(TEST_DIR)/test_validation.cc $(PROTO_DIR)/protoc_middleman 
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(TEST_DIR)/test_validation.cc -c -o $(TEST_DIR)/test_validation.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/test1.pb.cc -c -o $(PROTO_DIR)/test1.pb.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/validate.pb.cc -c -o $(PROTO_DIR)/validate.pb.o `pkg-config --cflags --libs protobuf`
	
$(TEST_DIR)/test_failures: $(TEST_DIR)/test_failures.o $(SRC_DIR)/validator.o $(PROTO_DIR)/protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -Wall -g -o $(TEST_DIR)/test_failures $(TEST_DIR)/test_failures.o $(PROTO_DIR)/test2.pb.o \
	       $(PROTO_DIR)/validate.pb.o $(SRC_DIR)/validator.o `pkg-config --cflags --libs protobuf`
	
$(TEST_DIR)/test_failures.o: $(TEST_DIR)/test_failures.cc $(PROTO_DIR)/protoc_middleman 
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(TEST_DIR)/test_failures.cc -c -o $(TEST_DIR)/test_failures.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/test2.pb.cc -c -o $(PROTO_DIR)/test2.pb.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/validate.pb.cc -c -o $(PROTO_DIR)/validate.pb.o `pkg-config --cflags --libs protobuf`	
	
	
$(SRC_DIR)/validator.o:  $(SRC_DIR)/validator.cc $(PROTO_DIR)/protoc_middleman
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ $(SRC_DIR)/validator.cc -c -o $(SRC_DIR)/validator.o `pkg-config --cflags --libs protobuf`
	c++ $(PROTO_DIR)/validate.pb.cc -c -o $(PROTO_DIR)/validate.pb.o `pkg-config --cflags --libs protobuf`
	
	
	
	
	