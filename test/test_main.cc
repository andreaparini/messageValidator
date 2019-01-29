/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   test_main.cc
 * Author: a.parini
 *
 * Created on 25 gennaio 2019, 9.11
 */

#include <stdlib.h>

#include "test.h"

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



using namespace std;

int main(int argc, char** argv) {
    
     
    cout << "TEST1 STARTED test1_validation" << endl;
    bool test1 = test1_validation();
    cout << "TEST1 FINISHED test1_validation" << endl << endl;;
     
    cout << "TEST2 STARTED test2_failures" << endl;
    bool test2 = test2_failures();
    cout << "TEST2 FINISHED test2_failures" << endl << endl;
    
    cout << "RESULTS: " << endl << endl;
    if (test1) 
        cout << "TEST1: PASSED" << endl;
    else cout << "TEST1: FAILED" << endl;
    if (test2) 
        cout << "TEST2: PASSED" << endl;
    else cout << "TEST2: FAILED" << endl;
    
    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    
    return (EXIT_SUCCESS);
}

