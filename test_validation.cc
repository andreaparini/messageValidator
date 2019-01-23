// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

#include "person.pb.h"
#include "google/protobuf/wrappers.pb.h"
#include "validator.h"

using namespace std;

using google::protobuf::util::TimeUtil;
using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Int32Value;
using google::protobuf::Message;


// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person;
    
     // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found. Creating new file." << endl;
    } else if (!person.ParseFromIstream(&input)) {
      cerr << "Failed to parse person." << endl;
      return -1;
    }
    
    
    int32_t true_equal    = 5;
    int32_t true_lt       = 5 - 1 ;
    int32_t true_lte      = 5  ;
    int32_t true_lte2     = 5 - 1;
    int32_t true_gt       = 5 + 1;
    int32_t true_gte      = 5;
    int32_t true_gte2     = 5 + 1;
    
    int32_t false_equal     = 5 - 1;
    int32_t false_lt        = 5 + 1;
    int32_t false_lte       = 5 + 1;
    int32_t false_lte2      = 5 + 1;
    int32_t false_gt        = 5 - 1;
    int32_t false_gte       = 5 - 1;
    int32_t false_gte2      = 5 + 1;
   
    Int32Value* wrap_true_equal = person.mutable_true_equal();
    wrap_true_equal->set_value(true_equal);
    
    Int32Value* wrap_true_lt = person.mutable_true_lt();
    wrap_true_lt->set_value(true_lt);
    
    Int32Value* wrap_true_lte = person.mutable_true_lte();
    wrap_true_lte->set_value(true_lte);
    
    Int32Value* wrap_true_lte2 = person.mutable_true_lte2();
    wrap_true_lte2->set_value(true_lte2);
    
    Int32Value* wrap_true_gt = person.mutable_true_gt();
    wrap_true_gt->set_value(true_gt);
    
    Int32Value* wrap_true_gte = person.mutable_true_gte();
    wrap_true_gte->set_value(true_gte);
    
    Int32Value* wrap_true_gte2 = person.mutable_true_gte2();
    wrap_true_gte2->set_value(true_gte2);
    
    Int32Value* wrap_false_equal = person.mutable_false_equal();
    wrap_false_equal->set_value(false_equal);
    
    Int32Value* wrap_false_lt = person.mutable_false_lt();
    wrap_false_lt->set_value(false_lt);
    
    Int32Value* wrap_false_lte = person.mutable_false_lte();
    wrap_false_lte->set_value(false_lte);
    
    Int32Value* wrap_false_lte2 = person.mutable_false_lte2();
    wrap_false_lte2->set_value(false_lte2);
    
    Int32Value* wrap_false_gt = person.mutable_false_gt();
    wrap_false_gt->set_value(false_gt);
    
    Int32Value* wrap_false_gte = person.mutable_false_gte();
    wrap_false_gte->set_value(false_gte);
    
    Int32Value* wrap_false_gte2 = person.mutable_false_gte2();
    wrap_false_gte2->set_value(false_gte2);
    
    // Write the new person back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!person.SerializeToOstream(&output)) {
      cerr << "Failed to write person." << endl;
      return -1;
    }
    
    Validator v;
    
    
    bool messageOK = v.validate(person);
     
    
  

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
