// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

#include "person2.pb.h"
#include "google/protobuf/wrappers.pb.h"
#include "validator.h"

using namespace std;

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

using google::protobuf::FloatValue;
using google::protobuf::DoubleValue;
using google::protobuf::Int32Value;
using google::protobuf::Int64Value;
using google::protobuf::UInt32Value;
using google::protobuf::UInt64Value;



// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial2::Person person;
    
     // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found. Creating new file." << endl;
    } else if (!person.ParseFromIstream(&input)) {
      cerr << "Failed to parse person." << endl;
      return -1;
    }
    
    
    //defining test values
    
    float floattrue_equal    = 5.;
    float floattrue_lt       = 5. - 1. ;
    float floattrue_lte      = 5.  ;
    float floattrue_lte2     = 5. - 1.;
    float floattrue_gt       = 5. + 1.;
    float floattrue_gte      = 5.;
    float floattrue_gte2     = 5. + 1.;
    
    float floatfalse_equal     = 5. - 1.;
    float floatfalse_lt        = 5. + 1.;
    float floatfalse_lte       = 5. + 1.;
    float floatfalse_lte2      = 5. + 1.;
    float floatfalse_gt        = 5. - 1.;
    float floatfalse_gte       = 5. - 1.;
    float floatfalse_gte2      = 5. + 1.;
    
    double doubletrue_equal    = 5.;
    double doubletrue_lt       = 5. - 1 ;
    double doubletrue_lte      = 5.  ;
   
    // float
    FloatValue* floatwrap_true_equal = person.mutable_floattrue_equal();
    floatwrap_true_equal->set_value(floattrue_equal);  
    FloatValue* floatwrap_true_lt = person.mutable_floattrue_lt();
    floatwrap_true_lt->set_value(floattrue_lt);
    FloatValue* floatwrap_true_lte = person.mutable_floattrue_lte();
    floatwrap_true_lte->set_value(floattrue_lte);
    FloatValue* floatwrap_true_lte2 = person.mutable_floattrue_lte2();
    floatwrap_true_lte2->set_value(floattrue_lte2);
    FloatValue* floatwrap_true_gt = person.mutable_floattrue_gt();
    floatwrap_true_gt->set_value(floattrue_gt);
    FloatValue* floatwrap_true_gte = person.mutable_floattrue_gte();
    floatwrap_true_gte->set_value(floattrue_gte);
    FloatValue* floatwrap_true_gte2 = person.mutable_floattrue_gte2();
    floatwrap_true_gte2->set_value(floattrue_gte2);
    FloatValue* floatwrap_false_equal = person.mutable_floatfalse_equal();
    floatwrap_false_equal->set_value(floatfalse_equal);
    FloatValue* floatwrap_false_lt = person.mutable_floatfalse_lt();
    floatwrap_false_lt->set_value(floatfalse_lt);
    FloatValue* floatwrap_false_lte = person.mutable_floatfalse_lte();
    floatwrap_false_lte->set_value(floatfalse_lte);
    FloatValue* floatwrap_false_lte2 = person.mutable_floatfalse_lte2();
    floatwrap_false_lte2->set_value(floatfalse_lte2);
    FloatValue* floatwrap_false_gt = person.mutable_floatfalse_gt();
    floatwrap_false_gt->set_value(floatfalse_gt);
    FloatValue* floatwrap_false_gte = person.mutable_floatfalse_gte();
    floatwrap_false_gte->set_value(floatfalse_gte);
    FloatValue* floatwrap_false_gte2 = person.mutable_floatfalse_gte2();
    floatwrap_false_gte2->set_value(floatfalse_gte2);

    
    
    // double
    DoubleValue* doublewrap_true_equal = person.mutable_doubletrue_equal();
    doublewrap_true_equal->set_value(doubletrue_equal);  
    DoubleValue* doublewrap_true_lt = person.mutable_doubletrue_lt();
    doublewrap_true_lt->set_value(doubletrue_lt);
    DoubleValue* doublewrap_true_lte = person.mutable_doubletrue_lte();
    doublewrap_true_lte->set_value(doubletrue_lte);
    

    
    

    
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
