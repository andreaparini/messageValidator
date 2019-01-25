/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   validator.h
 * Author: a.parini
 *
 * Created on 21 gennaio 2019, 15.23
 */

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <google/protobuf/util/time_util.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/wrappers.pb.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "../proto/validate.pb.h"
using namespace std;

using google::protobuf::util::TimeUtil;
using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::Reflection;
using google::protobuf::Int32Value;
using google::protobuf::Message;

using rulesOption = vector < pair<string, const FieldDescriptor*> > ;


// validator

class Validator {
public:
    
    //default constructor does not do anything, just allocates methods and 
    //setMsgToValidate method
    Validator();
    
    virtual ~Validator();
    
    enum ValidationOutput {VALIDATED, NOT_VALIDATED, 
                           NOTHING_TO_CHECK, INPUT_ERRORS};
    
    
    /* validate method throws an error if the message does not satisfy the set
     * constraints
     * true = no constraint violated
     * false = constraint violated
     */ 
    vector<ValidationOutput> validate(const Message& msgToValidate);
    
private:
    
    /* canFieldHaveOptions method takes as input a fieldDescriptor and returns
     * true if the field is a wrapper, that is, is a message type which contains
     * a single int32_t field
     */
    bool canFieldHaveOptions (const FieldDescriptor* fieldDescriptor);
    
    
    /* checkMismatch checks if the type of the field value is the same as the 
     * type of the option value
     * true = mismatch found
     * false = no mismatch found
     */
    bool checkMismatch (const FieldDescriptor* fieldDescriptor);
    
    
    /* getOptionsValues takes as input a FieldDescriptor and returns the vector
     * of pairs <string,int32_t> of the constraints to apply to the message
     */
    rulesOption getOptionsValues (const FieldDescriptor* fieldDescriptor);
    
    /*  returns 1 if the checkValue against optionValue logic operation
     *  defined by the constraint string is true, 0 otherwise
     */
    bool checkField(const string constraint, 
                    const FieldDescriptor* optionValueFieldDescriptor, 
                    const Message& valueFieldMessage);
    
    template <typename T>
    bool check (const string constraint, 
                const T checkValue, 
                const T optionValue);
    
    
};

#endif /* VALIDATOR_H */

