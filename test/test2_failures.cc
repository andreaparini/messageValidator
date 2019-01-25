// See README.txt for information and build instructions.

#include <fstream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

#include "../proto/test2.pb.h"
#include "google/protobuf/wrappers.pb.h"
#include "../src/validator.h"

using namespace std;

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Message;

using google::protobuf::DoubleValue;
using google::protobuf::Int32Value;
using google::protobuf::Int64Value;
using google::protobuf::UInt32Value;
using google::protobuf::UInt64Value;


vector<Validator::ValidationOutput> test2_failures () {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial2::Person person;
    
    vector<Validator::ValidationOutput> messageStatus;
    
    
    
    //defining test values
    
    int64_t int64true_equal    = 5.;
    int64_t int64true_lt       = 5. - 1. ;
    int64_t int64true_lte      = 5.  ;
    int64_t int64true_lte2     = 5. - 1.;
    int64_t int64true_gt       = 5. + 1.;
    int64_t int64true_gte      = 5.;
    int64_t int64true_gte2     = 5. + 1.;
    
    int64_t int64false_equal     = 5. - 1.;
    int64_t int64false_lt        = 5. + 1.;
    int64_t int64false_lte       = 5. + 1.;
    int64_t int64false_lte2      = 5. + 1.;
    int64_t int64false_gt        = 5. - 1.;
    int64_t int64false_gte       = 5. - 1.;
    int64_t int64false_gte2      = 5. + 1.;
    
    double doubletrue_equal    = 5.;
    double doubletrue_lt       = 5. ;
    double doubletrue_lte      = 5. - 1. ;
   
    // int64
    Int64Value* int64wrap_true_equal = person.mutable_int64true_equal();
    int64wrap_true_equal->set_value(int64true_equal);  
    Int64Value* int64wrap_true_lt = person.mutable_int64true_lt();
    int64wrap_true_lt->set_value(int64true_lt);
    Int64Value* int64wrap_true_lte = person.mutable_int64true_lte();
    int64wrap_true_lte->set_value(int64true_lte);
    Int64Value* int64wrap_true_lte2 = person.mutable_int64true_lte2();
    int64wrap_true_lte2->set_value(int64true_lte2);
    Int64Value* int64wrap_true_gt = person.mutable_int64true_gt();
    int64wrap_true_gt->set_value(int64true_gt);
    Int64Value* int64wrap_true_gte = person.mutable_int64true_gte();
    int64wrap_true_gte->set_value(int64true_gte);
    Int64Value* int64wrap_true_gte2 = person.mutable_int64true_gte2();
    int64wrap_true_gte2->set_value(int64true_gte2);
    Int64Value* int64wrap_false_equal = person.mutable_int64false_equal();
    int64wrap_false_equal->set_value(int64false_equal);
    Int64Value* int64wrap_false_lt = person.mutable_int64false_lt();
    int64wrap_false_lt->set_value(int64false_lt);
    Int64Value* int64wrap_false_lte = person.mutable_int64false_lte();
    int64wrap_false_lte->set_value(int64false_lte);
    Int64Value* int64wrap_false_lte2 = person.mutable_int64false_lte2();
    int64wrap_false_lte2->set_value(int64false_lte2);
    Int64Value* int64wrap_false_gt = person.mutable_int64false_gt();
    int64wrap_false_gt->set_value(int64false_gt);
    Int64Value* int64wrap_false_gte = person.mutable_int64false_gte();
    int64wrap_false_gte->set_value(int64false_gte);
    Int64Value* int64wrap_false_gte2 = person.mutable_int64false_gte2();
    int64wrap_false_gte2->set_value(int64false_gte2);

    // double
    DoubleValue* doublewrap_true_equal = person.mutable_doubletrue_equal();
    doublewrap_true_equal->set_value(doubletrue_equal);  
    DoubleValue* doublewrap_true_lt = person.mutable_doubletrue_lt();
    doublewrap_true_lt->set_value(doubletrue_lt);
    DoubleValue* doublewrap_true_lte = person.mutable_doubletrue_lte();
    doublewrap_true_lte->set_value(doubletrue_lte);
    
    // Write the new person back to disk.
    fstream output("p2.data", ios::out | ios::trunc | ios::binary);
    if (!person.SerializeToOstream(&output)) {
      cerr << "Failed to write person." << endl;
      return messageStatus;
    }
    Validator v;
    
    messageStatus = v.validate(person);
    

    return messageStatus;
}
